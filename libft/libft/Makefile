NAME		= libft.a

Library		= libft

SRC 	   = ft_strlen.c \
			 ft_memmove.c \
			 ft_memcpy.c \
			 ft_strlcpy.c \
			 ft_strlcat.c \
			 ft_isalpha.c \
			 ft_isdigit.c \
			 ft_isalnum.c \
			 ft_isascii.c \
			 ft_isprint.c \
			 ft_memset.c \
			 ft_bzero.c \
			 ft_toupper.c \
			 ft_tolower.c \
			 ft_strchr.c \
			 ft_strrchr.c \
			 ft_strncmp.c \
			 ft_memchr.c \
			 ft_memcmp.c \
			 ft_strnstr.c \
			 ft_atoi.c \
			 ft_calloc.c \
			 ft_strdup.c \
			 ft_substr.c \
			 ft_strjoin.c \
			 ft_strtrim.c \
			 ft_split.c \
			 ft_itoa.c \
			 ft_strmapi.c \
			 ft_striteri.c \
			 ft_putchar_fd.c \
			 ft_putstr_fd.c \
			 ft_putendl_fd.c \
			 ft_putnbr_fd.c \
			 ft_reverse_string.c \
			 ft_size_t_to_hex.c \
			 ft_pointer_to_hex.c \
			 ft_long_to_hex.c \
			 ft_uitoa.c \
			 ft_ltoa.c \
			 ft_string_to_upper.c\
			 ft_lstlast.c\
			 ft_lstmap.c\
			 ft_lstnew.c\
			 ft_lstlast.c\
			 ft_lstsize.c\
			 ft_lstclear.c\
			 ft_lstdelone.c\
			 ft_lstadd_back.c\
			 ft_lstiter.c\
			 ft_lstadd_front.c\
			 ft_atol.c

CC = g++
CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)
BOBJS = $(BSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
