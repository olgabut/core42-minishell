/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:16:12 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/19 16:05:37 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_FD_H
# define CLOSE_FD_H

# include "minishell.h"

int	close_fd_in_parent(t_exec_info *ei);
int	close_all_pipes(t_exec_info *ei_head);

#endif
