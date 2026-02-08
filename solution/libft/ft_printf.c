/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:56:25 by dprikhod          #+#    #+#             */
/*   Updated: 2025/07/20 11:43:14 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_var_handle(const char *format, va_list args, int i)
{
	int	temp;

	temp = 1;
	if (format[i + 1] == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (format[i + 1] == 's')
		temp = s_handle(va_arg(args, char *));
	else if (format[i + 1] == 'p')
		temp = p_handle(va_arg(args, void *));
	else if (format[i + 1] == 'd' || format[i + 1] == 'i')
		temp = i_handle(va_arg(args, int));
	else if (format[i + 1] == 'u')
		temp = u_handle(va_arg(args, unsigned int));
	else if (format[i + 1] == 'x')
		temp = x_handle((unsigned long)va_arg(args, unsigned int),
				"0123456789abcdef");
	else if (format[i + 1] == 'X')
		temp = x_handle((unsigned long)va_arg(args, unsigned int),
				"0123456789ABCDEF");
	else
		ft_putchar_fd('%', 1);
	return (temp);
}

/*
c - char
s - string
p - pointer
d - decimal
i - integer in base 10
u - unsigned decimal
x - lowercase hexidecimal
X - uppercase hexidecimal
% - percentage sign
*/
static int	helper(const char *format, va_list args, int *i)
{
	int	count;

	count = 0;
	if (format[*i] == '%')
	{
		if (format[*i + 1])
			count += ft_var_handle(format, args, *i);
		else
			return (-1);
		(*i)++;
	}
	else
	{
		ft_putchar_fd(format[*i], 1);
		count++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		ret;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		ret = helper(format, args, &i);
		if (ret == -1)
			return (ret);
		count += ret;
		i++;
	}
	va_end(args);
	return (count);
}
