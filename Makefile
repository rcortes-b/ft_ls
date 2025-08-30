NAME = ft_ls

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCS = src/ls.c src/list.c src/err.c src/utils.c src/entries.c src/sort.c src/print.c

HEAD = inc/ls.h inc/list.h inc/err.h inc/utils.h inc/entries.h inc/sort.h inc/print.h

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)


all : make_libs $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -MMD -c $< -o $@

make_libs:
	make -C libft
	make -C ft_printf

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -Llibft -lft -Lft_printf -lftprintf

clean :
	make clean -C libft
	make clean -C ft_printf
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	$(RM) $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re make_libs