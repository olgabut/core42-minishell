/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:34:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/04 23:02:37 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cases.h"

static t_cmd	*init_cmd(t_minishell *mshell)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	add_new_memory_link_for_control(&mshell->memory_head, cmd);
	return (cmd);
}

/*
	Return
		0 = we need to stop program (malloc errors or ambiguous redirect)
		1 = OK, continue
*/
int	parser(t_minishell *mshell, t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*cmd_head;
	t_list	*temp_args;

	if (!tokens || !tokens->value)
		return (1);
	cmd_head = init_cmd(mshell);
	cmd = cmd_head;
	temp_args = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			cmd->args = ft_strvec_from_word_list(temp_args);
			add_new_memory_link_for_control(&mshell->memory_head, cmd->args);
			ft_lstclear(&temp_args, NULL);
			cmd->next = init_cmd(mshell);
			cmd = cmd->next;
		}
		else if (is_redirection(tokens->type))
		{
			if (!add_io(mshell, cmd, &tokens))
				return (0);
		}
		else if (tokens->type == TOKEN_HEREDOC)
		{
			if (add_here_doc(mshell, cmd, &tokens))
			{
				ft_lstclear(&temp_args, free);
				mshell->cmd_list = NULL;
				return (1); //NULL
			}
		}
		else
			add_arg(mshell, &temp_args, tokens->value);
		if (tokens)
			tokens = tokens->next;
	}
	if (temp_args)
	{
		cmd->args = ft_strvec_from_word_list(temp_args);
		add_new_memory_link_for_control(&mshell->memory_head, cmd->args);
		ft_lstclear(&temp_args, NULL);
	}
	mshell->cmd_list = cmd_head;
	return (1);
}
