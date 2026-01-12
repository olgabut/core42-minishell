/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:13:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/12 12:02:11 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Creates new token by type and string value
*/
t_token *create_token(enum e_token_type type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

int	check_command_char(t_token	*token, char *line, int start_word_pos)
{
	int	cur_char_pos;
	bool	isQuote;

	if (line[start_word_pos + 1] == ' '
			|| line[start_word_pos + 1] == '\0')
	{
		if (line[start_word_pos] == '|')
			printf("TOKEN_PIPE\n");
		if (line[start_word_pos] == '<')
			printf("TOKEN_REDIR_IN\n");
		if (line[start_word_pos] == '>')
			printf("TOKEN_REDIR_OUT\n");
		if (line[start_word_pos] == '(')
			printf("TOKEN_LPAREN\n");
		if (line[start_word_pos] == ')')
			printf("TOKEN_RPAREN\n");
		if (line[start_word_pos] == ';')
			printf("TOKEN_SEMICOLON\n");
		return (start_word_pos + 1);
	}
	if (line[start_word_pos + 2] == ' '
			|| line[start_word_pos + 2] == '\0')
	{
		if (line[start_word_pos] == '<'
			&& line[start_word_pos + 1] == '<')
			printf("TOKEN_HEREDOC\n");
		if (line[start_word_pos] == '>'
			&& line[start_word_pos + 1] == '>')
			printf("TOKEN_APPEND\n");
		if (line[start_word_pos] == '&'
			&& line[start_word_pos + 1] == '&')
			printf("TOKEN_AND\n");
		if (line[start_word_pos] == '|'
			&& line[start_word_pos + 1] == '|')
			printf("TOKEN_OR\n");
		return (start_word_pos + 2);
	}
	cur_char_pos = 0;
	while (line[start_word_pos + cur_char_pos] != ' '
		&& line[start_word_pos + cur_char_pos] != '\0')
	{
		printf("char of word = %c\n", line[start_word_pos + cur_char_pos]);
		cur_char_pos++;
	}
	printf("TOKEN_WORD\n");
	return (start_word_pos + cur_char_pos);
}


t_token	*line_lexer(char *line)
{
	int	start_word_pos;
	int	line_length;
	enum e_token_type	type;
	t_token	*token;

	if (!line)
		return (NULL);
	start_word_pos = 0;
	line_length = strlen(line);
	printf("line len = %d\n", line_length);
	while (start_word_pos < line_length)
	{
		while (line[start_word_pos] == ' ')
			start_word_pos++;
		if (start_word_pos >= line_length)
			break;
		printf("new word from %d\n", start_word_pos);
		check_command_char(token, line, start_word_pos);
	}
	return (NULL);//todo return t_token
}