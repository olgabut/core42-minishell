/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:37:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/16 13:44:06 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdbool.h>
# include "minishell.h"

/*
* # STRUCTURE
	`int		outfd;`
	`int		infd;`
	`char	**argv;`
	`char	**envp;`
	`char	*path;`
*/
typedef struct s_exec_info {
	struct s_exec_info	*next;
	int					outfd;
	int					infd;
	char				**argv;
	char				**envp;
	char				*path;
	bool				is_built_in;
	int					pipefd;
}	t_exec_info;

int prepare_exec_info_list(t_exec_info **ei_head, t_minishell *sh);
int get_cmd_count_by_ei(t_exec_info *ei);

#endif
