/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:44:20 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/22 11:22:05 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	free_memory_links(t_memory_info *head)
{
	t_memory_info	*node;
	t_memory_info	*next_node;

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

int	create_memory_link_node(t_memory_info **new_memory_info, void *new_link)
{
	t_memory_info	*new_memory_info_node;

	new_memory_info_node = malloc(sizeof(t_memory_info));
	if (!new_memory_info_node)
		return (0);
	new_memory_info_node->link = new_link;
	new_memory_info_node->next = NULL;
	*new_memory_info = new_memory_info_node;
	return (1);
}

/* Return
	1 - ok
	0 - malloc error
 */
int	add_new_memory_link_for_control(t_memory_info **head, void *new_link)
{
	t_memory_info	*link_node;
	t_memory_info	*new_line_node;

	if (new_link == NULL)
		return (1);
	if (!create_memory_link_node(&new_line_node, new_link))
		return (0);
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

//test memory manager
// check leaks using command on the MAC OS" >
//> MallocStackLogging=1 leaks --atExit -- ./prog_name | grep leak
// check leaks using command on the Linux OS >
//> valgrind --leak-check=full ./prog_name
// int	main(void)
// {
// 	char *str;
// 	char *str2;
// 	t_memory_info *memory_link_head;
// 	int i;

// 	memory_link_head = NULL;
// 	str = NULL;
// 	str = malloc(sizeof(char)* 5);
// 	if (str == NULL)
// 		return (1);
// 	str[0] = 'w';
// 	str[1] = 'q';
// 	str[2] = '3';
// 	str[3] = '2';
// 	str[4] = '\0';
// 	add_new_memory_link_for_control(&memory_link_head, str);
// 	printf("str = %s\n", str);
// 	str2 = malloc(sizeof(char)*10);
// 	for (i=0; i<10;i++)
// 		str2[i] = '4';
// 	str2[9] = '\0';
// 	printf("str2 = %s\n", str2);
// 	add_new_memory_link_for_control(&memory_link_head, str2);
// 	free_memory_links(memory_link_head);
// 	return (0);
// }
