/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:33:09 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/14 22:29:37 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_empty_cmd(t_minishell *mshell)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args_list = NULL;
	cmd->io_list = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	add_new_memory_link_for_control(&mshell->memory_head, cmd);
	return (cmd);
}

void	add_new_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*cmd;

	if (new_cmd == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_cmd;
		return ;
	}
	cmd = *head;
	while (cmd->next != NULL)
		cmd = cmd->next;
	cmd->next = new_cmd;
}

t_cmd	*get_last_cmd(t_cmd **cmd_head)
{
	t_cmd	*cmd;

	if (!cmd_head)
		return (NULL);
	if (!*cmd_head)
		return (*cmd_head);
	cmd = *cmd_head;
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	add_io_to_cmd(t_cmd *cmd, t_io *new_io)
{
	t_io	*last;

	if (!cmd || !new_io)
		return ;
	if (!cmd->io_list)
	{
		cmd->io_list = new_io;
		return ;
	}
	last = cmd->io_list;
	while (last->next)
		last = last->next;
	last->next = new_io;
}

t_io	*create_io_node(enum e_token_type redir_type, char *path)
{
	t_io	*io;

	if (!path)
		return (NULL);
	io = malloc(sizeof(t_io));
	if (!io)
		return (NULL);
	io->next = NULL;
	io->path = path;
	io->type = redir_type;
	return (io);
}
