/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:30:28 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/21 11:43:37 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser_utils.h"

/* Return var with '$' (first character)*/
static char	*get_var_name(const char *word)
{
	int	i;

	i = 1;
	while (ft_isalnum(word[i]) || word[i] == '_')
		i++;
	return (ft_substr(word, 0, i));
}

void	cut_word_before_expand(t_list **substr_list_head, char *word)
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

static char	*get_value_from_env(t_env *env_list, char *key)
{
	char	*value;

	value = get_env_value(env_list, key);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

//ifs on value with flag need_open_ifd == true (before unpdate_content)
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
			if (substr[1] == '\0')
				value = ft_strdup("$");
			else if (substr[1] == '?')
				value = ft_itoa(g_info.exit_code);
			else
				value = get_value_from_env(mshell->env_list, substr + 1);
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
