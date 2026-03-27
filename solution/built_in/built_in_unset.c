/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:37:58 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/26 10:23:32 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"

/*
	built in UNSET command
	The unset command removes or clears an environment variables
	temporarily or permanently.

	unset VARIABLE_NAME

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
 */
int	built_in_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_env_node(env, argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
