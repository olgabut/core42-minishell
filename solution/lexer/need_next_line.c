/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:43:47 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/03 12:10:18 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	need_wait_for_closing_quote(t_token *token_head)
{
	t_token	*last_token;
	char	*line;
	bool	is_single_quote;
	bool	is_double_quote;
	int		i;

	is_single_quote = false;
	is_double_quote = false;
	last_token = get_last_token(token_head);
	if (last_token->type != TOKEN_WORD)
		return (false);
	line = last_token->value;
	i = 0;
	while (line[i] != '\0')
	{
		if (!is_double_quote && line[i] == '\'')
			is_single_quote = !is_single_quote;
		if (!is_single_quote && line[i] == '\"')
			is_double_quote = !is_double_quote;
		i++;
	}
	return (is_single_quote || is_double_quote);
}

bool	need_wait_for_continuation_of_command(t_token *token_head)
{
	t_token	*last_token;

	last_token = get_last_token(token_head);
	return (last_token->type == TOKEN_PIPE
		|| last_token->type == TOKEN_AND
		|| last_token->type == TOKEN_OR);
}


bool	need_next_line(t_token *token_head)
{
	if (!token_head)
		return (false);
	return (need_wait_for_closing_quote(token_head)
		|| need_wait_for_continuation_of_command(token_head));
}
