/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:35:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/12 10:04:09 by obutolin         ###   ########.fr       */
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
	signal(SIGINT, SIG_DFL);
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

/* Return <exit_code> */
static int	execute_cmd_in_child_process(t_exec_info *ei)
{
	int	id;
	int	status;

	id = fork();
	if (id == 0)
		exit(external_child_process(ei));
	else
	{
		close_in_parent(ei);
		waitpid(id, &status, 0);
		status = status >> 8;
		if (g_info.sigint)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (EXIT_CTRL_C);
		}
		return (status);
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
	g_info.exit_code = execute_cmd_in_child_process(ei);
	return (1);
}
