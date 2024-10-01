NAME			= libftprintf.a

library			= libftprintf

LIBFT_DIR			= libft
PRINTF_DIR			= printf
GET_NEXT_LINE_DIR	= get_next_line
PRINTF_FD_DIR		= printf_fd

LIBFT				= $(LIBFT_DIR)/libft.a
PRINTF				= $(PRINTF_DIR)/printf.a
GET_NEXT_LINE		= $(GET_NEXT_LINE_DIR)/get_next_line.a
PRINTF_FD			= $(PRINTF_FD_DIR)/printf_fd.a

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(GET_NEXT_LINE) $(PRINTF_FD)
	cp $(LIBFT) $(NAME)
	ar -x $(PRINTF)
	ar -x $(GET_NEXT_LINE)
	ar -x $(PRINTF_FD)
	ar -rs $(NAME) *.o

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(PRINTF_FD):
	$(MAKE) -C $(PRINTF_FD_DIR)

$(GET_NEXT_LINE):
	$(MAKE) -C $(GET_NEXT_LINE_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR)  fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean
	$(MAKE) -C $(PRINTF_FD_DIR) fclean
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
