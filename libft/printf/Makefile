NAME		= printf.a

library		= printf

SRC			= ft_printf.cpp \
			  write_char.cpp \
			  write_number.cpp

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
