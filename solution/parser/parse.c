/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:34:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 10:24:45 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void);

bool	is_redirection(enum e_token_type type)
{
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN)
		return (true);
	else
		return (false);
}

void	add_arg(t_cmd *cmd, char *arg)
{
}

void	add_io(t_cmd *cmd, t_token *token)
{}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*head;

	head = init_cmd();
	cmd = head;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			cmd->next = init_cmd();
			cmd = cmd->next;
		}
		else if (is_redirection(tokens->type))
		{
			add_io(cmd, tokens);
			tokens = tokens->next;
		}
		else
			add_arg(cmd, tokens->value);
		tokens = tokens->next;
	}
	return (cmd);
}
