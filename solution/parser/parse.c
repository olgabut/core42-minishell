/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:34:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 11:39:05 by dprikhod         ###   ########.fr       */
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

void	add_arg(t_list **word_list, char *arg)
{
	t_list	node;
	char	*str;

	str = ft_strdup(arg);
	if (!str)
		return ;
	node = ft_lstnew(str);
	if (!node)
		return ;
	ft_lstadd_back(&word_list, node);
}

void	ioadd_back(t_cmd *cmd, t_io *node);

void	add_io(t_cmd *cmd, t_token **token)
{
	t_io	*node;

	node = malloc(sizeof(t_io));
	if (!node)
		return ;
	node->type = (*token)->type;
	node->path = ft_strdup((*token)->value);
	if (!node->path)
		return ;
	ioadd_back(cmd, node);
	*token = (*token)->next;
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
			free_list(&temp_args);
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
		free_list(&temp_args);
	}
	return (head);
}
