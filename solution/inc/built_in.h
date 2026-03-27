/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:25:06 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/27 22:17:39 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

int	built_in_echo(char **argv);
int	built_in_pwd(void);
int	built_in_exit(char **argv, int last_cmd_exit, bool *need_exit);
int	built_in_env(char **argv, t_env *env);
int	built_in_export(char **argv, t_env **env);
int	built_in_unset(char **argv, t_env **env);
int	built_in_cd(char **argv, t_env **env);

#endif