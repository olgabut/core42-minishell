/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_info_list_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:12:04 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/22 12:33:21 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/execute.h"
#include "executor/cmd_path.h"

static char	**get_arg_array(t_memory_info **memory, t_list *arg)
{
	int		count;
	char	**arg_array;
	int		i;

	count = ft_lstsize(arg);
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
t_exec_info	*create_exec_info(t_cmd *cmd, t_minishell *sh)
{
	t_exec_info	*new_ei;

	if (!cmd || !cmd->args_list)
		return (NULL);
	new_ei = ft_calloc(1, sizeof(t_exec_info));
	if (!add_new_memory_link_for_control(&sh->memory_head, new_ei))
		return (NULL);
	new_ei->next = NULL;
	new_ei->prev = NULL;
	new_ei->is_error = false;
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
	new_ei->pipe_infd = -1;
	new_ei->pipe_outfd = -1;
	new_ei->is_built_in = is_built_in_cmd(cmd->args_list->content);
	return (new_ei);
}

void	add_new_exec_info_to_list(t_exec_info **head, t_exec_info *new_ei)
{
	t_exec_info	*ei;

	if (new_ei == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_ei;
		new_ei->prev = NULL;
		return ;
	}
	ei = *head;
	while (ei->next != NULL)
		ei = ei->next;
	ei->next = new_ei;
	new_ei->prev = ei;
}

int	get_cmd_count_by_ei(t_exec_info *ei)
{
	int	count;

	count = 0;
	while (ei)
	{
		count++;
		ei = ei->next;
	}
	return (count);
}
