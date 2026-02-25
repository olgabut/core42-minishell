/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:37:11 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/25 08:44:09 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
int	built_in_cd(char **argv)
{
	if (!argv || !argv[0] || ft_strcmp(argv[0], "cd") != 0)
		return (-1);
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}