/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:35:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/16 19:58:38 by obutolin         ###   ########.fr       */
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

	waitpid status bits meaning
		0-6    signal number that caused child to exit,
		       or 0177 if child stopped / continued
		       or zero if child exited without a signal
		7     1 if core dumped, else 0
		8-15   low 8 bits of value passed to _exit/exit or returned by main,
		       or signal that caused child to stop/continue
*/
void	execute_external_in_child(t_exec_info *ei)
{
	if (redirect_simple(ei) < 0)
		exit(errno);
	if (execve(ei->path, ei->argv, ei->envp) == -1)
	{
		msh_error(ei->argv[0], NULL);
		if (errno == ENOENT)
			exit(EXIT_CMD_NOT_FOUND);
		else if (errno == EACCES)
			exit(EXIT_PERMISSION_DENIED);
		else
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
