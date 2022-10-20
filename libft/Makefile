CC=gcc -Wall -Wextra -Werror -O3
LIBFT_FILES=ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
	  	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
	  	ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
	  	ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
	  	ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
	  	ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
	  	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
	  	ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
	  	ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
	  	ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstnew.c \
	  	ft_lstadd.c ft_lstdelone.c ft_lstdel.c ft_lstiter.c ft_lstmap.c \
	  	ft_lstadd_end.c get_next_line.c ft_free_doublearray.c \
		ft_iswhitespace.c ft_strcount.c ft_strjoin_three.c \
		ft_strlen_match.c
PRINTF_FILES=address.c assign.c bonus.c char.c flags.c flags2.c float.c \
		ft_printf.c helpers.c hex_flags.c hex.c int_flags.c int.c \
		octal_flags.c octal.c percent.c string.c unsigned.c

FULL_PRINTF_FILES=$(addprefix printf/srcs/, $(PRINTF_FILES))
FULL_LIBFT_FILES=$(addprefix libft_srcs/, $(LIBFT_FILES))
LIBFT_OBJECTS=$(FULL_LIBFT_FILES:%.c=%.o)
PRINTF_OBJECTS=$(FULL_PRINTF_FILES:%.c=%.o)
LIBNAME=libft.a
LIB=ar rc

all: $(LIBNAME)

$(LIBNAME): $(FULL_LIBFT_FILES:%.c=%.o) $(FULL_PRINTF_FILES:%.c=%.o)
	@$(LIB) $(LIBNAME) $(LIBFT_OBJECTS) $(PRINTF_OBJECTS)
	@printf "libft.a created!\n"

%.o: %.c
	$(CC) -c $(<) -o $(@)

clean:
	@rm -rf $(LIBFT_OBJECTS)
	@rm -rf $(PRINTF_OBJECTS)
	@printf "rm all .o files from libft_srcs/ && printf/srcs/\n"

fclean: clean
	rm -rf $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
