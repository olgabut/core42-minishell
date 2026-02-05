/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:40:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/04 18:44:05 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Return
		0 = we need to stop program (readline == NULL or malloc errors)
		1 = OK, continue
*/
int	heredoc_handler(t_memory_info **memory_head, t_cmd *cmd)
{
	char	*line;

	if (!cmd->heredoc)
		return (1);
	if (!create_pipe(fd))
		retrun (0);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !add_new_line(memory_head, &line, line))
			return (0);
		if (ft_strcmp(line, cmd->heredoc->delimiter) == 0)
		{
			free(line);
			break;
		}
	}
	return (1);
}
