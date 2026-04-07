/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:20:49 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/07 17:23:49 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_CMD_H
# define EXTERNAL_CMD_H
# include "executor/execute.h"
# include "minishell.h"

void	external_child(t_exec_info *ei);
int		execute_external_cmd(t_cmd *cmd, t_minishell *sh);

#endif
