/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:08:44 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/19 15:35:44 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_all_pipes(t_exec_info *ei_head)
{
	while (ei_head)
	{
		if (ei_head->pipe_infd != -1)
		{
			close(ei_head->pipe_infd);
			// printf("[CLOSE] closing fd=%d\n", ei_head->pipe_infd);
			ei_head->pipe_infd = -1;
		}
		if (ei_head->pipe_outfd != -1)
		{
			close(ei_head->pipe_outfd);
			// printf("[CLOSE] closing fd=%d\n", ei_head->pipe_outfd);
			ei_head->pipe_outfd = -1;
		}
		ei_head = ei_head->next;
	}
	return (0);
}

int	close_fd_in_parent(t_exec_info *ei)
{
	if (ei->infd != STDIN_FILENO)
		if (close(ei->infd) == -1)
			return (-1);
	if (ei->outfd != STDOUT_FILENO)
		if (close(ei->outfd) == -1)
			return (-1);
	if (ei->pipe_infd != -1)
		if (close(ei->pipe_infd) == -1)
			return (-1);
	if (ei->pipe_outfd != -1)
		if (close(ei->pipe_outfd) == -1)
			return (-1);
	return (0);
}
