/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirection.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:43:04 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/17 23:32:59 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLY_REDIRECTION_H
# define APPLY_REDIRECTION_H

# include "executor/execute.h"
# include "minishell.h"

/*
 *	# DESCRIPTION
 *	This function calls `dup2()` to redirect input and/or output to those
 *	specified in `ei->infd` and `ei->outfd` in case that it differs from
 *	standard ones.
 *
 *	# RETURN VALUE
 *	On success, retruns 0. On failure returns -1.
 */
int	redirect_infd_in_child(t_exec_info *ei);
int	redirect_outfd_in_child(t_exec_info *ei);

/*
 *	# DESCRIPTION
 *	This function calls `dup2()` to redirect input and/or output to those
 *	specified in `ei->infd` and `ei->outfd` in case that it differs from
 *	standard ones. Before redirection it saves standard ones to
 *	`sh->stdin_backup` and/or `sh->stdout_backup`
 *
 *	# RETURN VALUE
 *	On success, retruns 0. On failure returns -1.
 */
int	redirect_in_parent(t_minishell *sh, t_exec_info *ei);

/*
 *	# DESCRIPTION
 *	This function calls `dup2()` to restore redirection caused by
 *	`redirect_in_parent` function call.
 *
 *	# RETURN VALUE
 *	On success, retruns 0. On failure returns -1.
 */
int	restore_stdio_from_backup(t_minishell *sh);
/*
 *	# DESCRIPTION
 *	This function is meant to be called, when built-in command should be 
 *	executed in parent process. It is higher level function to redirect I/O if
 *	needed and set backup file descriptors inside `sh` structure to be restored
 *	later. 
 *
 *
 *	# RETURN VALUE
 *	On success, retruns 0. On failure returns -1.
 */
// int	redirect_built_in(t_cmd *cmd, t_minishell *sh);

/*
 *	# DESCRIPTION
 *	Closes `ei->outfd` and `ei->infd` if differs from standard I/O
 *
 *
 *	# RETURN VALUE
 *	On success, retruns 0. On failure returns -1.
 */
int close_fd_in_parent(t_exec_info *ei);
int close_all_pipes(t_exec_info *ei_head);

#endif
