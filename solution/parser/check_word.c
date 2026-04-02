/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:03:25 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/02 11:54:21 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_split_by_chars.h"
#include "parse_cases.h"
#include "expand_variables.h"
#include "parser_utils.h"

/*
	Update substr_list
	We split by env_ifs only if substr without quots
*/
void	apply_ifs(t_minishell *mshell, t_list **substr_list)
{
	char	*ifs;
	t_list	*fields;
	t_list	*node;
	char	*word;

	ifs = get_env_value(mshell->env_list, "IFS");
	if (!ifs || !*ifs)
		ifs = " \t\n";
	node = *substr_list;
	while (node)
	{
		word = (char *)(node->content);
		if (word && word[0] != SINGLE && word[0] != DOUBLE)
		{
			fields = ft_split_by_chars(word, ifs);
			print_list(fields, "fields after ifs");
		}
	}
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

char	*check_word(t_minishell *mshell, char *word)
{
	t_list	*substr_list;

	(void)*mshell;
	cut_word(&substr_list, word);
	print_list(substr_list, "substrlist after cut by quotes");
	expand(mshell, &substr_list);
	return (combine_str_from_list(&substr_list));
}
