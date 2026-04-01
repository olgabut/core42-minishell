/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 23:42:24 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/02 00:42:30 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	Result is substr of str (first len characters)
*/
void	beginning_of_str(char **substr, char *str, int len)
{
	*substr = NULL;
	if (len < 1)
		return ;
	*substr = ft_calloc(len + 1, sizeof(char));
	if (!*substr)
		return ;
	ft_strlcpy(*substr, str, len + 1);
}

char *combine_str_from_list(t_list **head_list)
{
	char *str;
	t_list *node;
	t_list *tmp_node;

	if (!head_list)
		return (NULL);
	str = ft_strdup("");
	node = *head_list;
	while (node)
	{
		// printf("list = %s\n", (char *)(node->content));
		str = ft_strjoin_free(str, node->content);
		tmp_node = node;
		node = node->next;
		free(tmp_node->content);
		free(tmp_node);
	}
	return (str);
}

void	print_list(t_list *head)
{
	t_list *node;
	
	node = head;
	while (node)
	{
		printf("%s\n", (char *)(node->content));
		node = node->next;
	}
}

