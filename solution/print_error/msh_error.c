/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 23:10:24 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/04 23:27:58 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Print error in format
	minishell: [<reason>: ][<message>]
*/
void	msh_error(char *reason, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (reason)
	{
		ft_putstr_fd(reason, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (message != NULL)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
		perror("");
}
