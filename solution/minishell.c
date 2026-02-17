/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/22 18:00:24 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_memory_info	*memory_head;
	t_token			*token_head;
	t_memory_info	*memory_long;
	t_memory_info	*memory_line;
	t_env			*env_head;

	signals();
	(void)argc;
	(void)**argv;
	memory_long = NULL;
	memory_line = NULL;
	(void)memory_line;
	env_head = NULL;
	if (!init_env(&memory_long, &env_head, envp))
	{
		ft_putstr_fd("Could not initialize environment", 1);
		return (0);
	}
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
			printf("Next step PARSING\n");

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
