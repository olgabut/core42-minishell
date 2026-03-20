/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:19:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/20 22:16:14 by dprikhod         ###   ########.fr       */
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
	if (!init_env(&sh->env_list, envp))
		ft_putstr_fd("Could not initialize environment", 1);
	signals();
}
