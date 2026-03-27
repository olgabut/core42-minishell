/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:37 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/27 23:05:10 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_cmd_path(t_cmd *cmd, t_minishell *sh)
{
	char	**path_ar;
	char	*path_try;
	char	*tmp;
	int		i;

	path_try = ft_strrchr(cmd->args[0], '/');
	if (path_try != NULL)
	{
		cmd->path = ft_strdup(cmd->args[0]);
		add_new_memory_link_for_control(&sh->memory_head, cmd->path);
		return ;
	}
	free(path_try);
	path_try = NULL;
	path_ar = ft_split(get_env_value(sh->env_list, "PATH"), ':');
	i = 0;
	while (path_ar[i] != NULL)
	{
		tmp = ft_straddchar(path_ar[i], '/');
		path_try = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		tmp = NULL;
		if (access(path_try, X_OK) == 0)
		{
			cmd->path = ft_strdup(path_try);
			add_new_memory_link_for_control(&sh->memory_head, cmd->path);
			break ;
		}
		free(path_try);
		path_try = NULL;
		i++;
	}
	i = 0;
	while (path_ar[i] != NULL)
	{
		free(path_ar[i]);
		i++;
	}
	free(path_ar);
}
