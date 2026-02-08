/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:34:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 16:49:44 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*head;
	t_list	*temp_args;

	head = init_cmd();
	cmd = head;
	temp_args = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			cmd->args = ft_strvec_from_word_list(temp_args);
			ft_lstclear(&temp_args, NULL);
			cmd->next = init_cmd();
			cmd = cmd->next;
		}
		else if (is_redirection(tokens->type))
			add_io(cmd, &tokens);
		else
			add_arg(&temp_args, tokens->value);
		if (tokens)
			tokens = tokens->next;
	}
	if (temp_args)
	{
		cmd->args = ft_strvec_from_word_list(temp_args);
		ft_lstclear(&temp_args, NULL);
	}
	return (head);
}
