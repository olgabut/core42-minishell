/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:13:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/19 09:10:05 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Search for double special characters (<<, >>, &&, ||)
	in the line string from start_word_pos
If we found this special characters - creates token
Return
	0-error (could't create token, malloc error)
	1-ok
*/
int	search_for_double_token(t_token **token, char *line, int start_word_pos)
{
	if (line[start_word_pos] == '<' && line[start_word_pos + 1] == '<')
		return (create_token(token, TOKEN_HEREDOC,
				ft_substr(line, start_word_pos, 2)));
	if (line[start_word_pos] == '>' && line[start_word_pos + 1] == '>')
		return (create_token(token, TOKEN_APPEND,
				ft_substr(line, start_word_pos, 2)));
	if (line[start_word_pos] == '&' && line[start_word_pos + 1] == '&')
		return (create_token(token, TOKEN_AND,
				ft_substr(line, start_word_pos, 2)));
	if (line[start_word_pos] == '|' && line[start_word_pos + 1] == '|')
		return (create_token(token, TOKEN_OR,
				ft_substr(line, start_word_pos, 2)));
	return (1);
}

/*
Search for single special characters (<, >, |, (, ), ;)
	in the line string from start_word_pos
If we found this special characters - creates token
Return
	0-error (could't create token, malloc error)
	1-ok
*/
int	search_for_single_token(t_token **token, char *line, int start_word_pos)
{
	if (line[start_word_pos] == '<')
		return (create_token(token, TOKEN_REDIR_IN,
				ft_substr(line, start_word_pos, 1)));
	if (line[start_word_pos] == '>')
		return (create_token(token, TOKEN_REDIR_OUT,
				ft_substr(line, start_word_pos, 1)));
	if (line[start_word_pos] == '|')
		return (create_token(token, TOKEN_PIPE,
				ft_substr(line, start_word_pos, 1)));
	if (line[start_word_pos] == '(')
		return (create_token(token, TOKEN_LPAREN,
				ft_substr(line, start_word_pos, 1)));
	if (line[start_word_pos] == ')')
		return (create_token(token, TOKEN_RPAREN,
				ft_substr(line, start_word_pos, 1)));
	if (line[start_word_pos] == ';')
		return (create_token(token, TOKEN_SEMICOLON,
				ft_substr(line, start_word_pos, 1)));
	return (1);
}

/*
Search for a word

Return
	0-error (could't create token, malloc error)
	1-ok
*/
int	search_for_word(t_token **token, char *line, int *start_word_pos)
{
	int		cur_char_pos;
	bool	is_single_quote;
	bool	is_double_quote;

	cur_char_pos = 0;
	is_single_quote = false;
	is_double_quote = false;
	while (line[*start_word_pos + cur_char_pos] != '\0'
		&& (is_single_quote || is_double_quote
			|| (line[*start_word_pos + cur_char_pos] != ' '
				&& line[*start_word_pos + cur_char_pos] != '|'
				&& line[*start_word_pos + cur_char_pos] != '<'
				&& line[*start_word_pos + cur_char_pos] != '>'
				&& line[*start_word_pos + cur_char_pos] != '&'
				&& line[*start_word_pos + cur_char_pos] != '('
				&& line[*start_word_pos + cur_char_pos] != ')'
				&& line[*start_word_pos + cur_char_pos] != ';')))
	{
		if (!is_double_quote && line[*start_word_pos + cur_char_pos] == '\'')
			is_single_quote = !is_single_quote;
		if (!is_single_quote && line[*start_word_pos + cur_char_pos] == '\"')
			is_double_quote = !is_double_quote;
		cur_char_pos++;
	}
	if (cur_char_pos > 0)
	{
		if (!create_token(token, TOKEN_WORD,
				ft_substr(line, *start_word_pos, cur_char_pos)))
			return (0);
		*start_word_pos = *start_word_pos + cur_char_pos;
	}
	return (1);
}

/*
	Search for a token
	Return only one first token in line
	Result will be in t_token **token like a last new node
	Change start_word_pos to the next token position
	Return 0-error, 1-ok
*/
int	search_for_token(t_token **token, char *line, int *start_word_pos)
{
	if (!search_for_double_token(token, line, *start_word_pos))
		return (0);
	if (*token != NULL)
	{
		*start_word_pos = *start_word_pos + 2;
		return (1);
	}
	if (!search_for_single_token(token, line, *start_word_pos))
		return (0);
	if (*token != NULL)
	{
		*start_word_pos = *start_word_pos + 1;
		return (1);
	}
	return (search_for_word(token, line, start_word_pos));
}

int	line_lexer(t_memory_info **memory_head,
	t_token **token_head, char *line)
{
	int		start_word_pos;
	int		line_length;
	t_token	*next_token;

	if (!line)
		return (0);
	start_word_pos = 0;
	line_length = strlen(line);
	while (start_word_pos < line_length)
	{
		next_token = NULL;
		while (line[start_word_pos] == ' ')
			start_word_pos++;
		if (start_word_pos >= line_length)
			break ;
		if (!search_for_token(&next_token, line, &start_word_pos))
			return (0);
		add_new_memory_link_for_control(memory_head, next_token->value);
		add_new_memory_link_for_control(memory_head, next_token);
		add_new_token(token_head, next_token);
	}
	return (1);
}
