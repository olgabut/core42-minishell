/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:37 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/15 21:57:34 by obutolin         ###   ########.fr       */
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
		path = ft_strjoin_free(tmp, cmd_name);
		tmp = NULL;
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (!path)
		return (NULL);
	return (path);
}

static void	possible_path_ar_free(char **env_path_ar)
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

char	*find_cmd_path(char *cmd_name, t_env *env)
{
	char	*cmd_name_with_slash;
	char	*env_path_value;
	char	**possible_path_ar;
	char	*path;

	cmd_name_with_slash = ft_strchr(cmd_name, '/');
	if (cmd_name_with_slash != NULL)
		return (ft_strdup(cmd_name));
	else
	{
		env_path_value = get_env_value(env, "PATH");
		if (env_path_value == NULL)
			return (NULL);
		possible_path_ar = ft_split(env_path_value, ':');
		if (possible_path_ar == NULL)
			return (NULL);
		path = find_cmd_path_from_env(cmd_name, possible_path_ar);
		possible_path_ar_free(possible_path_ar);
		return (path);
	}
}
