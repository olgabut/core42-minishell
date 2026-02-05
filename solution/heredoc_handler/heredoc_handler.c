/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:40:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/05 11:35:12 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 heredoc_handler steps:
	- Read user input line by line (Stop when the delimiter is typed exactly)
	- Store the input somewhere (usually a pipe or temp file)
	- Redirect the command’s STDIN to that stored input
	- Handle CTRL+C correctly
	Return
		0 = we need to stop program (readline == NULL or malloc errors)
		1 = OK, continue
*/
int	heredoc_handler(t_memory_info **memory_head, t_cmd *cmd)
{
	char	*line;
	int		fd[2];

	if (!cmd->redir || cmd->redir->type != HEREDOC)
		return (1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !add_new_line(memory_head, &line, line))
			return (0);
		if (ft_strcmp(line, cmd->redir->delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	return (1);
}
