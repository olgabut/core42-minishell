/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:37:11 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/04 11:29:43 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_directory(t_env **env, char *new_dir, bool print_dir)
{
	char	*cwd;
	char	*error;

	error = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (print_cmd_error("cd", "error", EXIT_FAILURE));
	if (chdir(new_dir) != 0)
	{
		print_cmd_error("cd", new_dir, EXIT_FAILURE);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(error);
		free(cwd);
		return (EXIT_FAILURE);
	}
	if (print_dir)
		ft_fprintf(STDOUT_FILENO, "%s\n", new_dir);
	if (!update_env(env, "OLDPWD", cwd) || !update_env(env, "PWD", new_dir))
	{
		free(cwd);
		return (print_cmd_error("cd", "error", EXIT_FAILURE));
	}
	free(cwd);
	return (EXIT_SUCCESS);
}

static int	change_to_home_directory(t_env **env)
{
	char	*home_dir;

	home_dir = NULL;
	if (!get_env_exist(*env, "HOME", &home_dir) || !home_dir)
		return (print_cmd_error("cd", "HOME not set", EXIT_FAILURE));
	return (change_directory(env, home_dir, false));
}

static int	change_to_old_directory(t_env **env)
{
	char	*old_dir;

	old_dir = NULL;
	if (!get_env_exist(*env, "OLDPWD", &old_dir) || !old_dir)
		return (print_cmd_error("cd", "OLDPWD not set", EXIT_FAILURE));
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
	if (!argv || !argv[0] || ft_strcmp(argv[0], "cd") != 0)
		return (-1);
	if (argv[2])
		return (print_cmd_error("cd", "too many arguments", EXIT_FAILURE));
	if (!argv[1])
		return (change_to_home_directory(env));
	if (ft_strcmp(argv[1], "-") == 0)
		return (change_to_old_directory(env));
	change_directory(env, argv[1], false);
	return (EXIT_SUCCESS);
}
