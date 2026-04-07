/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:28:42 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/07 16:46:49 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/apply_redirection.h"
#include "executor/redirection.h"

int	redirect_simple(t_exec_info *ei)
{
	if (ei->infd != STDIN_FILENO)
		if (dup2(ei->infd, STDIN_FILENO) < 0)
			return (-1);
	if (ei->outfd != STDOUT_FILENO)
		if (dup2(ei->outfd, STDOUT_FILENO) < 0)
			return (-1);
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

int	restore_stdio(t_minishell *sh)
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

int	redirect_built_in(t_cmd *cmd, t_minishell *sh)
{
	t_exec_info	*ei;

	if (!cmd->io_list)
		return (-1);
	ei = exec_info_init(cmd->args, sh->env_list, &sh->memory_head);
	if (!ei)
		return (18);
	prepare_redirs_before_exec(cmd, ei);
	return (redirect_in_parent(sh, ei));
}

int	close_in_parent(t_exec_info *ei)
{
	if (ei->infd != STDIN_FILENO)
		if (close(ei->infd) < -1)
			return (-1);
	if (ei->outfd != STDOUT_FILENO)
		if (close(ei->outfd) < -1)
			return (-1);
	return (0);
}
