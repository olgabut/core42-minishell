/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:19:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/14 14:20:08 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *sh, char **envp)
{
	sh->cmd_list = NULL;
	sh->exit_code = 0;
	sh->cmd_list = NULL;
	sh->stdin_backup = STDIN_FILENO;
	sh->stdout_backup = STDOUT_FILENO;
	sh->memory_head = NULL;
	sh->memory_long = NULL;
	if (!init_env(&sh->memory_long, &(sh->env_list), envp))
		ft_putstr_fd("Could not initialize environment", 1);
	signals();
}
