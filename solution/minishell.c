/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/22 11:18:10 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_memory_info	*memory_head;
	t_token			*token_head;

	signals();
	while (1)
	{
		memory_head = NULL;
		token_head = NULL;
		if (!lexer(&memory_head, &token_head))
		{
			printf("ctrl+D\n");
			break ;
		}
		if (token_head)
		{
			printf("Next step PARSING\n");
		}

		// if (pid == 0)
		// {
		// 	signal(SIGINT, SIG_DFL);
		// 	signal(SIGQUIT, SIG_DFL);
		// 	execve(...);
		// }
		free_memory_links(memory_head);
	}
	free_memory_links(memory_head);
	return (0);
}
