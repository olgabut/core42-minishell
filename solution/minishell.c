/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/21 14:35:54 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig_type;

int	main(void)
{
	t_memory_info	*memory_head;
	t_token			*token_head;

	g_sig_type = 0;
	signals();
	while (1)
	{
		if (!lexer(&memory_head, &token_head))
			break ;
		// if (token_head)
		// {
		// 	//continue
		// }
	}
	free_tokens(token_head);
	return (0);
}
