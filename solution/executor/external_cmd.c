/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:35:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/06 13:59:37 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/*
	execve(pathname, argv, envp)
		pathname - The pathname of the command to execute
		argv - The arguments to pass to the new program
		envp - The environment list
*/

/* Return <exit_code> */
static int	execute_cmd_in_child_process(
	t_cmd *cmd, char **env_array)
{
	int	id;
	int	status;

	id = fork();
	if (id == 0)
	{
		if (execve(cmd->path, cmd->args, env_array) == -1)
		{
			msh_error(cmd->args[0], NULL);
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
	else
	{
		waitpid(id, &status, 0);
		status = status >> 8;
		return (status);
	}
}

/*
	Return	1  - ok
			0  - error
*/
int	execute_external_cmd(t_cmd *cmd, t_minishell *sh)
{
	char	**env_array;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	env_array = get_env_array(&sh->memory_head, sh->env_list);
	find_cmd_path(cmd, sh);
	if (!cmd->path)
	{
		msh_error(cmd->args[0], "command not found");
		sh->exit_code = EXIT_CMD_NOT_FOUND;
		return (1);
	}
	add_new_memory_link_for_control(&sh->memory_head, cmd->path);
	sh->exit_code = execute_cmd_in_child_process(cmd, env_array);
	return (1);
}
