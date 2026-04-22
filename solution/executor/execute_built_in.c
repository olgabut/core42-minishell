/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:13:43 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/22 13:19:49 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "executor/close_fd.h"
#include "executor/redirect.h"

/*
	Return	1  - ok
			0  - need_exit
*/
static int	choose_built_in(t_exec_info *ei, t_minishell *sh)
{
	bool	need_exit;

	if (ft_strcmp(ei->argv[0], "echo") == 0)
		g_info.exit_code = built_in_echo(ei->argv);
	if (ft_strcmp(ei->argv[0], "cd") == 0)
		g_info.exit_code = built_in_cd(ei->argv, &sh->env_list);
	if (ft_strcmp(ei->argv[0], "pwd") == 0)
		g_info.exit_code = built_in_pwd(ei->argv);
	if (ft_strcmp(ei->argv[0], "export") == 0)
		g_info.exit_code = built_in_export(ei->argv, &sh->env_list);
	if (ft_strcmp(ei->argv[0], "unset") == 0)
		g_info.exit_code = built_in_unset(ei->argv, &sh->env_list);
	if (ft_strcmp(ei->argv[0], "env") == 0)
		g_info.exit_code = built_in_env(ei->argv, sh->env_list);
	need_exit = false;
	if (ft_strcmp(ei->argv[0], "exit") == 0)
	{
		g_info.exit_code = built_in_exit(ei->argv, &need_exit);
		return (!need_exit);
	}
	return (true);
}

int	execute_builtin_cmd_in_parent_process(t_exec_info *ei, t_minishell *sh)
{
	int	res;

	if (!ei->argv || !ei->argv[0])
		return (1);
	if (ei->is_error)
	{
		g_info.exit_code = EXIT_FAILURE;
		return (1);
	}
	if (redirect_in_parent(sh, ei))
		return (1);
	res = choose_built_in(ei, sh);
	close_fd_in_parent(ei);
	if (restore_stdio_from_backup(sh) < 0)
		msh_error("redirection", NULL);
	return (res);
}

void	execute_builtin_cmd_in_child_process(t_exec_info *ei, t_minishell *sh)
{
	if (!ei || !ei->argv || !ei->argv[0])
		exit (-1);
	choose_built_in(ei, sh);
	exit(g_info.exit_code);
}
