/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 10:39:02 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/28 18:59:44 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "minishell.h"
#include "executor/execute.h"

/*
 * Creates pipes for any here_doc needed.
 */
int	**prepare_pipes_for_here_doc(t_cmd *cmd);

/*
* Writes here_doc's 'line' to the pipe and closes both ends of this pipe. Repeat 
* for every here_doc token.
*/
int	fill_here_doc(t_cmd *cmd, int *fd[2]);

/*
* Opens file with name `cmd->io_list->filename` with read-only or write-only
* permissions (and other flags), depending on `cmd->io_list->type`. Pass
* created file descriptor to `dup2` function call to redirect output or input
* accordingly.
*
*
* For `TOKEN_HERE_DOC` redirection is made to `*hd_pipe[0]`, `*hd_pipe[1]` is
* closed as well. 
*
* `int *hd_pipe[2]` is array of "pipes" created by `prepare_pipes_for_here_doc`
* function for every `TOKEN_HERE_DOC` token in `cmd->io_list`
*/
// int	prepare_redirs_before_exec(t_cmd *cmd, int *hd_pipe[2]);
t_exec_info	*prepare_redirs_before_exec(t_cmd *cmd, t_memory_info **head);

#endif
