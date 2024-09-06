NAME		= libft.a

Library		= libft

SRC 	   = ft_strlen.cpp \
			 ft_memmove.cpp \
			 ft_memcpy.cpp \
			 ft_strlcpy.cpp \
			 ft_strlcat.cpp \
			 ft_isalpha.cpp \
			 ft_isdigit.cpp \
			 ft_isalnum.cpp \
			 ft_isascii.cpp \
			 ft_isprint.cpp \
			 ft_memset.cpp \
			 ft_bzero.cpp \
			 ft_toupper.cpp \
			 ft_tolower.cpp \
			 ft_strchr.cpp \
			 ft_strrchr.cpp \
			 ft_strncmp.cpp \
			 ft_memchr.cpp \
			 ft_memcmp.cpp \
			 ft_strnstr.cpp \
			 ft_atoi.cpp \
			 ft_calloc.cpp \
			 ft_strdup.cpp \
			 ft_substr.cpp \
			 ft_strjoin.cpp \
			 ft_strtrim.cpp \
			 ft_split.cpp \
			 ft_itoa.cpp \
			 ft_strmapi.cpp \
			 ft_striteri.cpp \
			 ft_putchar_fd.cpp \
			 ft_putstr_fd.cpp \
			 ft_putendl_fd.cpp \
			 ft_putnbr_fd.cpp \
			 ft_reverse_string.cpp \
			 ft_size_t_to_hex.cpp \
			 ft_pointer_to_hex.cpp \
			 ft_long_to_hex.cpp \
			 ft_uitoa.cpp \
			 ft_ltoa.cpp \
			 ft_string_to_upper.cpp \
			 ft_lstlast.cpp \
			 ft_lstmap.cpp \
			 ft_lstnew.cpp \
			 ft_lstlast.cpp \
			 ft_lstsize.cpp \
			 ft_lstclear.cpp \
			 ft_lstdelone.cpp \
			 ft_lstadd_back.cpp \
			 ft_lstiter.cpp \
			 ft_lstadd_front.cpp \
			 ft_atol.cpp

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++11

OBJS = $(SRC:.cpp=.o)
BOBJS = $(BSRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
