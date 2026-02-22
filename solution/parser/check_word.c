/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:03:25 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/22 17:17:36 by dprikhod         ###   ########.fr       */
/* ************************************************************************** */

#include "env_utils.h"
#include "expand_variables.h"
#include "ft_split_by_chars.h"
#include "parse_cases.h"

static char	*trim_quotes(char *word, enum e_quote flag)
{
	char	*trim_set;
	char	*trimmed;

	if (flag == SINGLE)
		trim_set = "'";
	else if (flag == DOUBLE)
		trim_set = "\"";
	else
		trim_set = NULL;
	if (trim_set)
	{
		trimmed = ft_strtrim(word, trim_set);
		free(word);
		if (!trimmed)
			return (NULL);
	}
	else
	{
		trimmed = ft_strdup(word);
		free(word);
		if (!trimmed)
			return (NULL);
	}
	return (trimmed);
}

t_list	*apply_ifs(t_minishell *mshell, char *word)
{
	char	*ifs;
	t_list	*fields;

	ifs = get_env_value(mshell->env_list, "IFS");
	if (!ifs || !*ifs)
	{
		free(ifs);
		ifs = ft_strdup(" \t\n");
	}
	fields = ft_split_by_chars(word, ifs);
	free(ifs);
	free(word);
	return (fields);
}

char	*check_word(t_minishell *mshell, char *word)
{
	enum e_quote	flag;
	char			*trimmed;
	char			*expanded;

	if (!word)
		return (NULL);
	flag = NONE;
	if (word[0] == SINGLE || word[0] == DOUBLE)
		flag = word[0];
	if (flag)
		trimmed = trim_quotes(word, flag);
	if (flag == SINGLE)
		expanded = trimmed;
	else
	{
		expanded = expand_variables(mshell, trimmed);
		free(trimmed);
		if (!expanded)
			return (NULL);
	}
	// if (is_redir)
	// {
	// 	size = ft_lstsize(fields);
	// 	if (size != 1 || !fields || !*((char *)fields->content))
	// 	{
	// 		ft_lstclear(&fields, free);
	// 		mshell->exit_code = 1;
	// 	}
	// }
	return (expanded);
}
