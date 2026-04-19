/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:37:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/19 16:05:53 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

int	prepare_exec_info_list(t_exec_info **ei_head, t_minishell *sh);
int	get_cmd_count_by_ei(t_exec_info *ei);

#endif
