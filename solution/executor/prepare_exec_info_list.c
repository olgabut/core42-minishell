/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec_info_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:11:48 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/19 13:44:41 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/exec_info.h"
#include "executor/cmd_path.h"
#include "executor/prepare_redirection.h"

/*
	Return
		0 - error
		1 - ok
*/
int	prepare_exec_info_list(t_exec_info **ei_head, t_minishell *sh)
{
	t_exec_info	*new_ei;
	t_cmd		*cmd;

	if (!sh || !sh->cmd_list)
		return (0);
	*ei_head = NULL;
	cmd = sh->cmd_list;
	while (cmd)
	{
		new_ei = create_exec_info(cmd, sh);
		if (!new_ei)
			return (0);
		add_new_exec_info_to_list(ei_head, new_ei);
		if (!check_cmd_path(new_ei))
			return (0);
		if (!prepare_redirections(new_ei, cmd->io_list))
			return (0);
		if (!prepare_pipe_fd(new_ei))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
