/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/25 22:17:14 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print_parsed_commands.h"
#include "parse.h"
#include "init.h"
#include "free_cmd.h"

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
			break ;
		}
		sh.cmd_list = parser(&sh, token_head);
		print_parsed_commands(sh.cmd_list);
		free_memory_links(&sh.memory_head);
	}
	free_env_list(&sh.env_list);
	free_memory_links(&sh.memory_head);
	return (0);
}
