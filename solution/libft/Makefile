NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_substr.c \
	ft_count_words_in_str.c \
	ft_strlen.c \
	ft_strtoint.c \
	ft_max.c \
	ft_min.c \
	ft_print_string.c

OBJS = $(SRC:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus