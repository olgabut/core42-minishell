/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:37 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/06 14:34:17 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/execute.h"

static char	*find_cmd_path_from_env(char *cmd_name, char **env_path_ar)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	path = NULL;
	while (env_path_ar && env_path_ar[i] != NULL)
	{
		tmp = ft_straddchar(env_path_ar[i], '/');
		path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		tmp = NULL;
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (!path)
		return (NULL);
	return (ft_strdup(path));
}

static void	path_ar_free(char **env_path_ar)
{
	int		i;

	i = 0;
	while (env_path_ar && env_path_ar[i] != NULL)
	{
		free(env_path_ar[i]);
		env_path_ar[i] = NULL;
		i++;
	}
	if (env_path_ar)
		free(env_path_ar);
}

void	find_cmd_path(t_exec_info *ei, t_env *env, t_memory_info **head)
{
	char	*cmd_name_with_slash;
	char	*env_path_value;
	char	**path_ar;

	cmd_name_with_slash = ft_strchr(ei->argv[0], '/');
	if (cmd_name_with_slash != NULL)
	{
		ei->path = ft_strdup(ei->argv[0]);
		add_new_memory_link_for_control(head, ei->path);
	}
	else
	{
		env_path_value = get_env_value(env, "PATH");
		if (env_path_value == NULL)
			return ;
		path_ar = ft_split(env_path_value, ':');
		if (path_ar == NULL)
			return ;
		ei->path = find_cmd_path_from_env(ei->argv[0], path_ar);
		if (ei->path)
			add_new_memory_link_for_control(head, ei->path);
		path_ar_free(path_ar);
	}
}
