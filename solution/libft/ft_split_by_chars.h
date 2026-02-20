/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_chars.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:10:57 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/20 18:16:43 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPLIT_BY_CHARS_H
# define FT_SPLIT_BY_CHARS_H

# include "libft.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_split_state
{
	int		i;
	size_t	start;
	bool	in_field;
}	t_split_state;

t_list	*ft_split_by_chars(const char *str, const char *ifs);

#endif
