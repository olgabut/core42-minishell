/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:13:43 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/14 13:09:44 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "executor/apply_redirection.h"
#include "executor/execute_built_in.h"

static void	choose_built_in(t_exec_info *ei, t_minishell *sh)
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
		g_info.exit_code = built_in_exit(ei->argv, &need_exit);
}
int	execute_built_in_parent(t_exec_info *ei, t_minishell *sh)
{
	if (redirect_in_parent(sh, ei))
		return (-2);
	if (!ei->argv || !ei->argv[0])
		return (-1);
	choose_built_in(ei, sh);
	if (restore_stdio(sh) < 0)
		return (errno);
	return (g_info.exit_code);
}

void	execute_built_in_child(t_exec_info *ei, t_minishell *sh)
{
	if (redirect_simple(ei))
	{
		ft_fprintf(STDERR_FILENO, "ms: %s\n", strerror(errno));
		exit (-1);
	}
	if (!ei->argv || !ei->argv[0])
		exit (-1);
	choose_built_in(ei, sh);
	exit(g_info.exit_code);
}
