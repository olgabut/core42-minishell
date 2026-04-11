/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:12:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/10 02:11:04 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"
#include "executor/apply_redirection.h"

size_t	count_argv(char **argv)
{
	size_t	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
	{
		i++;
	}
	return (i);
}

/*
	Return
		true- yes, this is a supported built-in command
		false- no
*/
bool	is_built_in_cmd(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	return (ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "unset") == 0);
}

/*
# RETURN VALUE

1  - need_exit
0  - ok
-1 - it's not built-in command
-2 - error occured during redirections
*/
int	execute_built_in_cmd(t_cmd *cmd, t_minishell *sh)
{
	bool	need_exit;

	if (cmd->io_list)
		if (redirect_built_in(cmd, sh) < 0)
			return (-2);
	if (!cmd->args || !cmd->args[0])
		return (-1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (sh->exit_code = built_in_echo(cmd->args));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (sh->exit_code = built_in_cd(cmd->args, &sh->env_list));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (sh->exit_code = built_in_pwd(cmd->args));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (sh->exit_code = built_in_export(cmd->args, &sh->env_list));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (sh->exit_code = built_in_unset(cmd->args, &sh->env_list));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (sh->exit_code = built_in_env(cmd->args, sh->env_list));
	need_exit = false;
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		sh->exit_code = built_in_exit(cmd->args, sh->exit_code, &need_exit);
		return (need_exit);
	}
	return (-1);
}
