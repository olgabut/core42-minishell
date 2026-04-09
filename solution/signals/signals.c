/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:35:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/09 23:16:25 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_info.exit_code = EXIT_SIGINT;
	g_info.sigint = 1;
	if (g_info.stage == STAGE_READLINE)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signals_for_child_proces(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("signal");
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
void	set_signals_for_common_code(void)
{
	// struct sigaction	sa_sigint;

	// ft_memset(&sa_sigint, 0, sizeof(sa_sigint));
	// sigemptyset(&sa_sigint.sa_mask);
	// sa_sigint.sa_handler = sigint_handler;
	// if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
	// 	perror("signal");
	// sigaction(SIGQUIT, &sa, NULL);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}
