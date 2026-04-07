/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/12 09:54:08 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print_parsed_commands.h"

t_global	g_signal;

static void	init_shell(t_minishell *sh, t_env **env_list)
{
	sh->env_list = *env_list;
	sh->cmd_list = NULL;
	sh->memory_head = NULL;
	sh->stdin_backup = STDIN_FILENO;
	sh->stdout_backup = STDOUT_FILENO;
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env_list;
	t_token			*token_head;
	t_minishell		sh;

	(void)argc;
	(void)**argv;
	init_env(&env_list, envp);
	signals();
	sh.exit_code = 0;
	while (1)
	{
		init_shell(&sh, &env_list);
		token_head = NULL;
		if (!lexer(&sh, &token_head))
		{
			ft_printf("lexer: ");
			break ;
		}
		if (!parse(&sh, token_head))
		{
			ft_printf("parser: ");
			break ;
		}
		// print_parsed_commands(sh.cmd_list);
		if (execute(&sh) != 0)
		{
			ft_fprintf(STDERR_FILENO, "executor: %d\n", sh.exit_code);
			break ;
		}
		free_memory_links(&sh.memory_head);
		if (g_signal.sigint)
		{
			printf("ctrl+C");
			sh.exit_code = EXIT_CTRL_C;
			g_signal.sigint = 0;
		}
	}
	free_env_list(&sh.env_list);
	free_memory_links(&sh.memory_head);
	return (0);
}
