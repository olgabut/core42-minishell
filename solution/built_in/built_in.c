/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:56:57 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/04 11:24:46 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_cmd_error(char *cmd_name, char *message, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd_name, message);
	return (exit_code);
}
