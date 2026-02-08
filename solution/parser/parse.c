/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:34:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 14:33:33 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

bool	is_redirection(enum e_token_type type)
{
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN)
		return (true);
	else
		return (false);
}

void	add_arg(t_list **word_list, char *arg)
{
	t_list	*node;
	char	*str;

	str = ft_strdup(arg);
	if (!str)
		return ;
	node = ft_lstnew(str);
	if (!node)
		return ;
	ft_lstadd_back(word_list, node);
}

void	io_add_back(t_cmd *cmd, t_io *node)
{
	t_io	*last;

	if (!cmd)
		return ;
	if (!cmd->io_list)
	{
		cmd->io_list = node;
		return ;
	}
	last = cmd->io_list;
	while (last->next)
		last = last->next;
	last->next = node;
}

void	add_io(t_cmd *cmd, t_token **token)
{
	t_io	*node;

	node = malloc(sizeof(t_io));
	if (!node)
		return ;
	node->type = (*token)->type;
	*token = (*token)->next;
	node->path = ft_strdup((*token)->value);
	if (!node->path)
		return ;
	io_add_back(cmd, node);
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
		tokens = tokens->next;
	}
	if (temp_args)
	{
		cmd->args = ft_strvec_from_word_list(temp_args);
		ft_lstclear(&temp_args, NULL);
	}
	return (head);
}
