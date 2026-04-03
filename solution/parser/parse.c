/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:34:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/02 22:21:55 by obutolin         ###   ########.fr       */
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

t_cmd	*parser(t_minishell *mshell, t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*head;
	t_list	*temp_args;

	if (!tokens || !tokens->value)
		return (NULL);
	head = init_cmd(mshell);
	cmd = head;
	temp_args = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			cmd->args = ft_strvec_from_word_list(temp_args);
			ft_lstclear(&temp_args, NULL);
			cmd->next = init_cmd(mshell);
			cmd = cmd->next;
		}
		else if (is_redirection(tokens->type))
			add_io(mshell, cmd, &tokens);
		else if (tokens->type == TOKEN_HEREDOC)
		{
			if (add_here_doc(mshell, cmd, &tokens))
			{
				ft_lstclear(&temp_args, free);
				mshell->cmd_list = NULL;
				return (NULL);
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
	return (head);
}
