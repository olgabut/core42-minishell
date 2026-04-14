/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:06:31 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/10 12:39:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool	is_redirection(enum e_token_type type)
{
	if (type == TOKEN_APPEND || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN)
		return (true);
	else
		return (false);
}

void	add_arg(t_minishell *mshell, t_list **word_list, char *token_word)
{
	char	*str;

	str = check_word(mshell, token_word);
	if (!str)
		return ;
	if (str[0] == '\0')
	{
		free(str);
		return ;
	}
	add_new_memory_link_for_control(&mshell->memory_head, str);
	ft_lstadd_back(word_list, ft_lstnew(str));
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

/*
	Return 0 - error
		   1 - ok
*/
int	add_io(t_minishell *mshell, t_cmd *cmd, t_token **token)
{
	t_io	*node;
	char	*path;
	t_list	*word_list;

	node = malloc(sizeof(t_io));
	if (!node)
		return (0);
	node->type = (*token)->type;
	*token = (*token)->next;
	path = (*token)->value;
	word_list = apply_ifs(mshell, check_word(mshell, path));
	if (ft_lstsize(word_list) != 1)
	{
		msh_error(path, "ambiguous redirect");
		free(node);
		ft_lstclear(&word_list, free);
		return (0);
	}
	node->path = word_list->content;
	add_new_memory_link_for_control(&mshell->memory_head, node->path);
	free(word_list);
	node->next = NULL;
	add_new_memory_link_for_control(&mshell->memory_head, node);
	io_add_back(cmd, node);
	return (1);
}
/*
HEREDOC documentation:
https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fredisplay_005ffunction
*/
/*
	Return 0 - error
		   1 - ok
*/
int	add_here_doc(t_minishell *mshell, t_cmd *cmd, t_token **token)
{
	t_io	*node;
	char	*buf;
	char	*eof;
	char	*res;
	int (*default_getc)(FILE *);

	(void)mshell;
	res = ft_strdup("");
	if (!res)
		return (0);
	*token = (*token)->next;
	eof = (*token)->value;
	default_getc = rl_getc_function;
	rl_getc_function = heredoc_rl_getc;
	while (1)
	{
		buf = readline("> ");
		if (g_info.sigint)
		{
			rl_getc_function = default_getc;
			if (buf)
				free(buf);
			free(res);
			return (0);
		}
		if (!buf)
		{
			free(res);
			return (0);
		}
		if (ft_strcmp(buf, eof) == 0)
		{
			free(buf);
			break ;
		}
		res = ft_strjoin_free(res, buf);
		res = ft_strjoin_free(res, "\n");
		if (!res)
			return (0);
	}
	node = malloc(sizeof(t_io));
	if (!node)
	{
		free(res);
		return (1);
	}
	node->next = NULL;
	node->path = res;
	add_new_memory_link_for_control(&mshell->memory_head, node->path);
	node->type = TOKEN_HEREDOC;
	add_new_memory_link_for_control(&mshell->memory_head, node);
	io_add_back(cmd, node);
	return (1);
}
