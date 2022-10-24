CC=gcc -Wall -Wextra -Werror -O3
# CC=gcc -Wall -Wextra -Werror -O3 -fsanitize=address -g

MS_FILES=main.c input.c env_print.c env_unset.c builtins.c \
	binaries.c env.c env_set.c convert.c parser.c

MS_FULL=$(addprefix srcs/, $(MS_FILES))
MS_OBJ=$(MS_FULL:%.c=%.o)
LIBNAME=libft/libft.a
NAME=minishell

all: $(NAME)

$(NAME): $(MS_OBJ) $(LIBNAME)
	$(CC) $(MS_OBJ) $(LIBNAME) -o $(NAME)

%.o: %.c
	$(CC) -c $(<) -o $(@)

$(LIBNAME):
	$(MAKE) -C libft/

clean:
	@$(MAKE) -C libft/ clean
	rm -rf $(MS_OBJ)

fclean: clean
	@$(MAKE) -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
