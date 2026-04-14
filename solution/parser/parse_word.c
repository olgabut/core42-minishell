/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:45:27 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/14 22:31:23 by obutolin         ###   ########.fr       */
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

	str = process_word(sh, word);
	if (!str)
		return (1);
	if (str[0] == '\0')
	{
		free(str);
		return (1);
	}
	add_new_memory_link_for_control(&sh->memory_head, str);
	ft_lstadd_back(&(cmd->args_list), ft_lstnew(str));
	return (1);
}
