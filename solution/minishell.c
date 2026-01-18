/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:30:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/18 22:23:10 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	// t_token	*token_head;

	// while (1)
	// {
	// 	if (!lexer(&token_head))
	// 		break ;
	// }
	// return (0);
	
	
	
	//test memory manager
	// check leaks using command on the MAC OS" >
	//> MallocStackLogging=1 leaks --atExit -- ./minishell | grep leak
	char *str;
	char *str2;
	t_memory_info *memory_link_head;
	int i;

	memory_link_head = NULL;
	str = NULL;
	str = malloc(sizeof(char)* 5);
	if (str == NULL)
		return (1);
	str[0] = 'w';
	str[1] = 'q';
	str[2] = '3';
	str[3] = '2';
	str[4] = '\0';
	add_new_memory_link_for_control(&memory_link_head, str, SIMPLE);
	printf("str = %s\n", str);
	str2 = malloc(sizeof(char)*10);
	for (i=0; i<10;i++)
		str2[i] = '4';
	printf("str2 = %s\n", str2);
	add_new_memory_link_for_control(&memory_link_head, str2, SIMPLE);
	
	free_memory_links(memory_link_head);
	return (0);
}
