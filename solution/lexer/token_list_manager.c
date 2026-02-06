/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:59:32 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/06 10:35:50 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Free all tokens
*/
void	free_tokens(t_token *head)
{
	t_token	*token;
	t_token	*next_token;

	token = head;
	while (token != NULL)
	{
		next_token = token->next;
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		free(token);
		token = next_token;
	}
}

/*
	Creates new token by type and string value
	Return
		1 - ok
		0 - malloc error
*/
int	create_token(
	t_token **token, enum e_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	*token = new_token;
	return (1);
}

/*
	Adds new_token to the list of tokens to the last position,
	where head is the first token
*/
void	add_new_token(t_token **head, t_token *new_token)
{
	t_token	*token;

	if (new_token == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		new_token->prev = NULL;
		return ;
	}
	token = *head;
	while (token->next != NULL)
		token = token->next;
	token->next = new_token;
	new_token->prev = token;
}

t_token	*get_last_token(t_token *head)
{
	t_token	*token;

	if (!head)
		return (NULL);
	token = head;
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	print_token_list(t_token *head)
{
	t_token	*token;

	// token = get_last_token(head);
	// printf("Print tokens from last to first:\n");
	// while (token)
	// {
	// 	printf("token type=%d value='%s'\n",
	// 		token->type, token->value);
	// 	token = token->prev;
	// }
}
