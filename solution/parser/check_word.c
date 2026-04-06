/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:03:25 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/06 11:25:33 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_split_by_chars.h"
#include "parser.h"

t_list	*apply_ifs(t_minishell *mshell, char *word)
{
	char	*ifs;
	t_list	*fields;

	ifs = get_env_value(mshell->env_list, "IFS");
	if (!ifs || !*ifs)
		ifs = " \t\n";
	fields = ft_split_by_chars(word, ifs);
	free(word);
	return (fields);
}

// char	*check_word(t_minishell *mshell, char *word)
// {
// 	enum e_quote	flag;
// 	char			*trimmed;
// 	char			*expanded;

// 	if (!word)
// 		return (NULL);
// 	flag = NONE;
// 	if (word[0] == SINGLE || word[0] == DOUBLE)
// 		flag = word[0];
// 	if (flag)
// 		trimmed = trim_quotes(word, flag);
// 	if (flag == SINGLE)
// 		expanded = trimmed;
// 	else
// 	{
// 		expanded = expand_variables(mshell, trimmed);
// 		free(trimmed);
// 		if (!expanded)
// 			return (NULL);
// 	}
// 	return (expanded);
// }

/*
	Result will be in <substr> from <str> up to the character quote
	without first and last quotes
*/
static int	substr_in_quotes(char **substr, char *str, int quote)
{
	int		i;
	char	*quotation;

	*substr = NULL;
	i = 1;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	quotation = ft_calloc(i + 2, sizeof(char));
	if (!quotation)
		return (0);
	ft_strlcpy(quotation, str, i + 2);
	*substr = quotation;
	return (i + 1);
}

/*
	Create substr_list by string <word>
	We cut <word> by quots
	Example <word> = 123"abc"555'dd"d''ccc'8
	 <substr_list> = 123 -> "abc" -> 555 -> 'dd"d' -> 'ccc' -> 8 -> NULL
	It needs to understand where expand env and apply ifs
*/
static void	cut_word(t_list **substr_list_head, char *word)
{
	int		i;
	char	*substr;

	i = 0;
	*substr_list_head = NULL;
	while (word[i] != '\0')
	{
		if (word[i] == SINGLE || word[i] == DOUBLE)
		{
			beginning_of_str(&substr, word, i);
			if (substr)
				ft_lstadd_back(substr_list_head, ft_lstnew(substr));
			word += i;
			i = substr_in_quotes(&substr, word, word[0]);
			if (substr)
				ft_lstadd_back(substr_list_head, ft_lstnew(substr));
			word += i;
			i = -1;
		}
		i++;
	}
	beginning_of_str(&substr, word, i);
	if (substr)
		ft_lstadd_back(substr_list_head, ft_lstnew(substr));
}

void	remove_quotes(t_list **substr_list)
{
	t_list	*node;
	char	*str;
	char	*str_without_quotes;
	size_t	len;

	if (!substr_list || !*substr_list)
		return ;
	node = *substr_list;
	while (node)
	{
		str = (char *)(node->content);
		if (str && (str[0] == SINGLE || str[0] == DOUBLE))
		{
			len = ft_strlen(str) - 1;
			str_without_quotes = ft_calloc(len, sizeof(char *));
			if (str_without_quotes)
			{
				ft_strlcpy(str_without_quotes, str + 1, len);
				update_content(&node, str_without_quotes);
			}
		}
		node = node->next;
	}
}

char	*check_word(t_minishell *mshell, char *word)
{
	t_list	*substr_list;

	(void)*mshell;
	cut_word(&substr_list, word);
	expand(mshell, &substr_list);
	remove_quotes(&substr_list);
	return (combine_str_from_list(&substr_list));
}
