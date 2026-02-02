/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:17:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/02 12:22:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	Function add_new_line rewrites
	line = line + '\n' + new_line
	Return 1 - ok
		0 - malloc errors
*/
int add_new_line(t_memory_info **memory_head, char **line, char *new_line)
{
	char *new_long_line;

	if (new_line == NULL)
		return (0);
	add_new_memory_link_for_control(memory_head, new_line);
	new_long_line = ft_straddchar(*line, '\n');
	if (new_long_line == NULL)
		return (0);
	add_new_memory_link_for_control(memory_head, new_long_line);
	new_long_line = ft_strjoin(new_long_line, new_line);
	if (new_long_line == NULL)
		return (0);
	free_memory_links(*memory_head);
	*line = new_long_line;
	return (1);
}

/*
	Return
		0 = we need to stop program (readline == NULL or malloc errors)
		1 = OK, continue
*/
int	lexer(t_memory_info **memory_head, t_token **token_head)
{
	char	*line;
	char	*new_line;

	line = NULL;
	line = readline("Minishell> ");
	if (line == NULL)
		return (0);
	add_new_memory_link_for_control(memory_head, line);
	if (line[0] == '\0')
		return (1);
	if (!line_lexer(memory_head, token_head, line))
		return (0);
	// while (need_next_line(*token_head))
	// {
	// 	new_line = readline("> ");
	// 	if (!add_new_line(memory_head, &line, new_line))
	// 		return (0);
	// 	*memory_head = NULL;
	// 	*token_head = NULL;
	// 	add_new_memory_link_for_control(memory_head, line);
	// 	printf("long line = '%s'\n", line);
	// 	if (!line_lexer(memory_head, token_head, line))
	// 		return (0);
	// }


	// if (command_with_error(*token_head))
	// {
	// 	free_memory_links(*memory_head);
	// 	return (1);
	// }
	
	print_token_list(*token_head);
	add_history(line);
	return (1);
}
