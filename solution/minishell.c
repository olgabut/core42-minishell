/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/15 16:17:27 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_memory_info	*memory_long;
	t_memory_info	*memory_line;
	t_token			*token_head;
	t_env			*env_head;

	(void)argc;
	(void)**argv;
	memory_long = NULL;
	memory_line = NULL;
	env_head = NULL;
	if (!init_env(&memory_long, &env_head, envp))
	{
		ft_putstr_fd("Could not initialize environment", 1);
		return (0);
	}
	while (1)
	{
		token_head = NULL;
		if (!lexer(&memory_line, &token_head))
			break ;
		if (token_head)
		{
			print_token_list(token_head);
			printf("Next step PARSING\n");
		}
		free_memory_links(&memory_line);
	}
	free_memory_links(&memory_line);
	free_memory_links(&memory_long);
	return (0);
}
