/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:56:57 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/05 12:04:47 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd_error(char *cmd_name, char *message)
{
	ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd_name, message);
}
