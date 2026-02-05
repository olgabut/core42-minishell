/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:51:59 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/05 12:38:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



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
	bool	n_flag;
	bool	can_be_flag;
	int		i;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "echo") != 0)
		return (0);
	i = 1;
	can_be_flag = true;
	n_flag = false;
	while (argv[i])
	{
		if (can_be_flag)
		{
			printf("can be flag\n");
			can_be_flag = (ft_strcmp(argv[i], "-n") == 0
					|| ft_strcmp(argv[i], "-e") == 0
					|| ft_strcmp(argv[i], "-E") == 0);
			n_flag = n_flag && ft_strcmp(argv[i], "-n");
		}
		else
		{
			printf("string for print: ");
			printf("%s", argv[i]);
		}
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (1);
}
