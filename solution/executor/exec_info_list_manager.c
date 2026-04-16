/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_info_list_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:12:04 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/16 23:19:31 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/execute.h"
#include "executor/cmd_path.h"
#include "executor/redirection.h"

static int count_arg(t_list *arg)
{
	int i;
	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

char **get_arg_array(t_memory_info **memory, t_list *arg)
{
	int		count;
	char	**arg_array;
	int		i;

	count = count_arg(arg);
	arg_array = ft_calloc(count + 1, sizeof(char *));
	if (!arg_array)
		return (NULL);
	add_new_memory_link_for_control(memory, arg_array);
	i = 0;
	while (i < count)
	{
		arg_array[i] = ft_strdup(arg->content);
		add_new_memory_link_for_control(memory, arg_array[i]);
		arg = arg->next;
		i++;
	}
	arg_array[i] = NULL;
	return (arg_array);
}

/*
	Create exec_info based on cmd and env from sh->env_list
*/
t_exec_info *create_exec_info(t_cmd *cmd, t_minishell *sh)
{
	t_exec_info	*new_ei;

	if (!cmd || !cmd->args_list)
		return (NULL);
	new_ei = ft_calloc(1, sizeof(t_exec_info));
	if (!add_new_memory_link_for_control(&sh->memory_head, new_ei))
		return (NULL);
	new_ei->next = NULL;
	new_ei->argv = get_arg_array(&sh->memory_head, cmd->args_list);
	if (!new_ei->argv)
		return (NULL);
	new_ei->envp = get_env_array(&sh->memory_head, sh->env_list);
	if (!new_ei->envp)
		return (NULL);
	new_ei->path = find_cmd_path(cmd->args_list->content, sh->env_list);
	if (new_ei->path)
		add_new_memory_link_for_control(&sh->memory_head, new_ei->path);
	new_ei->infd = STDIN_FILENO;
	new_ei->outfd = STDOUT_FILENO;
	new_ei->is_built_in = is_built_in_cmd(cmd->args_list->content);
	new_ei->pipefd = -1;
	return (new_ei);
}

void	add_new_exec_info_to_list(t_exec_info **head, t_exec_info *new_ei)
{
	t_exec_info *ei;

	if (new_ei == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_ei;
		return ;
	}
	ei = *head;
	while (ei->next != NULL)
		ei = ei->next;
	ei->next = new_ei;
}

int get_cmd_count(t_cmd *cmd)
{
	int count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int get_cmd_count_by_ei(t_exec_info *ei)
{
	int count;

	count = 0;
	while (ei)
	{
		count++;
		ei = ei->next;
	}
	return(count);
}

/*
	Return
		0 - error
		1 - ok
*/
int prepare_exec_info_list(t_exec_info **ei_head, t_minishell *sh)
{
	t_exec_info	*new_ei;
	t_cmd		*cmd;
	int			prev_read_fd;
	int cmd_count;
	int	fd_pipe[2];

	if (!sh || !sh->cmd_list)
		return (0);
	cmd = sh->cmd_list;
	*ei_head = NULL;
	cmd_count = get_cmd_count(sh->cmd_list);
	prev_read_fd = -1;
	while (cmd)
	{
		new_ei = create_exec_info(cmd, sh);
		if (!new_ei)
			return (0);
		if (!prepare_redirections(new_ei, cmd->io_list))
			return (0);
		if (cmd_count > 1)
		{
			if (prev_read_fd != -1 && new_ei->infd == STDIN_FILENO)
			{
				new_ei->infd = prev_read_fd;
				prev_read_fd = -1;
			}
			if (cmd->next)
			{
				if (pipe(fd_pipe) < 0)
					return (-1);
				if (new_ei->outfd != STDOUT_FILENO)
					new_ei->outfd = fd_pipe[1];
				prev_read_fd = fd_pipe[0];
			}
		}
		add_new_exec_info_to_list(ei_head, new_ei);
		cmd = cmd->next;
	}
	return (1);
}
