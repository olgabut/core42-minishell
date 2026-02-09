/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/09 11:56:13 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_memory_info	*memory_head;
	t_token			*token_head;

	while (1)
	{
		memory_head = NULL;
		token_head = NULL;
		if (!lexer(&memory_head, &token_head))
			break ;
		if (token_head)
		{
			print_token_list(token_head);
			printf("Next step PARSING\n");
		}
		free_memory_links(&memory_head);
	}
	free_memory_links(&memory_head);
	return (0);
}
