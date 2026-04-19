/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:15:34 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/19 16:01:31 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BUILT_IN_H
# define EXECUTE_BUILT_IN_H

# include "minishell.h"
# include "executor/execute.h"

int		execute_builtin_cmd_in_parent_process(
			t_exec_info *ei, t_minishell *sh);
void	execute_builtin_cmd_in_child_process(t_exec_info *ei, t_minishell *sh);

#endif
