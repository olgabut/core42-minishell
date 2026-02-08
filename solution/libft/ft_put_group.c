/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_group.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niel <niel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:30:24 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 12:11:24 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buf[12];
	int		i;
	long	num;

	num = n;
	i = 0;
	if (num == 0)
		buf[i++] = '0';
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	while (num > 0)
	{
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}
	while (i > 0)
		write(fd, &buf[--i], 1);
}

void	ft_print_string(char *str)
{
	if (!str)
		ft_putstr_fd("(null)", 1);
	ft_putstr_fd(str, 1);
}
