/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:34:55 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/17 23:22:08 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/apply_redirection.h"
#include "executor/execute_built_in.h"
#include "executor/redirection.h"
#include "executor/external_cmd.h"
#include "executor/cmd_path.h"
#include "executor/execute.h"
#include "minishell.h"
#include <sys/wait.h>

/* Return PID */
int	execute_cmd(t_exec_info *ei, t_minishell *sh)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		set_signals_in_child_process();
		if (redirect_infd_in_child(ei) < 0
			|| redirect_outfd_in_child(ei) < 0
			|| close_all_pipes(sh->ei_list) < 0)
		{
			//msh_error();
			exit (errno);
		}
		if (ei->is_built_in)
			execute_built_in_child(ei, sh);
		else
			execute_external_in_child(ei);
		exit(g_info.exit_code);
	}
	return (pid);
}

void analyse_status_from_child(int status)
{
	int	sig;

	if (WIFEXITED(status))
			g_info.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		g_info.exit_code = 128 + sig;
		if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		if (sig == SIGINT)
			write(1, "\n", 1);
	}
}

/*
	Return
		0 = we need to stop program (readirection errors or malloc errors)
		1 = OK, continue
*/
int execute_in_child(t_minishell *sh, t_exec_info *ei_head)
{
	t_exec_info	*ei;
	pid_t		*pids;
	int			status;
	int cmd_count;
	int i;

	ei = ei_head;
	cmd_count = get_cmd_count_by_ei(ei_head);
	pids = ft_calloc(cmd_count, sizeof(pid_t));
	if (pids == NULL)
	{
		msh_error("malloc", "Malloc Error");
		return (0);
	}
	add_new_memory_link_for_control(&sh->memory_head, pids);
	i = 0;
	while (ei)
	{
		pids[i] = execute_cmd(ei, sh);
		if (pids[i] == -1)
		{
			msh_error("fork", "Fork error");
			return (0);
		}
		i++;
		ei = ei->next;
	}
	if (close_all_pipes(ei_head) < 0)
		return (0);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
			analyse_status_from_child(status);
		i++;
	}
	return (1);
}

void print_ei_list(t_exec_info *ei_head)
{
	t_exec_info	*ei;
	int i;

	ei = ei_head;
	i = 0;
	while(ei)
	{
		printf("%d ", i);
		printf("ei %s \nis_built_in=%d\npath=%s\n", 
			ei->argv[0], ei->is_built_in, ei->path);
		printf("infd=%d\noutfd=%d\n", ei->infd, ei->outfd);
		printf("pipe_infd=%d\npipe_outfd=%d\n", ei->pipe_infd, ei->pipe_outfd);
		printf("----------------\n");
		i++;
		ei=ei->next;
	}
}

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
	//print_ei_list(ei_head);
	if (ei_head->next == NULL && ei_head->is_built_in)
		return(execute_built_in_parent(ei_head, sh));
	else
		return(execute_in_child(sh, ei_head));
	return (1);
}
