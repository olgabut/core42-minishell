/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:06:31 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/22 16:06:17 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_word.h"

bool	is_redirection(enum e_token_type type)
{
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN)
		return (true);
	else
		return (false);
}

void	add_arg(t_minishell *mshell, t_list **word_list, char *arg)
{
	t_list	*node;
	char	*str;

	str = check_word(mshell, arg);
	if (!str)
		return ;
	node = apply_ifs(mshell, str);
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

void	add_io(t_minishell *mshell, t_cmd *cmd, t_token **token)
{
	t_io	*node;
	char	*path;
	t_list	*word_list;

	node = malloc(sizeof(t_io));
	if (!node)
		return ;
	node->type = (*token)->type;
	*token = (*token)->next;
	path = (*token)->value;
	word_list = apply_ifs(mshell, check_word(mshell, path));
	if (ft_lstsize(word_list) != 1)
		return (perror("Ambigious redirect\n"));
	node->path = word_list->content;
	free(word_list);
	io_add_back(cmd, node);
}
