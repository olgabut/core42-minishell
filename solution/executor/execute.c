/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:34:55 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/24 11:11:41 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/execute_built_in.h"
#include "executor/execute.h"
#include "executor/close_fd.h"
#include "executor/run_child_process.h"
#include "minishell.h"
#include <sys/wait.h>

static int	create_pids(pid_t **pids, int cmd_count, t_memory_info **memory)
{
	*pids = ft_calloc(cmd_count, sizeof(pid_t));
	if (*pids == NULL)
	{
		msh_error("malloc", "Malloc Error");
		return (0);
	}
	if (!add_new_memory_link_for_control(memory, *pids))
	{
		msh_error("malloc", "Malloc Error");
		return (0);
	}
	return (1);
}

static int	run_child_processes(t_exec_info *ei_head, pid_t **pids,
	t_minishell *sh)
{
	t_exec_info	*ei;
	pid_t		*local_pids;
	int			i;

	i = 0;
	ei = ei_head;
	local_pids = *pids;
	while (ei)
	{
		local_pids[i] = run_child_process(ei, sh);
		if (local_pids[i] == -1)
		{
			msh_error("fork", "Fork error");
			return (0);
		}
		i++;
		ei = ei->next;
	}
	return (1);
}

static int	wait_pids(pid_t *pids, int cmd_count)
{
	int		finished;
	pid_t	cur_pid;
	int	status;

	finished = 0;
	while (finished < cmd_count)
	{
		cur_pid = waitpid(-1, &status, 0);
		if (cur_pid == pids[cmd_count - 1])
		{
			if (WIFEXITED(status))
				g_info.exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_info.exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
			}
		}
		finished++;
	}
	return (1);
}

/*
	Return
		0 = we need to stop program (readirection errors or malloc errors)
		1 = OK, continue
*/
static int	execute_cmd_in_child_process(t_minishell *sh, t_exec_info *ei_head)
{
	pid_t		*pids;
	int			cmd_count;

	cmd_count = get_cmd_count_by_ei(ei_head);
	if (!create_pids(&pids, cmd_count, &sh->memory_head))
		return (0);
	if (!run_child_processes(ei_head, &pids, sh))
		return (0);
	if (close_all_pipes(ei_head) < 0)
		return (0);
	if (!wait_pids(pids, cmd_count))
		return (0);
	return (1);
}

// void print_ei_list(t_exec_info *ei_head)
// {
// 	t_exec_info	*ei;
// 	int i;

// 	ei = ei_head;
// 	i = 0;
// 	while(ei)
// 	{
// 		printf("%d ", i);
// 		printf("ei %s \nis_built_in=%d\npath=%s\n",
// 			ei->argv[0], ei->is_built_in, ei->path);
// 		printf("infd=%d\noutfd=%d\n", ei->infd, ei->outfd);
// 		printf("pipe_infd=%d\npipe_outfd=%d\n", ei->pipe_infd, ei->pipe_outfd);
// 		printf("----------------\n");
// 		i++;
// 		ei=ei->next;
// 	}
// }

/*
	Return
		0 = we need to stop program (readirection errors or malloc errors)
		1 = OK, continue
*/
int	execute(t_minishell *sh)
{
	t_exec_info	*ei_head;

	if (!sh || !sh->cmd_list || !sh->cmd_list->args)
		return (1);
	if (!prepare_exec_info_list(&ei_head, sh))
		return (1);
	if (!ei_head || !ei_head->argv || !ei_head->argv[0])
		return (1);
	sh->ei_list = ei_head;
	if (ei_head->next == NULL && ei_head->is_built_in)
		return (execute_builtin_cmd_in_parent_process(ei_head, sh));
	else
		return (execute_cmd_in_child_process(sh, ei_head));
	return (1);
}
