/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:37 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/29 13:28:27 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_path_from_env(char *cmd_name, char **env_path_ar)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (env_path_ar[i] != NULL)
	{
		tmp = ft_straddchar(env_path_ar[i], '/');
		path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		tmp = NULL;
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		i++;
	}
	i = 0;
	while (env_path_ar[i] != NULL)
	{
		free(env_path_ar[i]);
		env_path_ar[i] = NULL;
		i++;
	}
	free(env_path_ar);
	return (path);
}

void	find_cmd_path(t_cmd *cmd, t_minishell *sh)
{
	char	*cmd_name_with_slash;
	char	*env_path_value;
	char	**path_ar;

	cmd_name_with_slash = ft_strchr(cmd->args[0], '/');
	if (cmd_name_with_slash != NULL)
	{
		cmd->path = ft_strdup(cmd->args[0]);
		add_new_memory_link_for_control(&sh->memory_head, cmd->path);
	}
	else
	{
		env_path_value = get_env_value(sh->env_list, "PATH");
		if (env_path_value == NULL)
			return ;
		path_ar = ft_split(env_path_value, ':');
		if (path_ar == NULL)
			return ;
		cmd->path = find_cmd_path_from_env(cmd->args[0], path_ar);
		if (cmd->path)
			add_new_memory_link_for_control(&sh->memory_head, cmd->path);
	}
}
