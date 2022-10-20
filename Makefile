# CC=gcc -Wall -Wextra -Werror -O3
CC=gcc -Wall -Wextra -Werror -O3 -fsanitize=address -g

MS_FILES=main.c parser.c parser_quotes.c env.c execve.c \
	bin_validation.c

MS_FULL=$(addprefix srcs/, $(MS_FILES))
MS_OBJ=$(MS_FULL:%.c=%.o)
LIBNAME=libft/libft.a
NAME=minishell
# $(MS_OBJ): $(LIBNAME)

all: $(NAME)

$(NAME): $(MS_OBJ) $(MS_FULL) $(LIBNAME)
	$(CC) $(MS_OBJ) $(LIBNAME) -o $(NAME)
	rm -rf $(MS_OBJ)

%.o: %.c
	$(CC) -c $(<) -o $(@)

$(LIBNAME):
	$(MAKE) -C libft/

clean:
	$(MAKE) -C libft/ clean
	rm -rf $(MS_OBJ)

fclean: clean
	$(MAKE) -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
