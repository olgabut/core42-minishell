/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/20 20:06:39 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print_parsed_commands.h"

int	main(int argc, char **argv, char **envp)
{
	t_token			*token_head;
	t_minishell		sh;

	(void)argc;
	(void)**argv;
	init_shell(&sh, envp);
	while (1)
	{
		token_head = NULL;
		if (!lexer(&sh.memory_head, &token_head))
		{
			printf("ctrl+D\n");
			free_memory_links(&sh.memory_long);
			break ;
		}
		sh.cmd_list = parser(&sh, token_head);
		print_parsed_commands(sh.cmd_list);
		free_memory_links(&sh.memory_head);
	}
	free_memory_links(&sh.memory_head);
	return (0);
}
