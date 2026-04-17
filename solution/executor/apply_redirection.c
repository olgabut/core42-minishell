/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:28:42 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/17 23:31:59 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/apply_redirection.h"
#include "executor/redirection.h"

int	redirect_infd_in_child(t_exec_info *ei)
{
	if (ei->infd != STDIN_FILENO)
	{
		if (dup2(ei->infd, STDIN_FILENO) < 0)
			return (-1);
	}
	else if (ei->pipe_infd != -1)
	{
		if (dup2(ei->pipe_infd, STDIN_FILENO) < 0)
			return (-1);
	}
	return (0);
}

int	redirect_outfd_in_child(t_exec_info *ei)
{
	if (ei->outfd != STDOUT_FILENO)
	{
		if (dup2(ei->outfd, STDOUT_FILENO) < 0)
			return (-1);
	}
	else if (ei->pipe_outfd != -1)
	{
		if (dup2(ei->pipe_outfd, STDOUT_FILENO) < 0)
			return (-1);
	}
	return (0);
}

int	redirect_in_parent(t_minishell *sh, t_exec_info *ei)
{
	if (ei->infd != STDIN_FILENO)
	{
		sh->stdin_backup = dup(STDIN_FILENO);
		if (sh->stdin_backup < 0)
			return (-1);
		if (dup2(ei->infd, STDIN_FILENO) < 0)
			return (-1);
	}
	if (ei->outfd != STDOUT_FILENO)
	{
		sh->stdout_backup = dup(STDOUT_FILENO);
		if (sh->stdout_backup < 0)
			return (-1);
		if (dup2(ei->outfd, STDOUT_FILENO) < 0)
			return (-1);
	}
	return (0);
}

int	restore_stdio_from_backup(t_minishell *sh)
{
	if (sh->stdin_backup != STDIN_FILENO)
	{
		if (dup2(sh->stdin_backup, STDIN_FILENO) < 0)
			return (-1);
		sh->stdin_backup = STDIN_FILENO;
	}
	if (sh->stdout_backup != STDOUT_FILENO)
	{
		if (dup2(sh->stdout_backup, STDOUT_FILENO) < 0)
			return (-1);
		sh->stdout_backup = STDOUT_FILENO;
	}
	return (0);
}

int close_all_pipes(t_exec_info *ei_head)
{
	while (ei_head)
	{
		if (ei_head->pipe_infd != -1)
		{
			close(ei_head->pipe_infd);
			ei_head->pipe_infd = -1;//
		}
		if (ei_head->pipe_outfd != -1)
		{
			close(ei_head->pipe_outfd);
			ei_head->pipe_outfd = -1;//
		}
		ei_head = ei_head->next;
	}
	return (0);
}

int	close_fd_in_parent(t_exec_info *ei)
{
	if (ei->infd != STDIN_FILENO)
		if (close(ei->infd) == -1)
			return (-1);
	if (ei->outfd != STDOUT_FILENO)
		if (close(ei->outfd) == -1)
			return (-1);
	if (ei->pipe_infd != -1)
		if (close(ei->pipe_infd) == -1)
			return (-1);
	if (ei->pipe_outfd != -1)
		if (close(ei->pipe_outfd) == -1)
			return (-1);
	return (0);
}
