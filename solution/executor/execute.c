/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:34:55 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/26 10:11:16 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_pipeline(t_minishell *sh)
{
	(void)*sh;
	return (1);
}

static int	execute_single_cmd(t_minishell *sh)
{
	if (sh->cmd_list && sh->cmd_list->args && sh->cmd_list->args[0]
		&& is_built_in_cmd(sh->cmd_list->args[0]))
		return (execute_built_in_cmd(sh->cmd_list, sh));
	return (printf("EXECUTE USING FORK\n"), 1);
	// return (1);
}

/*
	Executes commands (sh->cmd_list)
	Return	1-ok
			0-error
*/
int	execute(t_minishell *sh)
{
	(void)*sh;

	if (sh->cmd_list->next)
		return (execute_pipeline(sh));
	else
		return (execute_single_cmd(sh));
}