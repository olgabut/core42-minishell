/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:19:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/25 18:03:11 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// typedef struct s_minishell
// {
// 	t_env				*env_list;
// 	t_cmd				*cmd_list;
// 	t_memory_info		*memory_head;
// 	int					exit_code;
// 	int					stdin_backup;
// 	int					stdout_backup;
// }						t_minishell;

void	init_shell(t_minishell *sh, char **envp)
{
	init_env(&sh->env_list, envp);
	sh->cmd_list = NULL;
	sh->memory_head = NULL;
	sh->exit_code = 0;
	sh->stdin_backup = STDIN_FILENO;
	sh->stdout_backup = STDOUT_FILENO;
	// signals();-
}
