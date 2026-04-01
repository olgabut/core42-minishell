/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:52:50 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/02 00:27:05 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_dollar.h"

static char	*expand_question(t_minishell *mshell, char *result)
{
	char	*value;

	value = ft_itoa(mshell->exit_code);
	if (!value)
	{
		free(result);
		return (NULL);
	}
	result = ft_strjoin_free(result, value);
	free(value);
	return (result);
}

static char	*expand_digit(t_minishell *mshell, char *result, const char *word,
		size_t *i)
{
	char	*key;
	char	*value;

	key = ft_substr(word, *i, 1);
	if (!key)
	{
		free(result);
		return (NULL);
	}
	value = get_env_value(mshell->env_list, key);
	free(key);
	if (!value)
	{
		free(result);
		return (NULL);
	}
	result = ft_strjoin_free(result, value);
	free(value);
	(*i)++;
	return (result);
}

/* Return var with '$' (first character)*/
char	*get_var_name(const char *word)
{
	int i;

	i = 1;
	while (ft_isalnum(word[i]) || word[i] == '_')
		i++;
	return (ft_substr(word, 0, i));
}

static char	*expand_normal_var(t_minishell *mshell, char *result,
		const char *word, size_t *i)
{
	char	*key;
	char	*value;

	(void)*word;
	(void)*i;
	// key = get_var_name(word, i);
	key = NULL;
	if (!key)
	{
		free(result);
		return (NULL);
	}
	value = get_env_value(mshell->env_list, key);
	free(key);
	if (!value)
	{
		free(result);
		return (NULL);
	}
	result = ft_strjoin_free(result, value);
	free(value);
	return (result);
}

char	*handle_dollar(t_minishell *mshell, char *result, const char *word,
		size_t *i)
{
	(*i)++;
	if (!word[*i])
		return (ft_strjoin_free(result, "$"));
	if (word[*i] == '?')
	{
		result = expand_question(mshell, result);
		if (!result)
			return (NULL);
		(*i)++;
		return (result);
	}
	if (ft_isdigit(word[*i]))
		return (expand_digit(mshell, result, word, i));
	if (ft_isalpha(word[*i]) || word[*i] == '_')
		return (expand_normal_var(mshell, result, word, i));
	return (ft_strjoin_free(result, "$"));
}
