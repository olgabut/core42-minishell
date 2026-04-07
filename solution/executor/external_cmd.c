/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:35:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/07 17:28:23 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include "executor/redirection.h"
#include "executor/apply_redirection.h"
#include "executor/cmd_path.h"

/*
	execve(pathname, argv, envp)
		pathname - The pathname of the command to execute
		argv - The arguments to pass to the new program
		envp - The environment list
*/
void	external_child(t_exec_info *ei)
{
		if (redirect_simple(ei) < 0)
			exit(errno);
		if (execve(ei->path, ei->argv, ei->envp) == -1)
		{
			msh_error(ei->argv[0], NULL);
			if (errno == ENOENT)
				exit(EXIT_CMD_NOT_FOUND);
			else if (errno == EACCES)
				exit (EXIT_PERMISSION_DENIED);
			else
				exit (EXIT_FAILURE);
		}
		else
			exit(EXIT_SUCCESS);
}

/* Return <exit_code> */
static int	execute_cmd_in_child_process(t_exec_info *ei)
{
	int	id;
	int	status;

	id = fork();
	if (id == 0)
		external_child(ei);
	close_in_parent(ei);
	waitpid(id, &status, 0);
	status = status >> 8;
	return (status);
}

/*
	Return	1  - ok
			0  - error

*/
int	execute_external_cmd(t_cmd *cmd, t_minishell *sh)
{
	t_exec_info	*ei;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	ei = exec_info_init(cmd->args, sh->env_list, &sh->memory_head);
	if (cmd->io_list)
		if (prepare_redirs_before_exec(cmd, ei) < 0)
			return (ft_fprintf(STDERR_FILENO, "ms: %s\n", strerror(errno)));
	find_cmd_path(ei, sh->env_list, &sh->memory_head);
	if (!ei->path)
	{
		msh_error(cmd->args[0], "command not found");
		sh->exit_code = EXIT_CMD_NOT_FOUND;
		return (1);
	}
	sh->exit_code = execute_cmd_in_child_process(ei);
	return (1);
}
