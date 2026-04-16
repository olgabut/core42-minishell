/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:20:49 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/16 10:21:16 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_CMD_H
# define EXTERNAL_CMD_H
# include "executor/execute.h"
# include "minishell.h"

void	execute_external_in_child(t_exec_info *ei);
/*
* # RETURN VALUE
*
* returns exit code of executed command
*/
int		execute_external_cmd(t_cmd *cmd, t_minishell *sh);

#endif
