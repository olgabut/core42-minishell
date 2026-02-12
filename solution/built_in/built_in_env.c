/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:28:20 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/12 17:26:04 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	built in ENV command
	It can print all the current environment variables, set new ones,
	or run a command within a custom environment.

	env [OPTION]... [-][NAME=VALUE]... [COMMAND [ARG]...]

	FLAGS (IGNORED in minishell):
		Flags to modify the behavior of the 'env' command.
		'-i' or '--ignore-environment' or '-' Runs a command with an empty environment
		'-u' or '--unset' Remove variable from the environment
		'-0' or '--null' End each output line with NULL, not newline
		'-C' or '--chdir=DIR' Change 
		'--version' Display version information and exit.
		'--help' Display a help message and exit.
		-C, --chdir=КАТ Изменить рабочий каталог на КАТ
		-S, --split-string=S
		Обработать и разделить S на отдельные аргументы; используется для указания нескольких аргументов в строках с #!
		--block-signal[=SIG]
		Блокировать доставку сигнала(ов) SIG
		--default-signal[=SIG]
		Сбросить обработку сигнала(ов) SIG в значение по умолчанию
		--ignore-signal[=SIG]
		Назначить обработке сигнала(ов) SIG пустое значение
		--list-signal-handling
		Выдать обработчики сигнала, отличные от значений по умолчанию, в stderr
		-v, --debug
		Выводить подробную информацию на каждом шаге обработки
	NAME=VALUE (IGNORED in minishell): Defines environment variables and their values.
	COMMAND [ARG] (IGNORED in minishell): Specifies the command to be executed with the modified environment.

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
 */
int	built_in_env(char **argv, t_env *env)
{
	if (!argv || !argv[0] || ft_strcmp(argv[0], "env") != 0)
		return (-1);
	if (argv[1])
	{
		ft_putstr_fd("minishell: env: too many arguments", STDERR_FILENO);
		return (126); //todo
	}
	if (!env)
		return (EXIT_FAILURE);
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
