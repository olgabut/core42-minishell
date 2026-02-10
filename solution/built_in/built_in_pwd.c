/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:53:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/10 11:27:48 by obutolin         ###   ########.fr       */
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

	return status
		0 - successful completion     or    it's not pwd command
		1 - error
 */
int	built_in_pwd(char **argv)
{
	char	*cwd;
	int		fd;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "pwd") != 0)
		return (0);
	fd = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd = 2;
		ft_putstr_fd("error: pwd", fd);
		return (FAILURE);
	}
	ft_putstr_fd(cwd, fd);
	ft_putchar_fd('\n', fd);
	free(cwd);
	return (SUCCESS);
}
