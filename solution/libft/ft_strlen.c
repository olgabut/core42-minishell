/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:44:25 by obutolin          #+#    #+#             */
/*   Updated: 2025/09/08 09:57:57 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

/*
	The ft_strlen() function shall compute the number of bytes in the string
	to which s points, not including the terminating NUL character.
*/
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

// int main()
// {
// 	printf("%lu %lu\n", strlen(""), ft_strlen(""));
// 	printf("%lu %lu\n", strlen("123"), ft_strlen("123"));
// }