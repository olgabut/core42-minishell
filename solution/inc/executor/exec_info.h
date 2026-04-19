/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_info.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:41:43 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/19 15:38:10 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef EXEC_INFO_H
# define EXEC_INFO_H

int	get_cmd_count_by_ei(t_exec_info *ei);
void	add_new_exec_info_to_list(t_exec_info **head, t_exec_info *new_ei);
t_exec_info	*create_exec_info(t_cmd *cmd, t_minishell *sh);
int	prepare_exec_info_list(t_exec_info **ei_head, t_minishell *sh);

#endif