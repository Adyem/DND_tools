NAME		= get_next_line_old.a

library		= get_next_line_old

SRC			= get_next_line_old.cpp \
			  get_next_line_utils_old.cpp

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17

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
