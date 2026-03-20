/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 23:19:25 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/15 23:21:51 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_CMD_H
# define FREE_CMD_H

# include "minishell.h"

/*
* free all fields in 'cmd' structure
*/
void					free_cmd(t_cmd *cmd);

#endif
