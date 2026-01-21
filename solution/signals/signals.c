/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:35:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/21 12:13:09 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sig_type = 0;

void	print_sigaction_error(void)
{
	if (errno == EINVAL)
		ft_print_string(
			"Error: invalid signal number or bad handler.\n");
	else if (errno == EFAULT)
		ft_print_string(
			"Error: invalid memory address for sigaction structure.\n");
	else if (errno == EINVAL)
		ft_print_string(
			"Error: signal not supported on this system.\n");
	else
		ft_print_string(
			"Error: unknown problem while setting signal handler.\n");
}

void signals_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_type = 'C';
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_sig_type = '\\';
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
	struct sigaction sa;

	sa.sa_handler = &signals_handler;
	// sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
		print_sigaction_error();
	// signal(SIGQUIT, SIG_IGN);
}