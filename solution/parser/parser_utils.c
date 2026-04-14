/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 23:42:24 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/14 22:31:52 by obutolin         ###   ########.fr       */
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

char	*combine_str_from_list(t_list **head_list)
{
	char	*str;
	t_list	*node;
	t_list	*tmp_node;

	if (!head_list)
		return (NULL);
	str = ft_strdup("");
	node = *head_list;
	while (node)
	{
		str = ft_strjoin_free(str, node->content);
		tmp_node = node;
		node = node->next;
		free(tmp_node->content);
		free(tmp_node);
	}
	return (str);
}

void	update_content(t_list **node, char *new_content)
{
	t_list	*node_to_update;
	char	*str_for_free;

	node_to_update = *node;
	if (!new_content)
		return ;
	str_for_free = (char *)(node_to_update->content);
	node_to_update->content = new_content;
	free(str_for_free);
	str_for_free = NULL;
}

void	print_list(t_list *head, char *message)
{
	t_list	*node;
	int		i;

	node = head;
	printf("%s\n", message);
	i = 1;
	while (node)
	{
		printf("%d %s\n", i, (char *)(node->content));
		node = node->next;
		i++;
	}
	printf("=====================\n");
}
