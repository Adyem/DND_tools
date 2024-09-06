NAME		= get_next_line.a

library		= get_next_line

SRC			= get_next_line.c \
			  get_next_line_utils.c

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++11

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
