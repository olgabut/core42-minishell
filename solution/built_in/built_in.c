/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:12:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/27 22:37:46 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"

void	print_cmd_error(char *cmd_name, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (message != NULL)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
		perror("");
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
	if (ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	return (false);
}

/*
	Return	1  - ok
			0  - need_exit
			-1 - it's not built-in command
*/
int	execute_built_in_cmd(t_cmd *cmd, t_minishell *sh)
{
	bool	need_exit;

	if (!cmd->args || !cmd->args[0])
		return (-1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (sh->exit_code = built_in_echo(cmd->args), 1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (sh->exit_code = built_in_cd(cmd->args, &sh->env_list), 1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (sh->exit_code = built_in_pwd(), 1);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (sh->exit_code = built_in_export(cmd->args, &sh->env_list), 1);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (sh->exit_code = built_in_unset(cmd->args, &sh->env_list), 1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (sh->exit_code = built_in_env(cmd->args, sh->env_list), 1);
	need_exit = false;
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		sh->exit_code = built_in_exit(cmd->args, sh->exit_code, &need_exit);
		return (!need_exit);
	}
	return (-1);
}

