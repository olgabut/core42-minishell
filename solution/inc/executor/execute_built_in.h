/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:15:34 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/07 17:04:03 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BUILT_IN_H
# define EXECUTE_BUILT_IN_H

# include "minishell.h"
# include "executor/execute.h"

int		execute_built_in_parent(t_exec_info *ei, t_minishell *sh);

void	execute_built_in_child(t_exec_info *ei, t_minishell *sh);

#endif
