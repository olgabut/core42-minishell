/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:51:59 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/26 10:08:16 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"

bool	is_echo_flags(char *word)
{
	int	i;

	if (word[0] != '-' || word[1] == '\0')
		return (false);
	i = 1;
	while (word[i])
	{
		if (word[i] != 'n' && word[i] != 'e' && word[i] != 'E')
			return (false);
		i++;
	}
	return (true);
}

bool	print_word(char *word, int fd, bool printed_first_word)
{
	if (printed_first_word)
		ft_putchar_fd(' ', fd);
	ft_putstr_fd(word, fd);
	return (true);
}

bool	is_echo(char **argv)
{
	return (!(!argv || !argv[0] || ft_strcmp(argv[0], "echo") != 0));
}

/*
	built in ECHO command
	minishell: echo with option -n

	The echo command is used to show a line of text or a variable's value
		in the terminal.

	echo [flag(s)] [string(s)]

	flags:
	-n (SUPPORTED in minishell) Omits trailing newlines.
	-e (IGNORED in minishell) Enables backslash escapes (like \n and \t).
	-E (IGNORED in minishell) Disables backslash escapes (default behavior).

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status

	FEATURE (NOT IMPLEMENTED in minishell yet!)
	'echo [flags] *' == ls
	'echo [flags] **' == ls (files with folder)
 */
int	built_in_echo(char **argv)
{
	bool	n_flag;
	bool	flag;
	bool	printed_first_word;
	int		i;

	i = 1;
	flag = true;
	n_flag = false;
	printed_first_word = false;
	while (argv[i])
	{
		if (flag)
		{
			flag = is_echo_flags(argv[i]);
			n_flag = n_flag || (flag && ft_strchr(argv[i], 'n') != NULL);
		}
		if (!flag)
			printed_first_word = print_word(argv[i], 1, printed_first_word);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
