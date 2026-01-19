/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:39:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/19 08:47:26 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>

typedef struct s_memory_info
{
	char					*link;
	struct s_memory_info	*next;
}	t_memory_info;

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		ft_strtoint(int *num_result, char *str);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_print_string(char *str);
int		add_new_memory_link_for_control(t_memory_info **head, void *new_link);
void	free_memory_links(t_memory_info *head);

#endif