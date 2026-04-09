/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:34:55 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/10 01:37:42 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/apply_redirection.h"
#include "executor/execute_built_in.h"
#include "executor/redirection.h"
#include "executor/external_cmd.h"
#include "executor/cmd_path.h"
#include "minishell.h"
#include <sys/wait.h>

int	execute_cmd(t_exec_info *ei, t_minishell *sh, bool need_fork)
{
	int	pid;
	int status;

	if (is_built_in_cmd(ei->argv[0]))
		if (need_fork)
		{
			pid = fork();
			if (pid == 0)
				execute_built_in_child(ei, sh);
		}
		else
			return (execute_built_in_parent(ei, sh));
	else
	{
		find_cmd_path(ei, sh->env_list, &sh->memory_head);
		pid = fork();
		if (pid == 0)
			external_child(ei);
	}
	close_in_parent(ei);
	status = 0;
	waitpid(pid, &status, 0);
	sh->exit_code = WEXITSTATUS(status);
	return (sh->exit_code);
}
/*
 * # RETURN VALUE
 * on success returns 0, on failure returns error code:
 * - 12 in case of `malloc()` failure;
 * - `errno` that set by `open()` or `pipe()` on its failure.
 */
static int	execute_pipeline(t_minishell *sh)
{
	t_cmd		*cur_cmd;
	int			prev_read_fd;
	t_exec_info	*ei;
	bool		need_fork;

	prev_read_fd = -1;
	cur_cmd = sh->cmd_list;
	while (cur_cmd)
	{
		need_fork = 0;
		ei = exec_info_init(cur_cmd->args, sh->env_list, &sh->memory_head);
		if (!ei)
			return (ENOMEM);
		if (prev_read_fd != -1)
		{
			ei->infd = prev_read_fd;
			prev_read_fd = -1;
		}
		if (cur_cmd->next)
		{
			prev_read_fd = create_pipefd(ei);
			if (prev_read_fd == -1)
				return (errno);
		}
		if (prepare_redirs_before_exec(cur_cmd, ei) != 0)
			return (errno);
		if (cur_cmd->next)
			need_fork = 1;
		execute_cmd(ei, sh, need_fork);
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

static int	execute_single_cmd(t_minishell *sh)
{
	int	exit_code;

	if (sh->cmd_list && sh->cmd_list->args && sh->cmd_list->args[0]
		&& is_built_in_cmd(sh->cmd_list->args[0]))
	{
		exit_code = execute_built_in_cmd(sh->cmd_list, sh);
		if (restore_stdio(sh) < 0)
			exit_code = -1;
		return (exit_code);
	}
	else
		return (execute_external_cmd(sh->cmd_list, sh));
}

/*
	Executes commands (sh->cmd_list)
	Return	1-ok
			0-error
*/
int	execute(t_minishell *sh)
{
	if (!sh || !sh->cmd_list || !sh->cmd_list->args)
		return (1);
	if (sh->cmd_list->next)
		return (execute_pipeline(sh));
	else
		return (execute_single_cmd(sh));
}
