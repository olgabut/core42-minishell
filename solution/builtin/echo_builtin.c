/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:51:59 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/06 15:12:43 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_echo_flags(char *word)
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
	echo command builtin
	The echo command is used to show a line of text or a variable's value
		in the terminal.

	echo [flag(s)] [string(s)]

	flags:
	-n (SUPPORTED in minishell) Omits trailing newlines.
	-e (IGNORED in minishell) Enables backslash escapes (like \n and \t).
	-E: (IGNORED in minishell) Disables backslash escapes (default behavior).

	return
		0 - successful completion     or    it's not echo command
		1 - error
 */
int	echo_builtin(char **argv)
{
	bool	n_flag;
	bool	flag;
	bool	printed_first_word;
	int		i;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "echo") != 0)
		return (0);
	i = 1;
	flag = true;
	n_flag = false;
	printed_first_word = false;
	while (argv[i])
	{
		if (flag)
		{
			flag = is_echo_flags(argv[i]);
			n_flag = n_flag || ft_strcmp(argv[i], "-n") == 0;
		}
		if (!flag)
			printed_first_word = print_word(argv[i], printed_first_word);
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
