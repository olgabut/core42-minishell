/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:51:59 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/06 10:20:36 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_echo_options(char *word)
{
	return (ft_strcmp(word, "-n") == 0
		|| ft_strcmp(word, "-e") == 0
		|| ft_strcmp(word, "-E") == 0);
}

bool	print_word(char *word, bool printed_first_word)
{
	if (printed_first_word)
		printf(" ");
	printf("%s", word);
	return (true);
}

/*
	echo command
	echo [option(s)] [string(s)]

	options:
	-n (SUPPORTED in minishell) Omits trailing newlines.
	-e (IGNORED in minishell) Enables backslash escapes (like \n and \t).
	-E: (IGNORED in minishell) Disables backslash escapes (default behavior).
 */
int	echo_builtin(char **argv)
{
	bool	n_option;
	bool	option;
	bool	printed_first_word;
	int		i;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "echo") != 0)
		return (0);
	i = 1;
	option = true;
	n_option = false;
	printed_first_word = false;
	while (argv[i])
	{
		if (option)
		{
			option = is_echo_options(argv[i]);
			n_option = n_option || ft_strcmp(argv[i], "-n") == 0;
		}
		if (!option)
			printed_first_word = print_word(argv[i], printed_first_word);
		i++;
	}
	if (!n_option)
		printf("\n");
	return (1);
}
