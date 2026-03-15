/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :::      ::::::::   */
/*                                                    +:+ +:+             */
/*   By: opencode <opencode@student.42.fr>          +#+  +:+       */
/*                                                +#+#+#+#+#+   +#++#++#+     */
/*   Created: 2026/03/15 by opencode              #+#    #+#               */
/*   Updated: 2026/03/15 by opencode              ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_io(t_io *io)
{
	t_io	*tmp;

	while (io)
	{
		tmp = io;
		io = io->next;
		if (tmp->path)
			free(tmp->path);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			free(tmp->args);
		}
		if (tmp->path)
			free(tmp->path);
		if (tmp->io_list)
			free_io(tmp->io_list);
		free(tmp);
	}
}
