/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:17:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/19 09:17:38 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Return
		0 = we need to stop program (error)
		1 = OK, continue
*/
int	lexer(t_memory_info **memory_head, t_token **token_head)
{
	char	*line;

	line = NULL;
	*token_head = NULL;
	line = readline("Minishell> ");
	if (line == NULL)
		return (0);
	add_new_memory_link_for_control(memory_head, line);
	if (!line_lexer(memory_head, token_head, line))
		return (0);
	if (command_with_error(*token_head))
	{
		free_memory_links(*memory_head);
		return (1);
	}
	printf("before chack need new line \n");
	if (need_next_line(*token_head))
	{
		printf("need new line\n");
	}
	print_token_list(*token_head);
	add_history(line);
	return (1);
}
