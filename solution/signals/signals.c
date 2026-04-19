/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:35:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/19 16:15:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_rl_getc(FILE *stream)
{
	char	c;
	int		ret;

	(void)stream;
	ret = read(STDIN_FILENO, &c, 1);
	if (ret < 0 && errno == EINTR)
		return (EOF);
	if (ret == 0)
		return (EOF);
	return ((unsigned char)c);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_info.sigint = 1;
	g_info.exit_code = EXIT_SIGINT;
	if (g_info.stage == STAGE_READLINE)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signals_in_child_process(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("signal");
}

void	set_signals_for_common_code(void)
{
	g_info.sigint = 0;
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}
