/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/06 00:06:21 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print_parsed_commands.h"
#include "parse.h"
#include "init.h"

int	main(int argc, char **argv, char **envp)
{
	t_env			*env_list;
	t_token			*token_head;
	t_minishell		sh;

	(void)argc;
	(void)**argv;
	init_env(&env_list, envp);
	sh.exit_code = 0;
	while (1)
	{
		init_shell(&sh, &env_list);
		token_head = NULL;
		if (!lexer(&sh, &token_head))
		{
			printf("ctrl+D\n");
			break ;
		}
		if (!parser(&sh, token_head))
			break;
		// print_parsed_commands(sh.cmd_list);
		if (!execute(&sh))
			break ;
		free_memory_links(&sh.memory_head);
	}
	free_env_list(&sh.env_list);
	free_memory_links(&sh.memory_head);
	return (0);
}
