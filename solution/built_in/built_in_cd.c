/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:37:11 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/26 09:47:46 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"

static int	change_directory(t_env **env, char *new_dir, bool print_dir)
{
	char	*prev_cwd;
	char	*cwd;
	char	*error;

	error = NULL;
	prev_cwd = getcwd(NULL, 0);
	if (!prev_cwd)
		return (print_cmd_error("cd", "error"), EXIT_FAILURE);
	if (chdir(new_dir) != 0)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: ", new_dir);
		perror(error);
		return (free(prev_cwd), EXIT_FAILURE);
	}
	if (print_dir)
		ft_fprintf(STDOUT_FILENO, "%s\n", new_dir);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(prev_cwd), print_cmd_error("cd", "error"), EXIT_FAILURE);
	if (!update_env(env, "OLDPWD", prev_cwd, false))
		return (free(prev_cwd), print_cmd_error("cd", "error"), EXIT_FAILURE);
	free(prev_cwd);
	if (!update_env(env, "PWD", cwd, false))
		return (free(cwd), print_cmd_error("cd", "error"), EXIT_FAILURE);
	return (free(cwd), EXIT_SUCCESS);
}

static int	change_to_home_directory(t_env **env)
{
	char	*home_dir;

	home_dir = get_env_value(*env, "HOME");
	if (!home_dir)
		return (print_cmd_error("cd", "HOME not set"), EXIT_FAILURE);
	return (change_directory(env, home_dir, false));
}

static int	change_to_old_directory(t_env **env)
{
	char	*old_dir;

	old_dir = get_env_value(*env, "OLDPWD");
	if (!old_dir)
		return (print_cmd_error("cd", "OLDPWD not set"), EXIT_FAILURE);
	return (change_directory(env, old_dir, true));
}

/*
	built in CD command
	minishell: cd with only a relative or absolute path

	The cd command supports several useful options for navigating directories:
		cd ..: Move up one directory level
		cd ~: Change to the home directory
		cd -: Switch to the previous directory
		cd /: Change to the root directory

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
*/
int	built_in_cd(char **argv, t_env **env)
{
	if (argv[2])
		return (print_cmd_error("cd", "too many arguments"), EXIT_FAILURE);
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		return (change_to_home_directory(env));
	if (ft_strcmp(argv[1], "-") == 0)
		return (change_to_old_directory(env));
	change_directory(env, argv[1], false);
	return (EXIT_SUCCESS);
}
