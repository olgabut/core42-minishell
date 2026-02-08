/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:23:03 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/08 12:07:57 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

static int	atoi_loop(char *str, int base)
{
	int	digit;
	int	result;

	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'A' && *str <= 'Z')
			digit = *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'z')
			digit = *str - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		result = result * base + digit;
		str++;
	}
	return (result);
}

int	ft_atoi_base(char *str, int base)
{
	int	sign;

	if (!str)
		return (0);
	if (base < 2 || base > 32)
		return (0);
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*(str++) == '-')
		sign = -1;
	else if (*str == '+')
		str++;
	return (atoi_loop(str, base) * sign);
}

int	get_unsigned_num(long long *num, char *str, int sign)
{
	long int	long_num;

	long_num = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		long_num = (long_num * 10) + (*str - '0');
		str++;
		if (long_num * sign < INT_MIN || long_num * sign > INT_MAX)
			return (0);
	}
	*num = long_num;
	return (1);
}

/*
	The ft_strtoint() function converts string (str) to integer number (*ptr_num)
	Parameters:
		int *ptr_num: pointer to integer for number.
		char *str: string
	Return:
		1 - correct number
		0 - error
*/
int	ft_strtoint(int *ptr_num, char *str)
{
	long long	long_num;
	int			minus;

	if (!str || !ptr_num)
		return (0);
	minus = 1;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	if (!*str)
		return (0);
	if (!get_unsigned_num(&long_num, str, minus))
		return (0);
	long_num *= minus;
	if (long_num < INT_MIN || long_num > INT_MAX)
		return (0);
	*ptr_num = (int)long_num;
	return (1);
}
