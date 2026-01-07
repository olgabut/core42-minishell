/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:39:10 by obutolin          #+#    #+#             */
/*   Updated: 2025/10/09 08:54:59 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_count_words_in_str(char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strtoint(int *num_result, char *str);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_print_string(char *str);

#endif