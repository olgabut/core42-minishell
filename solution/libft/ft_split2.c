/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:10:49 by dprikhod          #+#    #+#             */
/*   Updated: 2025/10/27 18:53:51 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_split(char **arr)
{
	while (arr)
	{
		if (*arr)
			ft_printf("%s\n", *arr);
		else
			return ;
		arr++;
	}
}

/*
 * ## Free array after split
 * */
void	ft_clr_split(void *content)
{
	char	**arr;
	int		i;

	arr = (char **)content;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
