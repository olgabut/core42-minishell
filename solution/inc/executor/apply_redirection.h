/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirection.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:43:04 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/30 19:55:56 by dprikhod         ###   ########.fr       */
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
int	redirect_simple(t_exec_info *ei);

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
int	restore_stdio(t_minishell *sh);

#endif
