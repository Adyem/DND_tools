NAME		= dnd_tools

NAME_DEBUG	= dnd_tools_debug

HEADER		= include.h \
			  dnd_tools.h \
			  character.h \
			  maverick.h \
			  zephyr.h \
			  air_totem.h \
			  air_goblin.h \
			  air_goblin_shaman.h \
			  goblin.h \
			  grizzletooth.h

SRC			= name.c \
			  dnd_tools.c \
			  maverick.c \
			  maverick_turn.c \
			  zephyr.c \
			  zephyr_turn.c \
			  air_totem.c \
			  air_goblin.c \
			  goblin.c \
			  grizzletooth.c \
			  air_goblin_shaman.c \
			  npc_stats.c \
			  npc_set_stats.c \
			  npc_change_stats.c \
			  npc_update_buff_01.c \
			  utils01.c \
			  utils02.c \
			  debug.c \
			  initiative.c \
			  free_memory.c \
			  read_file.c \
			  init_info.c \
			  save_data.c \
			  check_data.c \
			  check_buff_attack.c \
			  check_buff_save.c \
			  check_buff_skill.c \
			  check_buff_general.c \
			  update_buff.c \
			  update_buff_special.c \
			  update_lightning_strike.c \
			  to_hit.c \
			  read_line_check.c \
			  roll.c \
			  roll_utilities.c \
			  roll_parse_dice.c \
			  roll_validate_string.c \
			  roll_validate_utils.c \
			  fclean.c

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libftprintf.a
OBJ_DIR		= ./objs

LDFLAGS		= -L$(LIBFT_DIR) -lftprintf -lreadline

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

debug: CFLAGS += -DDEBUG=1
debug: $(NAME_DEBUG)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(NAME_DEBUG): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME_DEBUG) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re debug windows
