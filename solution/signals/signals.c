/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:35:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/07 23:40:06 by obutolin         ###   ########.fr       */
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

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal.sigint = 1;
}

/*
struct sigaction {
    void     (*sa_handler)(int); // Link to the handler
    void     (*sa_sigaction)(int, siginfo_t *, void *); // For SA_SIGINFO
    sigset_t   sa_mask;
    int        sa_flags; // SA_RESTART making certain system
                            calls restartable across signals
    void     (*sa_restorer)(void);
};

SIGINT // Ctrl+C
SIGQUIT // Ctrl+\
*/
void	signals(void)
{
	// struct sigaction sa_sigint;

	// sa_sigint.sa_handler = sigint_handler;
    // sigemptyset(&sa_sigint.sa_mask);
    // sa_sigint.sa_flags = SA_RESTART;
    // if (sigaction(SIGINT, &sa_sigint, NULL))
	// 	print_sigaction_error();
	// signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	g_signal.sigint = 0;
}
