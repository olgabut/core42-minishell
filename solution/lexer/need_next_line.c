/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:43:47 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/02 11:40:59 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	need_wait_for_closing_quote(t_token *token_head)
{
	t_token	*last_token;
	char	*line;
	char	cur_quote;
	int		i;

	printf("need_wait_for_closing_quote\n");
	cur_quote = '0';
	last_token = get_last_token(token_head);
	if (last_token->type != TOKEN_WORD)
		return (false);
	line = last_token->value;
	i = 0;
	printf("	last_token_value = '%s'\n", last_token->value);
	while (line[i] != '\0')
	{
		if (line[i] == cur_quote && cur_quote != '0')
			cur_quote = '0';
		if (line[i] == '\'' && cur_quote == '0')
			cur_quote = '\'';
		else if (line[i] == '\"' && cur_quote == '0')
			cur_quote = '\"';
		i++;
	}
	if (cur_quote != '0')
		return (true);
	return (false);
}

bool	need_next_line(t_token *token_head)
{
	return (need_wait_for_closing_quote(token_head));
}
