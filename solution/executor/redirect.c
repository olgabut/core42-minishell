/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:28:42 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/19 15:45:25 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_infd_in_child(t_exec_info *ei)
{
	if (ei->infd != STDIN_FILENO)
	{
		dup2(ei->infd, STDIN_FILENO);
		if (ei->pipe_infd != -1)
			close(ei->pipe_infd);
	}
	else if (ei->pipe_infd != -1)
	{
		dup2(ei->pipe_infd, STDIN_FILENO);
	}
	return (0);
}

int	redirect_outfd_in_child(t_exec_info *ei)
{
	if (ei->outfd != STDOUT_FILENO)
	{
		dup2(ei->outfd, STDOUT_FILENO);
		if (ei->pipe_outfd != -1)
			close(ei->pipe_outfd);
	}
	else if (ei->pipe_outfd != -1)
	{
		dup2(ei->pipe_outfd, STDOUT_FILENO);
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
