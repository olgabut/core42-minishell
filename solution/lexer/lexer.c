/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:17:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/21 14:51:14 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Return
		0 = we need to stop program (readline == NULL or malloc errors)
		1 = OK, continue
*/
int	lexer(t_memory_info **memory_head, t_token **token_head)
{
	char	*line;

	*memory_head = NULL;
	line = NULL;
	*token_head = NULL;
	line = readline("Minishell> ");
	printf("line = '%s'\n", line);
	if (line == NULL)
		return (0);
	if (!line_lexer(memory_head, token_head, line))
	{
		free(line);
		return (0);
	}
	// if (command_with_error(*token_head))
	// {
	// 	free_memory_links(*memory_head);
	// 	return (1);
	// }
	// if (need_next_line(*token_head))
	// {
	// 	printf("need new line\n");
	// }
	print_token_list(*token_head);
	add_history(line);
	free(line);
	return (1);
}
