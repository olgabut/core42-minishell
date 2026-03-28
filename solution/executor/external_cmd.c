/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:35:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/28 18:35:22 by dprikhod         ###   ########.fr       */
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

static void	execute_cmd_in_child_process(
	t_cmd *cmd, char **env_array, int *status)
{
	int		id;

	id = fork();
	if (id == 0)
	{
 		execve(cmd->path, cmd->args, env_array);
		print_cmd_error(cmd->args[0], NULL);
		exit(EXIT_CMD_NOT_FOUND);
	}
	else
	{
		waitpid(id, status, 0);
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
	if (cmd->path == NULL)
	{
		print_cmd_error(cmd->args[0], "command not found");
		sh->exit_code = EXIT_CMD_NOT_FOUND;
		return (1);
	}
	execute_cmd_in_child_process(cmd, env_array, &sh->exit_code);
	return (1);
}
