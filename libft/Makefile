CC = clang

CFLAGS = -Wall -Wextra -Werror -g

NAME = libft.a

LIB_C = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_itoa.c\
		  ft_isascii.c ft_isdigit.c ft_isprint.c\
		  ft_memset.c ft_toupper.c ft_tolower.c\
		  ft_strlen.c ft_memcpy.c ft_memmove.c ft_strncmp.c\
		  ft_strlcpy.c ft_strchr.c ft_strlcat.c ft_strrchr.c\
		  ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c\
		  ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
		  ft_strtrim.c ft_strmapi.c ft_striteri.c\
		  ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_split.c\
		  ft_putendl_fd.c ft_free_split.c\

BONUS_C = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		  ft_lstdelone.c ft_lstadd_back.c ft_lstclear.c\
		  ft_lstiter.c ft_lstmap.c

LIB_O = $(LIB_C:.c=.o) $@

BONUS_O =	$(BONUS_C:.c=.o) $@

all: $(NAME)

$(NAME): $(LIB_O) $(BONUS_O)
	$(AR) -r $@ $?

bonus: $(LIB_O) $(BONUS_O)
	$(AR) -r $(NAME) $?

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_O) $(BONUS_O) $@

fclean: clean
	rm -f $(NAME) $@

re: fclean all

.PHONY: all clean fclean re bonus