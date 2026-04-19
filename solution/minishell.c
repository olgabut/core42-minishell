/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/19 16:09:27 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print_parsed_commands.h"

t_global	g_info;

static void	init_shell(t_minishell *sh, t_env **env_list)
{
	sh->env_list = *env_list;
	sh->cmd_list = NULL;
	sh->memory_head = NULL;
	sh->stdin_backup = STDIN_FILENO;
	sh->stdout_backup = STDOUT_FILENO;
	set_signals_for_common_code();
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env_list;
	t_token			*token_head;
	t_minishell		sh;

	(void)argc;
	(void)**argv;
	init_env(&env_list, envp);
	g_info.sigint = 0;
	g_info.exit_code = 0;
	while (1)
	{
		init_shell(&sh, &env_list);
		token_head = NULL;
		if (!lexer(&sh, &token_head))
			break ;
		if (!parse(&sh, token_head))
			break ;
		if (!execute(&sh))
			break ;
		free_memory_links(&sh.memory_head);
	}
	free_env_list(&sh.env_list);
	free_memory_links(&sh.memory_head);
	return (0);
}
