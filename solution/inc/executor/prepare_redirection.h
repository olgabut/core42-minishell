/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirection.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 10:39:02 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/19 12:19:30 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPARE_REDIRECTION_H
#define PREPARE_REDIRECTION_H

#include "minishell.h"

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
int	prepare_redirections(t_exec_info *ei, t_io *io_head);
int prepare_pipe_fd(t_exec_info *ei);

#endif
