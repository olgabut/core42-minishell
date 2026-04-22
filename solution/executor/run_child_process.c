/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:35:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/22 13:31:04 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/execute_built_in.h"
#include "executor/redirect.h"
#include "executor/close_fd.h"
#include <sys/wait.h>

/*
	execve(pathname, argv, envp)
		pathname - The pathname of the command to execute
		argv - The arguments to pass to the new program
		envp - The environment list

	waitpid status bits meaning
		0-6    signal number that caused child to exit,
		       or 0177 if child stopped / continued
		       or zero if child exited without a signal
		7     1 if core dumped, else 0
		8-15   low 8 bits of value passed to _exit/exit or returned by main,
		       or signal that caused child to stop/continue
*/
static void	execute_external_cmd_in_child_process(t_exec_info *ei)
{
	if (ei->is_error)
		exit(EXIT_FAILURE);
	else if (execve(ei->path, ei->argv, ei->envp) == -1)
	{
		if (errno == ENOENT)
			exit(EXIT_CMD_NOT_FOUND);
		else if (errno == EACCES)
			exit(EXIT_PERMISSION_DENIED);
		else
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/* Return PID */
int	run_child_process(t_exec_info *ei, t_minishell *sh)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		set_signals_in_child_process();
		if (redirect_outfd_in_child(ei) < 0
			|| redirect_infd_in_child(ei) < 0
			|| close_all_pipes(sh->ei_list) < 0)
		{
			exit(errno);
		}
		if (ei->is_built_in)
			execute_builtin_cmd_in_child_process(ei, sh);
		else
			execute_external_cmd_in_child_process(ei);
		// exit(g_info.exit_code);
	}
	return (pid);
}
