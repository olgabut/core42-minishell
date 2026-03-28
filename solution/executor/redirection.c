/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:17:20 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/28 19:20:16 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/redirection.h"
#include "minishell.h"
#include <fcntl.h>

// maybe it is good to add check aftere each open later
t_exec_info	*prepare_redirs_before_exec(t_cmd *cmd, t_memory_info **head)
{
	t_exec_info	*ei;
	t_io		*list;
			int pipefd[2];

	ei = malloc(sizeof(t_exec_info));
	if (!add_new_memory_link_for_control(head, ei))
		return (NULL);
	ei->infd = STDIN_FILENO;
	ei->outfd = STDOUT_FILENO;
	list = cmd->io_list;
	while (list->next)
	{
		if (list->type == TOKEN_REDIR_IN)
		{
			if (ei->infd != STDIN_FILENO)
				close(ei->infd);
			ei->infd = open(list->path, O_RDONLY);
		}
		else if (list->type == TOKEN_REDIR_OUT)
		{
			if (ei->outfd != STDOUT_FILENO)
				close(ei->outfd);
			ei->outfd = open(list->path, O_WRONLY | O_TRUNC);
		}
		else if (list->type == TOKEN_APPEND)
		{
			if (ei->outfd != STDOUT_FILENO)
				close(ei->outfd);
			ei->outfd = open(list->path, O_WRONLY | O_TRUNC | O_APPEND);
		}
		else if (list->type == TOKEN_HEREDOC)
		{
			if (ei->infd != STDIN_FILENO)
				close(ei->infd);
			pipe(pipefd);
			ft_putstr_fd(list->path, pipefd[1]);
			close(pipefd[1]);
			ei->infd = pipefd[0];
		}
		list = list->next;
	}
	/*
	only copies pointer to arguments, however, need to fill envp later and 
	consider to allocate full copy of args and envp to send to fork, to free_memory_links
	in child, but don't lost data. 
	*/
	ei->argv = cmd->args;	
	return (ei);
}
