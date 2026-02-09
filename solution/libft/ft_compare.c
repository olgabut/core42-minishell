/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:51:29 by dprikhod          #+#    #+#             */
/*   Updated: 2026/01/26 12:53:29 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min_int(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_max_int(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
