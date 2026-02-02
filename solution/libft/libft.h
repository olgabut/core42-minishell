/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:39:10 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/02 10:55:48 by obutolin         ###   ########.fr       */
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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_straddchar(const char *str, char c);
int		ft_strtoint(int *num_result, char *str);
void	ft_print_string(char *str);
int		add_new_memory_link_for_control(t_memory_info **head, void *new_link);
void	free_memory_links(t_memory_info *head);

#endif