/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:44:50 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 13:58:15 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strvec_from_word_list(t_list *list)
{
	char	**strvec;
	int		size;
	int		i;

	size = ft_lstsize(list);
	if (size == 0)
		return (NULL);
	i = 0;
	strvec = malloc(sizeof(char *) * (size + 1));
	if (!strvec)
		return (NULL);
	while (i < size)
	{
		strvec[i] = (char *)list->content;
		list = list->next;
		i++;
	}
	strvec[i] = NULL;
	return (strvec);
}
