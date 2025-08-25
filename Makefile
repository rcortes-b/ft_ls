NAME = ft_ls

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCS = src/ls.c


OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

HEAD = inc/ls.h

all : make_libs $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -MMD -c $< -o $@

make_libs:
	make bonus -C libft
	make -C ft_printf

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -Llibft -lft -Lft_printf -lftprintf

clean :
	make clean -C libft
	make clean -C ft_printf
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	make clean -C libft
	make fclean -C ft_printf
	$(RM) $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re make_libs