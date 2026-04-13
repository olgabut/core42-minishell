/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:37:30 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/13 20:27:20 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define MAX_PIPE_COUNT 16

/*
* # STRUCTURE
	`int		outfd;`
	`int		infd;`
	`char	**argv;`
	`char	**envp;`
	`char	*path;`
*/
typedef struct s_exec_info {
	int		outfd;
	int		infd;
	char	**argv;
	char	**envp;
	char	*path;
}	t_exec_info;

#endif
