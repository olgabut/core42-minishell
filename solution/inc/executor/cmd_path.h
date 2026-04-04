/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:04:18 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/04 12:37:34 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PATH_H
# define CMD_PATH_H

# include "minishell.h"
# include "executor/execute.h"

void	find_cmd_path(t_exec_info *ei, t_env *env, t_memory_info **head);

#endif
