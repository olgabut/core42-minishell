/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:44:20 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/18 22:21:43 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	create_mamory_link_node(t_memory_info **new_mamory_info,
	void *new_link, enum e_memory_type new_link_type)
{
	t_memory_info	*new_mamory_info_node;

	new_mamory_info_node = malloc(sizeof(t_memory_info));
	if (!new_mamory_info_node)
		return (0);
	new_mamory_info_node->type = new_link_type;
	new_mamory_info_node->link = new_link;
	new_mamory_info_node->next = NULL;
	*new_mamory_info = new_mamory_info_node;
	return (1);
}

int	add_new_memory_link_for_control(t_memory_info **head,
	void *new_link, enum e_memory_type new_link_type)
{
	t_memory_info	*link_node;
	t_memory_info   *new_line_node;

	if (new_link == NULL)
		return (1);
	if (!create_mamory_link_node(&new_line_node, new_link, new_link_type))
	{
		//free all, end of the program
		return (0);
	}
	if (*head == NULL)
	{
		*head = new_line_node;
		return (1);
	}
	link_node = *head;
	while (link_node->next != NULL)
		link_node = link_node->next;
	link_node->next = new_line_node;
	return (1);
}

void free_memory_links(t_memory_info *head)
{
	t_memory_info *node;
	t_memory_info *next_node;

	node = head;
	while (node != NULL)
	{
		next_node = node->next;
		free(node->link);
		node->link = NULL;
		free(node);
		node = next_node;
	}
}
