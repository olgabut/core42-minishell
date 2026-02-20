/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:30:28 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/20 16:45:25 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_variables.h"
#include "handle_dollar.h"

static char	*process_literal(char *result, const char *word, size_t *i)
{
	char	*tmp;

	tmp = ft_straddchar(result, word[*i]);
	if (!tmp)
		return (NULL);
	(*i)++;
	return (tmp);
}

char	*expand_variables(t_minishell *mshell, const char *word)
{
	char	*result;
	size_t	i;
	char	*tmp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			tmp = handle_dollar(mshell, result, word, &i);
		else
			tmp = process_literal(result, word, &i);
		if (!tmp)
			return (NULL);
		result = tmp;
	}
	return (result);
}
