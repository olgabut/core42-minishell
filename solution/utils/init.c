/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:19:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/05 21:14:23 by obutolin         ###   ########.fr       */
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

void	init_shell(t_minishell *sh, t_env **env_list)
{
	sh->env_list = *env_list;
	sh->cmd_list = NULL;
	sh->memory_head = NULL;
	sh->stdin_backup = STDIN_FILENO;
	sh->stdout_backup = STDOUT_FILENO;
	// signals();-
}
