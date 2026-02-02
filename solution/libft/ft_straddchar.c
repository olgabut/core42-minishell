/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:15:30 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/02 11:08:02 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddchar(const char *str, char c)
{
	size_t len;
	char *new_str;

	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return NULL;
	ft_strlcpy(new_str, str, len + 2);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return new_str;
}
