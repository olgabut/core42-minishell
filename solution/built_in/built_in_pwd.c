/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:53:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/11 09:04:25 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		fd;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "pwd") != 0)
		return (-1);
	fd = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd = 2;
		ft_putstr_fd("error: pwd", fd);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(cwd, fd);
	ft_putchar_fd('\n', fd);
	free(cwd);
	return (EXIT_SUCCESS);
}
