/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:34:55 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/14 15:01:30 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/apply_redirection.h"
#include "executor/execute_built_in.h"
#include "executor/redirection.h"
#include "executor/external_cmd.h"
#include "executor/cmd_path.h"
#include "minishell.h"
#include <sys/wait.h>

int	execute_cmd(t_exec_info *ei, t_minishell *sh, bool need_fork, int pipefd)
{
	int	pid;

	pid = 0;
	if (is_built_in_cmd(ei->argv[0]))
		if (need_fork)
		{
			pid = fork();
			if (pid == 0)
			{
				set_signals_for_child_proces();
				if (pipefd != -1)
					close(pipefd);
				execute_built_in_child(ei, sh);
			}
		}
		else
			return (execute_built_in_parent(ei, sh));
	else
	{
		find_cmd_path(ei, sh->env_list, &sh->memory_head);
		pid = fork();
		if (pid == 0)
		{
			set_signals_for_child_proces();
			if (pipefd != -1)
				close(pipefd);
			external_child_process(ei);
		}
	}
	close_in_parent(ei);
	return (pid);
}
/*
 * # RETURN VALUE
 * on success returns 1, on failure return 0
*/
static int	execute_pipeline(t_minishell *sh)
{
	t_cmd		*cur_cmd;
	int			prev_read_fd;
	t_exec_info	*ei;
	int			pid[MAX_PIPE_COUNT];
	int			i = 0;
	int			status;

	prev_read_fd = -1;
	cur_cmd = sh->cmd_list;
	while (cur_cmd)
	{
		ei = exec_info_init(cur_cmd->args, sh->env_list, &sh->memory_head);
		if (!ei)
		{
			msh_error("memory", "Memory allocation error");
			return (0);
		}
		if (prev_read_fd != -1)
		{
			ei->infd = prev_read_fd;
			prev_read_fd = -1;
		}
		if (cur_cmd->next)
		{
			prev_read_fd = create_pipefd(ei);
			if (prev_read_fd == -1)
			{
				msh_error("read_fd", NULL);
				return (0);
			}
		}
		if (prepare_redirs_before_exec(cur_cmd, ei) != 0)
		{
			msh_error("redirections", NULL);
			return (0);
		}
		pid[i] = execute_cmd(ei, sh, cur_cmd->next != NULL, prev_read_fd);
		if (pid[i] < 0)
			break ;
		i++;
		cur_cmd = cur_cmd->next;
	}
	while (i > 0)
	{
		i--;
		if (pid[i] != 0)
			waitpid(pid[i], &status, 0);
		g_info.exit_code = WEXITSTATUS(status);
	}
	return (1);
}

static int	execute_single_cmd(t_minishell *sh)
{
	int	res;

	if (sh->cmd_list && sh->cmd_list->args && sh->cmd_list->args[0]
		&& is_built_in_cmd(sh->cmd_list->args[0]))
	{
		res = execute_built_in_cmd(sh->cmd_list, sh);
		if (restore_stdio(sh) < 0)
			res = 0;
		return (res);
	}
	else
		return (execute_external_cmd(sh->cmd_list, sh));
}

/*
	Return
		0 = we need to stop program (readirection errors or malloc errors)
		1 = OK, continue
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
