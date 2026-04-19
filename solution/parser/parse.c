/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:34:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/14 22:31:36 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parse.h"
#include "parser/cmd_list_manager.h"

static int	parse_tokens(t_minishell *sh, t_token *tokens, t_cmd **cmd_head)
{
	enum e_token_type	redir_type;

	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			add_new_cmd(cmd_head, create_empty_cmd(sh));
		else if (tokens->type == TOKEN_WORD)
			parse_word(sh, get_last_cmd(cmd_head), tokens->value);
		else
		{
			redir_type = tokens->type;
			tokens = tokens->next;
			if (!parse_redirection(sh, get_last_cmd(cmd_head),
					redir_type, tokens->value))
				return (0);
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (1);
}

/*
	Return
		0 = we need to stop program (malloc errors or ambiguous redirect)
		1 = OK, continue
*/
int	parse(t_minishell *sh, t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd;

	if (!tokens || !tokens->value)
		return (1);
	cmd_head = create_empty_cmd(sh);
	if (!cmd_head)
		return (0);
	if (!parse_tokens(sh, tokens, &cmd_head))
		return (0);
	sh->cmd_list = cmd_head;
	cmd = cmd_head;
	while (cmd)
	{
		cmd->args = ft_strvec_from_word_list(cmd->args_list);
		add_new_memory_link_for_control(&sh->memory_head, cmd->args);
		cmd = cmd->next;
	}
	return (1);
}
