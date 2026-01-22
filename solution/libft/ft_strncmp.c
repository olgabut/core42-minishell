/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:02:57 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/22 11:40:46 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The ft_strncmp() function shall compare not more than n bytes
		(bytes that follow a NUL character are not compared) from
		the array pointed to by s1 to the array pointed to by s2.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && (*s1 == *s2) && (n > 0))
	{
		s1++;
		s2++;
		n--;
	}
	if (*s1 == *s2 || n == 0)
		return (0);
	if ((unsigned int)*s1 > (unsigned int)(*s2))
		return (1);
	else
		return (-1);
}