/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:17:20 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/28 13:43:35 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/redirection.h"
#include "minishell.h"
#include <fcntl.h>
#include <errno.h>

int	**prepare_pipes_for_here_doc(t_cmd *cmd)
{
	t_io	*list;
	int		len;
	int		i;
	int		*fd_here_doc[2];
	int		j;
	int		**ret;

	j = 0;
	i = 0;
	list = cmd->io_list;
	if (!list)
		return (NULL);
	len = ft_lstsize((t_list *)list);
	while (i < len)
	{
		if (list->type == TOKEN_HEREDOC)
		{
			pipe(*(fd_here_doc + j));
			j++;
		}
		list = list->next;
	}
	ret = malloc((sizeof(int[2])) * (j + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, fd_here_doc, sizeof(int[2]) * (j + 1));
	return (ret);
}

int	fill_here_doc(t_cmd *cmd, int *fd[2])
{
	t_io	*list;

	list = cmd->io_list;
	while (list->next)
	{
		if (list->type == TOKEN_HEREDOC)
		{
			close(*fd[0]);
			ft_putstr_fd(list->path, *fd[1]);
			close(*fd[1]);
			fd++;
		}
	}
	return (0);
}

int	apply_here_doc(int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	return (0);
}

int	prepare_redirs_before_exec(t_cmd *cmd, int *hd_pipe[2])
{
	t_io	*list;
	int		new_fd;
	int		old_fd;

	list = cmd->io_list;
	old_fd = STDIN_FILENO;
	while (list->next)
	{
		if (list->type == TOKEN_REDIR_IN)
			new_fd = open(list->path, O_RDONLY);
		else if (list->type == TOKEN_REDIR_OUT)
			new_fd = open(list->path, O_WRONLY | O_TRUNC);
		else if (list->type == TOKEN_APPEND)
			new_fd = open(list->path, O_WRONLY | O_TRUNC | O_APPEND);
		else if (list->type == TOKEN_HEREDOC)
		{
			if (!hd_pipe)
				return (1);
			close(*hd_pipe[1]);
			new_fd = *hd_pipe[0];
			hd_pipe++;
		}
		if (new_fd < 0)
			return(errno);
		if (list->type == TOKEN_REDIR_OUT || list->type == TOKEN_APPEND)
			old_fd = STDOUT_FILENO;
		if (dup2(new_fd, old_fd) < 0)
			return (errno);
		list = list->next;
	}
	return (0);
}
