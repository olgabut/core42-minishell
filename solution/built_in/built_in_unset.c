/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:37:58 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/12 17:12:44 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!argv || !argv[0] || ft_strcmp(argv[0], "unset") != 0)
		return (-1);
}