/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:45:27 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/15 14:43:25 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/process_word.h"

/*
	return 0 - error
		   1 - ok, continue
*/
int	parse_word(t_minishell *sh, t_cmd *cmd, char *word)
{
	char	*str;
	t_list	*node;

	str = process_word(sh, word);
	if (!str)
		return (1);
	if (str[0] == '\0')
	{
		free(str);
		return (1);
	}
	add_new_memory_link_for_control(&sh->memory_head, str);
	node = ft_lstnew(str);
	if (!node)
		return (0);
	ft_lstadd_back(&(cmd->args_list), node);
	add_new_memory_link_for_control(&sh->memory_head, node);
	return (1);
}
