ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
else
    EXE_EXT :=
endif

NAME        = dnd_tools$(EXE_EXT)
NAME_DEBUG  = dnd_tools_debug$(EXE_EXT)

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
              maverick.hpp \
              frank.hpp \
              grizz.hpp \
			  ghost.hpp \
			  dorgar_stoneguard.hpp \
			  hilda_stormshield.hpp \
			  murna_claygrip.hpp \
			  thorbald_ironpocket.hpp \
			  key_list.hpp \
			  treeNode.hpp \
			  dwarf_paladin.hpp \
			  felbeast.hpp \
			  ancient_predatory_beast.hpp \
			  snow_goblin.hpp \
              night_elven_guard.hpp \
              xavius.hpp \
              shadow_illusion.hpp \
              malfurion.hpp \
			  demonic_portal_a.hpp \
			  shield_spell_a.hpp \
			  felguard.hpp \
			  snow_goblin_shaman.hpp

SRC         = name.cpp \
			  snow_goblin_shaman.cpp \
			  felguard.cpp \
              goblin.cpp \
              chaos_goblin.cpp \
              veraak.cpp \
              veraak_turn.cpp \
              maverick.cpp \
			  snow_goblin.cpp \
              maverick_turn.cpp \
              chaos_crystal.cpp \
			  dwarf_paladin.cpp \
              gundren_rockseeker.cpp \
			  dorgar_stoneguard.cpp \
			  hilda_stormshield.cpp \
			  murna_claygrip.cpp \
			  thorbald_ironpocket.cpp \
              goblin_warmaster.cpp \
			  ancient_predatory_beast.cpp \
			  night_elven_guard.cpp \
              grizz.cpp \
			  ghost.cpp \
              main.cpp \
              template.cpp \
              npc_stats.cpp \
              npc_set_stats.cpp \
              npc_change_stats_02.cpp \
              npc_change_stats_03.cpp \
              npc_change_stats_04.cpp \
              npc_update_buff_01.cpp \
              growth_stack.cpp \
              utils01.cpp \
              utils02.cpp \
              debug.cpp \
			  add_element.cpp \
			  fetch_target.cpp \
			  remove_concentration.cpp \
			  initialize.cpp \
			  remove_element.cpp \
			  open.cpp \
              initiative_all.cpp \
              initiative_pc.cpp \
              initiative_request.cpp \
              initiative_sort_1.cpp \
              initiative_sort_2.cpp \
              initiative.cpp \
              free_memory.cpp \
              init_info.cpp \
              save_data.cpp \
              save_player.cpp \
              check_data.cpp \
			  shadow_claw_effect.cpp \
              check_buff_attack.cpp \
              check_buff_save.cpp \
              check_buff_skill.cpp \
              check_buff_general.cpp \
              update_buff.cpp \
              update_buff_special.cpp \
              update_lightning_strike.cpp \
              to_hit.cpp \
              readline_check.cpp \
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
              cast_concentration_multi_target_02.cpp \
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
              crackback.cpp \
              frank.cpp \
			  cast_divine_smite.cpp \
			  cast_cure_wounds.cpp \
              cast_lightning_bolt.cpp \
			  spell_utils.cpp \
			  initialize_key_value_pairs.cpp \
			  cast_bless.cpp \
			  attack_prompt_action.cpp \
			  attack_readline_prompt.cpp \
			  attack_utils.cpp \
			  calculate_util_stats.cpp \
			  treeNode.cpp \
			  treeNode_functions.cpp \
			  felbeast.cpp \
			  cast_magic_drain.cpp \
			  attack_additional_effects.cpp \
			  fel_poison_weapon_effects.cpp \
			  ancient_predatory_beast_weapon_effects.cpp \
			  slow_weapon_effect.cpp \
              strength_drain_wand.cpp \
              xavius.cpp \
              shadow_illusion.cpp \
              malfurion.cpp \
			  demonic_portal_a.cpp \
              shield_spell_a.cpp \
              encounter.cpp \
              update_buff_healing.cpp \
              help.cpp

CC          = g++

OPT_LEVEL ?= 0

ifeq ($(OPT_LEVEL),0)
	OPT_FLAGS = -O0 -g
else ifeq ($(OPT_LEVEL),1)
	OPT_FLAGS = -O1 -flto -s -ffunction-sections -fdata-sections -Wl,--gc-sections
else ifeq ($(OPT_LEVEL),2)
	OPT_FLAGS = -O2 -flto -s -ffunction-sections -fdata-sections -Wl,--gc-sections
else ifeq ($(OPT_LEVEL),3)
	OPT_FLAGS = -O3 -flto -s -ffunction-sections -fdata-sections -Wl,--gc-sections
else
	$(error Unsupported OPT_LEVEL=$(OPT_LEVEL))
endif

COMPILE_FLAGS = -Wall -Werror -Wextra -std=c++17 -Wmissing-declarations \
				-Wold-style-cast -Wshadow -Wconversion -Wformat=2 -Wundef \
				-Wfloat-equal -Wconversion -Wodr -Wuseless-cast \
				-Wzero-as-null-pointer-constant -Wmaybe-uninitialized $(OPT_FLAGS)

CFLAGS = $(COMPILE_FLAGS)

ifeq ($(OS),Windows_NT)
    MKDIR   = mkdir
    RMDIR   = rmdir /S /Q
    RM      = del /F /Q
else
    MKDIR   = mkdir -p
    RMDIR   = rm -rf
    RM      = rm -f
endif

LIBFT_DIR   = ./libft

OBJ_DIR         = ./objs
OBJ_DIR_DEBUG   = ./objs_debug

ENABLE_LTO  ?= 0
ENABLE_PGO  ?= 0
export ENABLE_LTO ENABLE_PGO

ifeq ($(ENABLE_LTO),1)
    COMPILE_FLAGS   += -flto
    LDFLAGS  += -flto
endif

ifeq ($(ENABLE_PGO),1)
    COMPILE_FLAGS  += -fprofile-generate
endif

ifeq ($(DEBUG),1)
    CFLAGS    += -DDEBUG=1
    OBJ_DIR    = $(OBJ_DIR_DEBUG)
    TARGET     = $(NAME_DEBUG)
    LIBFT      = $(LIBFT_DIR)/Full_Libft_debug.a
else
    TARGET     = $(NAME)
    LIBFT      = $(LIBFT_DIR)/Full_Libft.a
endif

export COMPILE_FLAGS

ifeq ($(OS),Windows_NT)
    LDFLAGS     = $(LIBFT)
else
    LDFLAGS     = $(LIBFT) -lreadline
endif

OBJS        = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: dirs $(TARGET)

dirs:
	-$(MKDIR) $(OBJ_DIR)
	-$(MKDIR) $(OBJ_DIR_DEBUG)

debug:
	$(MAKE) all DEBUG=1

$(TARGET): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) $(if $(DEBUG), debug)

$(OBJ_DIR)/%.o: %.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJ_DIR)/*.o $(OBJ_DIR_DEBUG)/*.o
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	-$(RM) $(NAME) $(NAME_DEBUG)
	-$(RMDIR) $(OBJ_DIR) $(OBJ_DIR_DEBUG) data

re: fclean all

both: all debug

re_both: re both

.PHONY: all dirs clean fclean re debug both re_both
