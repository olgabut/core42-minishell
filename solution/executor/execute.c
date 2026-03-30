/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:34:55 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/30 20:03:00 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/redirection.h"
#include "minishell.h"

/*
 * # RETURN VALUE
 * on success returns 0, on failure returns error code:
 * - 12 in case of `malloc()` failure;
 * - `errno` that set by `open()` or `pipe()` on its failure.
 */
static int	execute_pipeline(t_minishell *sh)
{
	t_cmd		*cur_cmd;
	int			prev_read_fd;
	t_exec_info	*ei;

	prev_read_fd = -1;
	cur_cmd = sh->cmd_list;
	while (cur_cmd)
	{
		ei = exec_info_init(cur_cmd->args, sh->env_list, &sh->memory_head);
		if (!ei)
			return (ENOMEM);
		if (prev_read_fd != -1)
		{
			ei->infd = prev_read_fd;
			prev_read_fd = -1;
		}
		if (cur_cmd->next)
		{
			prev_read_fd = create_pipefd(ei);
			if (prev_read_fd == -1)
				return (errno);
		}
		if (prepare_redirs_before_exec(cur_cmd, ei) != 0)
			return (errno);
		apply_execution(&sh->memory_head, ei, &sh->exit_code);
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

static int	execute_single_cmd(t_minishell *sh)
{
	if (sh->cmd_list && sh->cmd_list->args && sh->cmd_list->args[0]
		&& is_built_in_cmd(sh->cmd_list->args[0]))
		return (execute_built_in_cmd(sh->cmd_list, sh));
	else
		return (execute_external_cmd(sh->cmd_list, sh));
}

/*
	Executes commands (sh->cmd_list)
	Return	1-ok
			0-error
*/
int	execute(t_minishell *sh)
{
	if (!sh || !sh->cmd_list || !sh->cmd_list->args)
		return (1);
	if (sh->cmd_list->next)
		return (execute_pipeline(sh));
	else
		return (execute_single_cmd(sh));
}
