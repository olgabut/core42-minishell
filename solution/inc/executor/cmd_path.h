/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:04:18 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/19 13:17:38 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PATH_H
# define CMD_PATH_H

# include "minishell.h"

char	*find_cmd_path(char *cmd_name, t_env *env);
int		check_cmd_path(t_exec_info *ei);

#endif
