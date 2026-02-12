/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:46:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/12 17:12:17 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	built in EXPORT command
	The export command allows you to update and propagate the values of
	environment variables to the current session and any spawned child processes,
	ensuring that changes are immediately effective.

	export [-f] [-n] [name[=value] ...] or export -p

	FLAGS (IGNORED in minishell):
	-p To view all exported variables on current shell.
	-f The names are NOT variables, names are  functions
	name[=value] assign value before exporting
	-n Named variables (or functions, with -f) will no longer be exported.

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
 */
int	built_in_export(char **argv, t_env *env)
{
	if (!argv || !argv[0] || ft_strcmp(argv[0], "export") != 0)
		return (-1);
}