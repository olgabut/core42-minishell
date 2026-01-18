/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:17:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/18 19:06:48 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



/*
	Return
		0 = we need to stop program (error)
		1 = OK, continue
*/
int	lexer(t_token **token_head)
{
	char	*line;

	line = NULL;
	*token_head = NULL;
	line = readline("Minishell> ");
	if (line == NULL)
		return (0);
	if (!line_lexer(token_head, line))
		return (0);
	if (command_with_error(*token_head))
	{
		// free current (we will be waiting new line from scratch)
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