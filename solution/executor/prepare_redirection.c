/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:17:20 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/22 21:59:41 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	set_fd(t_exec_info *ei, t_io *io)
{
	int	fd;
	int	pipefd[2];

	fd = -2;
	if (io->type == TOKEN_REDIR_OUT)
		fd = open(io->path, O_WRONLY | O_CREAT, 446);
	else if (io->type == TOKEN_APPEND)
		fd = open(io->path, O_WRONLY | O_CREAT | O_APPEND, 446);
	else if (io->type == TOKEN_REDIR_IN)
		fd = open(io->path, O_RDONLY);
	else if (io->type == TOKEN_HEREDOC)
	{
		if (pipe(pipefd) == -1)
			return (-2);
		ft_putstr_fd(io->path, pipefd[1]);
		close(pipefd[1]);
		fd = pipefd[0];
	}
	if (fd != -1 && (io->type == TOKEN_REDIR_OUT || io->type == TOKEN_APPEND))
		ei->outfd = fd;
	if (fd != -1 && (io->type == TOKEN_REDIR_IN || io->type == TOKEN_HEREDOC))
		ei->infd = fd;
	return (fd);
}

/*
	Return 1 - ok
	0 - error (can't execute the command)
*/
int	prepare_redirections(t_exec_info *ei, t_io *io_head)
{
	t_io	*io;
	int		res;

	if (!io_head)
		return (1);
	io = io_head;
	while (io)
	{
		res = set_fd(ei, io);
		if (res == -1)
		{
			msh_error(io->path, NULL);
			g_info.exit_code = 1;
			ei->is_error = true;
			return (1);
		}
		io = io->next;
	}
	return (1);
}

int	prepare_pipe_fd(t_exec_info *ei)
{
	int	fd_pipe[2];

	if (!ei->prev)
		return (1);
	if (pipe(fd_pipe) < 0)
	{
		msh_error("pipe", "Pipe error");
		return (0);
	}
	ei->prev->pipe_outfd = fd_pipe[1];
	ei->pipe_infd = fd_pipe[0];
	return (1);
}
