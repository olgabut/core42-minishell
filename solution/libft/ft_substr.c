/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:45:41 by obutolin          #+#    #+#             */
/*   Updated: 2025/09/08 09:59:00 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/*
	The ft_substr() function allocates memory (using malloc(3)) and returns a
		substring from the string ’s’. The substring starts at index ’start’
		and has a maximum length of ’len’.
	Parameters:
		s: The original string from which to create the substring.
		start: The starting index of the substring within ’s’.
		len: The maximum length of the substring.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			substrlen;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		substrlen = 0;
	else
	{
		substrlen = ft_strlen(s + start);
		if (substrlen > len)
			substrlen = len;
	}
	substr = malloc(substrlen + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < substrlen)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[substrlen] = '\0';
	return (substr);
}
