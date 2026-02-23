/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/23 10:14:57 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print_parsed_commands.h"

static void	init_shell(t_minishell *sh, char **envp)
{
	sh->cmd_list = NULL;
	sh->exit_code = 0;
	sh->cmd_list = NULL;
	sh->stdin_backup = STDIN_FILENO;
	sh->stdout_backup = STDOUT_FILENO;
	sh->memory_head = NULL;
	sh->memory_long = NULL;
	if (!init_env(&sh->memory_long, &(sh->env_list), envp))
		ft_putstr_fd("Could not initialize environment", 1);
	signals();
}

int	main(int argc, char **argv, char **envp)
{
	t_token			*token_head;
	t_minishell		sh;

	(void)argc;
	(void)**argv;
	init_shell(&sh, envp);
	sh.env_list = NULL;
	while (1)
	{
		token_head = NULL;
		if (!lexer(&sh.memory_head, &token_head))
		{
			printf("ctrl+D\n");
			break ;
		}
		if (token_head)
			printf("Next step PARSING\n");
		sh.cmd_list = parser(&sh, token_head);
		print_parsed_commands(sh.cmd_list);
		// if (pid == 0)
		// {
		// 	signal(SIGINT, SIG_DFL);
		// 	signal(SIGQUIT, SIG_DFL);
		// 	execve(...);
		// }
		free_memory_links(&sh.memory_head);
	}
	free_memory_links(&sh.memory_head);
	return (0);
}
