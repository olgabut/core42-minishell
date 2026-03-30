/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:17:20 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/30 16:36:04 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/redirection.h"
#include "minishell.h"
#include <fcntl.h>

static int	check_token(int type, t_exec_info *ei, char *path)
{
	int	pipefd[2];

	if (type == TOKEN_REDIR_IN)
	{
		if (ei->infd != STDIN_FILENO)
			close(ei->infd);
		ei->infd = open(path, O_RDONLY);
	}
	else if (type == TOKEN_REDIR_OUT)
	{
		if (ei->outfd != STDOUT_FILENO)
			close(ei->outfd);
		ei->outfd = open(path, O_WRONLY | O_TRUNC);
	}
	else if (type == TOKEN_APPEND)
	{
		if (ei->outfd != STDOUT_FILENO)
			close(ei->outfd);
		ei->outfd = open(path, O_WRONLY | O_TRUNC | O_APPEND);
	}
	else if (type == TOKEN_HEREDOC)
	{
		if (ei->infd != STDIN_FILENO)
			close(ei->infd);
		if (pipe(pipefd) == -1)
			return (-2);
		ft_putstr_fd(path, pipefd[1]);
		close(pipefd[1]);
		ei->infd = pipefd[0];
	}
	if (type == TOKEN_APPEND || type == TOKEN_REDIR_OUT)
		return (ei->outfd);
	else
		return (ei->infd);
}
// maybe it is good to add check after each open later
t_exec_info	*prepare_redirs_before_exec(t_cmd *cmd, t_memory_info **head, t_env *env)
{
	t_exec_info	*ei;
	t_io		*list;

	ei = malloc(sizeof(t_exec_info));
	if (!add_new_memory_link_for_control(head, ei))
		return (NULL);
	ei->infd = STDIN_FILENO;
	ei->outfd = STDOUT_FILENO;
	list = cmd->io_list;
	while (list->next)
	{
		if (check_token(list->type, ei, list->path) < 0)
			return (NULL);
		list = list->next;
	}
	ei->argv = cmd->args;
	ei->envp = get_env_array(head, env);
	return (ei);
}
