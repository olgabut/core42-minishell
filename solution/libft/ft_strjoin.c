/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:38:50 by olgabutolin       #+#    #+#             */
/*   Updated: 2026/02/02 10:16:12 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The ft_striteri() function allocates memory (using malloc(3)) and
	returns a new string, which is the result of concatenating
	’s1’ and ’s2’.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	s1len;
	size_t	s2len;
	int		i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = malloc(s1len + s2len + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[i - s1len] != '\0')
	{
		newstr[i] = s2[i - s1len];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
