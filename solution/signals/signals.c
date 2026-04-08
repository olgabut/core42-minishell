/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:35:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/08 11:52:05 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sigaction_error(void)
{
	if (errno == EINVAL)
		ft_putstr_fd(
			"Error: invalid signal number or bad handler.\n", 2);
	else if (errno == EFAULT)
		ft_putstr_fd(
			"Error: invalid memory address for sigaction structure.\n", 2);
	else if (errno == EINVAL)
		ft_putstr_fd(
			"Error: signal not supported on this system.\n", 2);
	else
		ft_putstr_fd(
			"Error: unknown problem while setting signal handler.\n", 2);
}

/*
	stage = 1 (readline in lexer)
	stage = 2 (child process in executor)
	stage = 3 (heredoc)
	stage = 0 (other)
*/
void	sigint_handler(int sig)
{
	(void)sig;
	g_info.exit_code = EXIT_CTRL_C;
	g_info.sigint = 1;
	if (g_info.stage == 1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
SIGINT // Ctrl+C
SIGQUIT // Ctrl+\
*/
void	set_signals(void)
{
	g_info.stage = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
