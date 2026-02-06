/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:53:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/06 15:11:50 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	pwd command builtin (print woring directory)
	The pwd command shows you the full path of the folder you're currently in.

	pwd [flag(s)]

	flags:
	-L (IGNORED in minishell) Display the logical current working directory.
	-P: (IGNORED in minishell) Display the physical current working directory.

	return
		0 - successful completion     or    it's not pwd command
		1 - error
 */
int	pwd_builtin(char **argv)
{
	char	*cwd;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "pwd") != 0)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
