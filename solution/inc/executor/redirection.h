/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 10:39:02 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/30 18:30:20 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "minishell.h"
#include "executor/execute.h"

t_exec_info	*exec_info_init(char **argv, t_env *env_list, t_memory_info **head);

int	create_pipefd(t_exec_info *ei);

/*
* Opens file with name `cmd->io_list->path` with read-only or write-only
* permissions (and other flags), depending on `cmd->io_list->type`. Sets
* created file descriptor to `ei->outfd` or `ei->infd` to redirect output or input
* accordingly.
*
*
* For `TOKEN_HERE_DOC` creates pipe, writes `cmd->io_list->path` to the 
* write-end and sets `ei->infd` to read-end.
*/
int	prepare_redirs_before_exec(t_cmd *cmd, t_exec_info *ei);

#endif
