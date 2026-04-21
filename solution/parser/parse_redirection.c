/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:07:52 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/21 09:58:21 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_split_by_chars.h"
#include "parser/parse.h"
#include "parser/cmd_list_manager.h"
#include "parser/process_word.h"

static t_list	*apply_ifs(t_minishell *mshell, char *word)
{
	char	*ifs;
	t_list	*fields;

	ifs = get_env_value(mshell->env_list, "IFS");
	if (!ifs || !*ifs)
		ifs = " \t\n";
	fields = ft_split_by_chars(word, ifs);
	free(word);
	return (fields);
}

/*
Return
		0 - error (critical like malloc error - stop program)
		1 - ok (all is good)
		-1 - logic error or stop signal (can't execute cmd, but continue prog)
*/
int	parse_redirection(t_minishell *sh, t_cmd *cmd,
	enum e_token_type redir_type, char *word)
{
	t_io	*io_node;
	t_list	*word_list;

	if (redir_type == TOKEN_HEREDOC)
		return (parse_here_doc(sh, cmd, word));
	if (redir_type != TOKEN_APPEND
		&& redir_type != TOKEN_REDIR_OUT
		&& redir_type != TOKEN_REDIR_IN)
		return (1);
	word_list = apply_ifs(sh, process_word(sh, word));
	if (ft_lstsize(word_list) != 1)
	{
		msh_error(word, "ambiguous redirect");
		ft_lstclear(&word_list, free);
		g_info.exit_code = 1;
		return (-1);
	}
	io_node = create_io_node(redir_type, word_list->content);
	if (!io_node)
		return (0);
	add_io_to_cmd(cmd, io_node);
	add_new_memory_link_for_control(&sh->memory_head, io_node->path);
	add_new_memory_link_for_control(&sh->memory_head, io_node);
	return (1);
}
