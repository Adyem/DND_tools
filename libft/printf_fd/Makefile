NAME		= printf_fd.a

library		= printf_fd

SRC			= ft_printf_fd.cpp \
			  write_char_fd.cpp \
			  write_number_fd.cpp

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++11

OBJS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
