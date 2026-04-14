/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 22:40:18 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/14 22:26:31 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_MANAGER_H
# define CMD_LIST_MANAGER_H

# include "minishell.h"

t_cmd	*create_empty_cmd(t_minishell *mshell);
void	add_new_cmd(t_cmd **head, t_cmd *new_cmd);
t_cmd	*get_last_cmd(t_cmd **cmd_head);
void	add_io_to_cmd(t_cmd *cmd, t_io *new_io);
t_io	*create_io_node(enum e_token_type redir_type, char *path);

#endif