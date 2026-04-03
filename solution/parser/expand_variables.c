/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:30:28 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/03 16:49:53 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_variables.h"
#include "parse_cases.h"
#include "parser_utils.h"

// static char	*process_literal(char *result, const char *word, size_t *i)
// {
// 	char	*tmp;

// 	tmp = ft_straddchar(result, word[*i]);
// 	if (!tmp)
// 		return (NULL);
// 	(*i)++;
// 	return (tmp);
// }

// char	*expand_variables(t_minishell *mshell, const char *word)
// {
// 	char	*result;
// 	size_t	i;
// 	char	*tmp;

// 	result = ft_strdup("");
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (word[i])
// 	{
// 		if (word[i] == '$')
// 			tmp = handle_dollar(mshell, result, word, &i);
// 		else
// 		{
// 			tmp = process_literal(result, word, &i);
// 			free(result);
// 		}
// 		if (!tmp)
// 		{
// 			free(result);
// 			return (NULL);
// 		}
// 		result = tmp;
// 	}
// 	return (result);
// }

/* Return var with '$' (first character)*/
static char	*get_var_name(const char *word)
{
	int i;

	i = 1;
	while (ft_isalnum(word[i]) || word[i] == '_')
		i++;
	return (ft_substr(word, 0, i));
}

void cut_word_before_expand(t_list **substr_list_head, char *word)
{
	size_t	i;
	char	*substr;

	i = 0;
	*substr_list_head = NULL;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			beginning_of_str(&substr, word, i);
			if (substr)
				ft_lstadd_back(substr_list_head, ft_lstnew(substr));
			word += i;
			i = 0;
			if (word[i + 1] == '?')
			{
				substr = ft_strdup("$?");
				i = 2;
			}
			else
			{
				substr = get_var_name(word);
				i = ft_strlen(substr);
			}
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

static char	*expand_variables(t_minishell *mshell, char *word)
{
	t_list	*substr_for_expand;
	t_list	*node;
	char	*substr;
	char	*value;

	substr_for_expand = NULL;
	cut_word_before_expand(&substr_for_expand, word);
	node = substr_for_expand;
	while (node)
	{
		substr = (char *)(node->content);
		if (substr && substr[0] == '$')
		{
			if (substr[1] == '?')
				value = ft_itoa(mshell->exit_code);
			else
				value = ft_strdup(get_env_value(mshell->env_list, substr + 1));
			//ifs on value with flag need_open_ifd == true
			update_content(&node, value);
		}
		node = node->next;
	}
	return (combine_str_from_list(&substr_for_expand));
}

/*
	Update substr_list
	We expand env in substr in normal string and string with double quotes
	We don't expand env in string with single quotes
*/
void	expand(t_minishell *mshell, t_list **substr_list)
{
	t_list	*node;
	char	*substr;

	if (!substr_list || !*substr_list)
		return ;
	node = *substr_list;
	while (node)
	{
		substr = (char *)(node->content);
		if (substr && substr[0] != SINGLE)
			update_content(&node, expand_variables(mshell, substr));
		node = node->next;
	}
}
