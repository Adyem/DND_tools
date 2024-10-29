NAME        = dnd_tools
NAME_DEBUG  = dnd_tools_debug

HEADER      = dnd_tools.hpp \
              character.hpp \
              template.hpp \
              player_character.hpp \
              initialize.hpp \
              goblin.hpp \
              veraak.hpp \
              chaos_crystal.hpp \
              chaos_goblin.hpp \
              identification.hpp \
              melee_weapons.hpp \
              ranged_weapons.hpp \
              armor.hpp \
              gundren_rockseeker.hpp \
              goblin_warmaster.hpp \
              maverick.hpp

SRC         = name.cpp \
              goblin.cpp \
              chaos_goblin.cpp \
              veraak.cpp \
              veraak_turn.cpp \
              maverick.cpp \
              maverick_turn.cpp \
              chaos_crystal.cpp \
              gundren_rockseeker.cpp \
              goblin_warmaster.cpp \
			  grizz.cpp \
              main.cpp \
              template.cpp \
              npc_stats.cpp \
              npc_set_stats.cpp \
              npc_change_stats_02.cpp \
              npc_change_stats_03.cpp \
              npc_change_stats_04.cpp \
              npc_update_buff_01.cpp \
              utils01.cpp \
              utils02.cpp \
              debug.cpp \
              initiative_all.cpp \
              initiative_pc.cpp \
              initiative_request.cpp \
              initiative_sort_1.cpp \
              initiative_sort_2.cpp \
              initiative.cpp \
              free_memory.cpp \
              read_file.cpp \
              init_info.cpp \
              save_data.cpp \
              save_player.cpp \
              check_data.cpp \
              check_buff_attack.cpp \
              check_buff_save.cpp \
              check_buff_skill.cpp \
              check_buff_general.cpp \
              update_buff.cpp \
              update_buff_special.cpp \
              update_lightning_strike.cpp \
              to_hit.cpp \
              read_line_check.cpp \
              roll.cpp \
              roll_utilities.cpp \
              roll_parse_dice.cpp \
              roll_validate_string.cpp \
              roll_validate_utils.cpp \
              roll_parse_md.cpp \
              roll_parse_pm.cpp \
              roll_parse_brackets.cpp \
              fclean.cpp \
              player.cpp \
              concentration.cpp \
              request_damage_taken.cpp \
              saving_throw.cpp \
              skill_throw.cpp \
              deal_damage.cpp \
              print_hp_status.cpp \
              turn.cpp \
              update_intiative_file.cpp \
              npc_set_stats_string.cpp \
              check_name.cpp \
              cast_concentration.cpp \
              free_info.cpp \
              get_character_info.cpp \
              resize_double_char.cpp \
              concentration_remove_debuf.cpp \
              check_buff_damage.cpp \
              attack.cpp \
              to_hit_check_buffs.cpp \
              kill.cpp \
              calculate_stats.cpp \
              trim_start.cpp \
              set_debuf.cpp \
              cast_hunters_mark.cpp \
              read_line.cpp \
              calculate_skills.cpp \
              calculate_resistance.cpp \
              calculate_damage_reduction.cpp \
              cast_chaos_armor.cpp \
              cast_concentration_caster.cpp \
              roll_parse_utils.cpp \
              roll_dice.cpp \
              create_data_folder.cpp \
              cast_concentration_multi_target_01.cpp \
              ordinal_suffix.cpp \
              check_equipment.cpp \
              test.cpp \
              test_make_input.cpp \
              initialize_suggestions_readline.cpp \
              test_excecute.cpp \
              print_abilities.cpp \
              get_pc_list.cpp \
              get_random_target.cpp \
              npc_set_stats_player.cpp \
			  feats.cpp

CC          = g++
CFLAGS      = -Wall -Werror -Wextra -g -O0 -std=c++17

LIBFT_DIR   = ./libft

OBJ_DIR     = ./objs
OBJ_DIR_DEBUG = ./objs_debug

ifeq ($(DEBUG),1)
    CFLAGS += -DDEBUG=1
    OBJ_DIR = $(OBJ_DIR_DEBUG)
    TARGET = $(NAME_DEBUG)
    LIBFT = $(LIBFT_DIR)/Full_Libft_debug.a
else
    TARGET = $(NAME)
    LIBFT = $(LIBFT_DIR)/Full_Libft.a
endif

LDFLAGS     = $(LIBFT) -lreadline

OBJS        = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

debug:
	$(MAKE) all DEBUG=1

$(TARGET): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) $(if $(DEBUG), debug)

$(OBJ_DIR)/%.o: %.cpp $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_DEBUG)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean all

both: all debug

re_both: re both

.PHONY: all clean fclean re debug both re_both
