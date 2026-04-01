/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:41:47 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/02 00:32:09 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_cases.h"

/*
	Result will be in <substr> from <str> up to the character quote
	without first and last quotes
*/
static int	substr_in_quotes(char **substr, char *str, int quote)
{
	int	i;
	char *quotation;

	*substr = NULL;
	i = 1;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	quotation = ft_calloc(i + 1, sizeof(char));
	if (!quotation)
		return (0);
	ft_strlcpy(quotation, str + 1, i);
	*substr = quotation;
	return (i + 1);
}

// /*
// 	Result is substr of str (first len characters)
// */
static char	*beginning_of_str(char *str, int len)
{
	char	*substr;

	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, str, len + 1);
	return (substr);
}

/* Expand env key in str to env value
	Revrite str
	Return 0 - error
		   1 - ok
*/
static int	expand_env_varibales(t_minishell *sh, char **str)
{
	char	*expanded;

	(void)*sh;
	if (!str || !*str)
		return (1);
	expanded = ft_strdup(*str);//expand_variables(sh, *str);
	if (!expanded)
		return (0);
	free(*str);
	*str = expanded;
	return (1);
}


char	*expand_based_on_quotes(t_minishell *sh, char *word)
{
	int		i;
	t_list	*substr_list;
	char	*substr;

	i = 0;
	substr_list = NULL;
	substr = NULL;
	while (word[i] != '\0')
	{
		if (word[i] == SINGLE || word[i] == DOUBLE)
		{
			substr = NULL;
			substr = beginning_of_str(word, i);
			if (substr
				&& expand_env_varibales(sh, &substr) && substr[0] != '\0')
				ft_lstadd_back(&substr_list, ft_lstnew(substr));
			word += i;
			i = substr_in_quotes(&substr, word, word[0]);
			if (word[0] == DOUBLE && substr
				&& expand_env_varibales(sh, &substr) && substr[0] != '\0')
				ft_lstadd_back(&substr_list, ft_lstnew(substr));
			else if (substr && substr[0] != '\0')
				ft_lstadd_back(&substr_list, ft_lstnew(substr));
			word += i;
			i = -1;
		}
		i++;
	}
	if (i > 0)
	{
		substr = beginning_of_str(word, i);
		if (substr && expand_env_varibales(sh, &substr) && substr[0] != '\0')
			ft_lstadd_back(&substr_list, ft_lstnew(substr));
	}
	return (combine_str_from_list(&substr_list));
}
