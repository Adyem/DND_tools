NAME		= dnd_tools

NAME_DEBUG	= dnd_tools_debug

HEADER		= include.h \
			  dnd_tools.h \
			  character.h \
			  template.h \
			  player_character.h \
			  initialize.h \
			  goblin.h \
			  veraak.h \
			  chaos_crystal.h \
			  chaos_goblin.h \
			  identification.h \
			  melee_weapons.h \
			  ranged_weapons.h \
			  armor.h

SRC			= name.c \
			  goblin.c \
			  chaos_goblin.c \
			  veraak.c \
			  veraak_turn.c \
			  chaos_crystal.c \
			  main.c \
			  template.c \
			  npc_stats.c \
			  npc_set_stats.c \
			  npc_change_stats_02.c \
			  npc_change_stats_03.c \
			  npc_change_stats_04.c \
			  npc_update_buff_01.c \
			  utils01.c \
			  utils02.c \
			  debug.c \
			  initiative_all.c \
			  initiative_pc.c \
			  initiative_request.c \
			  initiative_sort_1.c \
			  initiative_sort_2.c \
			  initiative.c \
			  free_memory.c \
			  read_file.c \
			  init_info.c \
			  save_data.c \
			  save_player.c \
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
			  roll_parse_md.c \
			  roll_parse_pm.c \
			  roll_parse_brackets.c \
			  fclean.c \
			  player.c \
			  concentration.c \
			  request_damage_taken.c \
			  saving_throw.c \
			  skill_throw.c \
			  deal_damage.c \
			  print_hp_status.c \
			  turn.c \
			  update_intiative_file.c \
			  npc_set_stats_string.c \
			  check_name.c \
			  cast_concentration.c \
			  free_info.c \
			  get_character_info.c \
			  resize_double_char.c \
			  concentration_remove_debuf.c \
			  check_buff_damage.c \
			  attack.c \
			  to_hit_check_buffs.c \
			  kill.c \
			  calculate_stats.c \
			  trim_start.c \
			  set_debuf.c \
			  cast_hunters_mark.c \
			  read_line.c \
			  calculate_skills.c \
			  calculate_resistance.c \
			  calculate_damage_reduction.c \
			  cast_chaos_armor.c \
			  cast_concentration_caster.c \
			  roll_parse_utils.c \
			  roll_dice.c \
			  create_data_folder.c \
			  cast_concentration_multi_target.c \
			  ordinal_suffix.c

CC          = gcc
CFLAGS      = -Wall -Werror -Wextra -g -O0

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libftprintf.a

OBJ_DIR     = ./objs
OBJ_DIR_DEBUG = ./objs_debug

ifeq ($(DEBUG),1)
    CFLAGS += -DDEBUG=1
    OBJ_DIR = $(OBJ_DIR_DEBUG)
    TARGET = $(NAME_DEBUG)
else
    TARGET = $(NAME)
endif

LDFLAGS     = -L$(LIBFT_DIR) -lftprintf -lreadline

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

debug:
	$(MAKE) all DEBUG=1

$(NAME) $(NAME_DEBUG): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_DEBUG)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean all

both: all debug

re_both: re both

.PHONY: all clean fclean re debug both re_both
