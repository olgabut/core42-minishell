/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:20:32 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/26 17:08:42 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_split_by_chars.h"

static void	add_field(t_list **lst, const char *str, int start, size_t len)
{
	char	*field;

	field = ft_substr(str, start, len);
	if (field && *field)
		ft_lstadd_back(lst, ft_lstnew(field));
	else
		free(field);
}

static void	on_ifs_char(t_split_state *st, const char *str, t_list **lst)
{
	if (st->in_field)
	{
		add_field(lst, str, st->start, st->i - st->start);
		st->in_field = false;
	}
	st->i++;
	st->start = st->i;
}

static void	on_regular_char(t_split_state *st)
{
	if (!st->in_field)
		st->start = st->i;
	st->in_field = true;
	st->i++;
}

t_list	*ft_split_by_chars(const char *str, const char *ifs)
{
	t_list			*fields;
	t_split_state	st;

	st.i = 0;
	fields = NULL;
	st.start = 0;
	st.in_field = false;
	while (str[st.i])
	{
		if (ft_strchr(ifs, str[st.i]))
			on_ifs_char(&st, str, &fields);
		else
			on_regular_char(&st);
	}
	if (st.in_field)
		add_field(&fields, str, st.start, st.i - st.start);
	return (fields);
}
