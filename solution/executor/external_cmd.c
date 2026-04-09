/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:35:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/12 10:08:10 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor/apply_redirection.h"
#include "executor/cmd_path.h"
#include "executor/redirection.h"
#include "minishell.h"
#include <sys/wait.h>

/*
	execve(pathname, argv, envp)
		pathname - The pathname of the command to execute
		argv - The arguments to pass to the new program
		envp - The environment list
*/
/* Return exit_code */
static int	external_child_process(t_exec_info *ei)
{
	set_signals_for_child_proces();
	if (redirect_simple(ei) < 0)
		return (errno);
	if (execve(ei->path, ei->argv, ei->envp) == -1)
	{
		msh_error(ei->argv[0], NULL);
		if (errno == ENOENT)
			return (EXIT_CMD_NOT_FOUND);
		else if (errno == EACCES)
			return (EXIT_PERMISSION_DENIED);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

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

/* Return <exit_code> */
static void	execute_cmd_in_child_process(t_exec_info *ei)
{
	int	id;
	int	status;
	int	sig;

	id = fork();
	if (id == 0)
		exit(external_child_process(ei));
	else
	{
		close_in_parent(ei);
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			g_info.exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			g_info.exit_code = 128 + sig;
			if (sig == SIGQUIT)
				write(1, "Quit\n", 5);
			if (sig == SIGINT)
				write(1, "\n", 1);
		}
	}
}

int	execute_external_cmd(t_cmd *cmd, t_minishell *sh)
{
	t_exec_info	*ei;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	ei = exec_info_init(cmd->args, sh->env_list, &sh->memory_head);
	if (cmd->io_list && prepare_redirs_before_exec(cmd, ei) < 0)
		return (msh_error(strerror(errno), NULL), 0);
	find_cmd_path(ei, sh->env_list, &sh->memory_head);
	if (!ei->path)
	{
		msh_error(cmd->args[0], "command not found");
		g_info.exit_code = EXIT_CMD_NOT_FOUND;
		return (1);
	}
	execute_cmd_in_child_process(ei);
	return (1);
}
