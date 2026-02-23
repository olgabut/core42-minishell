/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:34:56 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/23 10:13:02 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// ft_is_group.c
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);

// ft_is_2.c
int					ft_isspace(int c);

// ft_mem_group.c
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *s, int c, int n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);

// ft_str_utils.c
char				*ft_strtrim(char const *s1, char const *set);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_straddchar(const char *str, char c);

// ft_str_finder.c
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

// ft_str_basic.c
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, const char *s2);

// ft_str_adv.c
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// ft_atoi_group.c
int					ft_atoi(const char *str);
int					ft_atoi_base(char *str, int base);
int					ft_strtoint(int *num_result, char *str);

// ft_split_group.c
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);

// ft_split2.c
void				ft_print_split(char **arr);
void				ft_clr_split(void *content);

// ft_malloc_group.c
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s);
void				*ft_bzero(void *s, int n);
char				*ft_itoa(int n);

// ft_put_group.c
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_print_string(char *str);

// ft_printf_utils.c
int					s_handle(char *s, int fd);
int					u_handle(unsigned int u, int fd);
int					i_handle(int n, int fd);
int					x_handle(unsigned long x, char *base, int fd);
int					p_handle(void *p, int fd);

// ft_printf.c
int					ft_fprintf(int fd, const char *format, ...);
int					ft_printf(const char *format, ...);

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;

typedef struct s_node
{
	struct s_list	*next;
}					t_node;

// ft_bonus.c
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);

// ft_bonus_2.c
void				ft_lstdelone(t_list *lst, void (*del)(void *));
int					ft_lstsize(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), 
						void (*del)(void *));

// ft_list_utils.c
char				**ft_strvec_from_word_list(t_list *list);

// ft_compare.c
int					ft_min_int(int a, int b);
int					ft_max_int(int a, int b);

# define BUFFER_SIZE 4

// get_next_line.c
char				*get_next_line(int fd);

// memory_manager
typedef t_list		t_memory_info;

int					add_new_memory_link_for_control(t_memory_info **head,
						void *new_link);
void				free_memory_links(t_memory_info **head);

#endif
