/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:53:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/20 21:55:09 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	built in PWD command (print woring directory)
	The pwd command shows you the full path of the folder you're currently in.

	pwd [flag(s)]

	flags:
	-L (IGNORED in minishell) Display the logical current working directory.
	-P: (IGNORED in minishell) Display the physical current working directory.

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
 */
int	built_in_pwd(char **argv)
{
	char	*cwd;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "pwd") != 0)
		return (-1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd: error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
