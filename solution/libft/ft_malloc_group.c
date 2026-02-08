/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_group.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niel <niel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:29:13 by niel              #+#    #+#             */
/*   Updated: 2025/07/20 10:36:37 by niel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, int n)
{
	ft_memset(s, 0, n);
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	size;	

	size = ft_strlen(s) + 1;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, size);
	return (ptr);
}

static size_t	ft_count_len(int nb)
{
	size_t	len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*c;
	long	nb1;
	size_t	len;
	int		neg;
	int		i;

	nb1 = n;
	neg = (nb1 < 0);
	if (neg)
		nb1 = -nb1;
	len = ft_count_len(nb1);
	c = (char *)malloc(len + neg + 1);
	if (!c)
		return (NULL);
	c[len + neg] = '\0';
	i = len + neg - 1;
	while (i >= neg)
	{
		c[i] = '0' + (nb1 % 10);
		nb1 /= 10;
		i--;
	}
	if (neg)
		c[0] = '-';
	return (c);
}
