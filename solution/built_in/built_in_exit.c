/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:39:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/10 11:53:19 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	built in EXIT command
	The exit command exits the shell with a status of N.

	exit [n]

		where n specifies the exit status code to be returned upon exiting
	the shell.
		If no parameter is provided, the command returns the exit status
	of the last executed command.

	return status
		n % 256 or status of last executed command
*/
// int	built_in_exit(char **argv)
// {
// 	// ft_putstr_fd("exit\n", 1);
// 	// if (!argv[1])
// 	// 	exit(g_last_exit_code);

// 	// if (!is_numeric(argv[1]))
// 	// {
// 	// 	error("numeric argument required");
// 	// 	exit(255);
// 	// }

// 	// if (args[2])
//     // {
//     //     error("too many arguments");
//     //     return 1;
//     // }

//     // exit(ft_atoi(args[1]) % 256);

// 	return (0);
// }
