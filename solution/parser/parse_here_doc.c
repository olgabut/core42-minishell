/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 15:42:43 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/22 22:29:38 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/cmd_list_manager.h"

/*
HEREDOC documentation:
https://tiswww.case.edu/php/chet/readline/readline.html
#index-rl_005fredisplay_005ffunction
*/

/*
	Return 0 - error
		   1 - ok
*/
static int	read_here_doc_lines(char **res, char *eof)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (g_info.sigint)
		{
			if (buf)
				free(buf);
			return (0);
		}
		if (ft_strcmp(buf, eof) == 0)
		{
			free(buf);
			return (1);
		}
		*res = ft_strjoin_free(*res, buf);
		*res = ft_strjoin_free(*res, "\n");
		if (buf)
			free(buf);
		if (!res)
			return (0);
	}
}

/*
	Return 0 - error
		   1 - ok
*/
int	parse_here_doc(t_minishell *sh, t_cmd *cmd, char *eof)
{
	t_io	*io_node;
	char	*path;
	int		(*default_getc)(FILE *);
	int		status_read_heredoc;

	path = ft_strdup("");
	if (!path)
		return (0);
	default_getc = rl_getc_function;
	rl_getc_function = heredoc_rl_getc;
	status_read_heredoc = read_here_doc_lines(&path, eof);
	if (g_info.sigint)
	{
		rl_getc_function = default_getc;
		free(path);
		return (0);
	}
	io_node = create_io_node(TOKEN_HEREDOC, path);
	if (!io_node)
		return (0);
	add_io_to_cmd(cmd, io_node);
	add_new_memory_link_for_control(&sh->memory_head, io_node->path);
	add_new_memory_link_for_control(&sh->memory_head, io_node);
	return (status_read_heredoc);
}
