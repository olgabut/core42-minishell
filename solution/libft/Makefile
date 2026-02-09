NAME = libft.a

SOURCES = ft_is_group.c \
	ft_is_2.c \
	ft_malloc_group.c \
	ft_mem_group.c \
	ft_put_group.c \
	ft_split_group.c \
	ft_split2.c \
	ft_atoi_group.c \
	ft_str_adv.c \
	ft_str_basic.c \
	ft_str_finder.c \
	ft_str_utils.c \
	ft_printf.c \
	ft_printf_utils.c \
	ft_bonus.c \
	ft_bonus_2.c \
	get_next_line.c \
	ft_compare.c \
	memory_manager/memory_manager.c

OBJECTS = $(SOURCES:.c=.o)

BONUS = ft_bonus.c ft_bonus_2.c
BONUS_OBJECTS = $(BONUS:.c=.o)

HEADERS = libft.h

CFLAGS = -Wall -Wextra -Werror -fPIC

CUR_DIR = $(shell pwd)

CC = cc

all: $(NAME) bonus

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

bonus: $(NAME) $(BONUS_OBJECTS)
	@ar rc $(NAME) $(BONUS_OBJECTS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -I $(CUR_DIR) -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
