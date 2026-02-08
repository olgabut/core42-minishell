/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:06:31 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 15:07:19 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	io_add_back(t_cmd *cmd, t_io *node)
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
