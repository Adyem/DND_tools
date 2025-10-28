ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
else
    EXE_EXT :=
endif

NAME        = dnd_tools$(EXE_EXT)
NAME_DEBUG  = dnd_tools_debug$(EXE_EXT)
TEST_NAME   = automated_tests$(EXE_EXT)

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
                          command_builtins.hpp \
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
			  snow_goblin_shaman.hpp \
			  mannoroth.hpp

SRC         = name.cpp \
			  snow_goblin_shaman.cpp \
			  felguard.cpp \
			  mannoroth.cpp \
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
              utils02.cpp \
              debug.cpp \
			  add_element.cpp \
                          fetch_target.cpp \
                          remove_concentration.cpp \
                          initialize.cpp \
                          initialize_character_template.cpp \
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
              nightmare_claw_effect.cpp \
              check_buff_attack.cpp \
              check_buff_save.cpp \
              check_buff_skill.cpp \
              check_buff_general.cpp \
              update_buff.cpp \
              update_buff_special.cpp \
              update_lightning_strike.cpp \
              to_hit.cpp \
              readline_check.cpp \
              command_builtins.cpp \
              roll.cpp \
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
              check_buff_damage.cpp \
              attack.cpp \
              to_hit_check_buffs.cpp \
              kill.cpp \
              calculate_stats.cpp \
              trim_start.cpp \
              set_debuf.cpp \
              cast_hunters_mark.cpp \
              read_file_lines.cpp \
              read_line.cpp \
              calculate_skills.cpp \
              calculate_resistance.cpp \
              calculate_damage_reduction.cpp \
              cast_chaos_armor.cpp \
              cast_concentration_caster.cpp \
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
              print_items.cpp \
              get_pc_list.cpp \
              get_random_target.cpp \
              npc_set_stats_player.cpp \
              crackback.cpp \
              frank.cpp \
                          cast_divine_smite.cpp \
                          divine_smite_utils.cpp \
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

MAKEFLAGS  += --no-print-directory

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
SUBMODULE_SENTINEL = $(LIBFT_DIR)/Makefile

OBJ_DIR         = ./objs
OBJ_DIR_DEBUG   = ./objs_debug
OBJ_DIR_TEST    = ./objs_tests

MODULE_NAME         = DND_tools
MODULE_NAME_TESTS   = DND_tools Tests

TOTAL_SRCS       = $(words $(SRC))
TOTAL_TEST_SRCS  = $(words $(TEST_SRC))

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
    LIBFT_MAKE_TARGET = debug
else
    TARGET     = $(NAME)
    LIBFT      = $(LIBFT_DIR)/Full_Libft.a
    LIBFT_MAKE_TARGET = all
endif

export COMPILE_FLAGS

ifeq ($(OS),Windows_NT)
    LDFLAGS     = $(LIBFT)
else
    LDFLAGS     = $(LIBFT) -lreadline -pthread -lsqlite3 -lssl -lcrypto
endif

OBJS        = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

TEST_SRC    = tests/automated_tests.cpp \
              tests/test_support.cpp \
              tests/string_prefix_tests.cpp \
              tests/ordinal_suffix_tests.cpp \
             tests/roll_validation_tests.cpp \
             tests/roll_command_tests.cpp \
             tests/roll_command_argument_tests.cpp \
             tests/roll_command_expression_tests.cpp \
             tests/roll_command_error_tests.cpp \
             tests/dice_roll_tests.cpp \
             tests/clean_tests.cpp \
             tests/check_name_tests.cpp \
             tests/check_equipment_tests.cpp \
             tests/check_buff_tests.cpp \
             tests/attack_utils_tests.cpp \
             tests/attack_prompt_tests.cpp \
             tests/command_builtin_tests.cpp \
             tests/npc_command_tests.cpp \
             tests/command_builtin_stubs.cpp \
             tests/resistance_tests.cpp \
             tests/calculate_damage_reduction_tests.cpp \
             tests/calculate_stats_tests.cpp \
             tests/calculate_skills_tests.cpp \
             tests/calculate_util_stats_tests.cpp \
             tests/divine_smite_tests.cpp \
             tests/concentration_tests.cpp \
             tests/concentration_test_stubs.cpp \
             tests/set_debuf_tests.cpp \
             tests/npc_check_info_tests.cpp \
             tests/deal_damage_tests.cpp \
             tests/initiative_sort_tests.cpp \
             deal_damage.cpp \
             initiative_sort_1.cpp \
             initiative_sort_2.cpp \
             free_memory.cpp \
             free_info.cpp \
             attack_utils.cpp \
             attack_prompt_action.cpp \
             attack_readline_prompt.cpp \
             spell_utils.cpp \
             readline_check.cpp \
             command_builtins.cpp \
             read_file_lines.cpp \
             fclean.cpp \
             tests/spell_utils_tests.cpp \
             tests/create_data_folder_tests.cpp \
             tests/get_pc_list_tests.cpp \
             tests/add_element_tests.cpp \
             tests/save_load_test_stubs.cpp \
              tests/save_load_tests.cpp \
             npc_change_stats_02.cpp \
             cast_divine_smite.cpp \
             divine_smite_utils.cpp \
             trim_start.cpp \
             set_debuf.cpp \
             ordinal_suffix.cpp \
             roll.cpp \
             roll_dice.cpp \
             create_data_folder.cpp \
             add_element.cpp \
             save_player.cpp \
             save_data.cpp \
              npc_stats.cpp \
              init_info.cpp \
              npc_set_stats.cpp \
              npc_set_stats_string.cpp \
             npc_set_stats_player.cpp \
             initialize.cpp \
             fetch_target.cpp \
             get_character_info.cpp \
             get_pc_list.cpp \
             initialize_key_value_pairs.cpp \
             treeNode.cpp \
             treeNode_functions.cpp \
             check_data.cpp \
             calculate_resistance.cpp \
             calculate_damage_reduction.cpp \
             calculate_stats.cpp \
             calculate_skills.cpp \
             calculate_util_stats.cpp \
             check_equipment.cpp \
             check_name.cpp \
             check_buff_attack.cpp \
             check_buff_save.cpp \
             check_buff_skill.cpp \
             check_buff_general.cpp \
             check_buff_damage.cpp \
             update_buff.cpp \
             update_buff_special.cpp \
             skill_throw.cpp \
             update_buff_healing.cpp \
             cast_concentration_caster.cpp \
             utils02.cpp \
             initiative_pc.cpp

TEST_OBJS   = $(TEST_SRC:%.cpp=$(OBJ_DIR_TEST)/%.o)

all: ensure_libft dirs $(TARGET)

tests: ensure_libft dirs $(TEST_NAME)

dirs:
	@-$(MKDIR) $(OBJ_DIR)
	@-$(MKDIR) $(OBJ_DIR_DEBUG)
	@-$(MKDIR) $(OBJ_DIR_TEST)
	@printf '        [$(MODULE_NAME)] Build directories ready\n'

debug:
	@printf '        [$(MODULE_NAME)] Building debug configuration\n'
	@$(MAKE) all DEBUG=1

$(TARGET): $(LIBFT) $(OBJS)
	@printf '        [$(MODULE_NAME)] Linking executable %s\n' "$@"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@printf '        [$(MODULE_NAME)] Build complete\n'

$(TEST_NAME): $(LIBFT) $(TEST_OBJS)
	@printf '        [$(MODULE_NAME_TESTS)] Linking executable %s\n' "$@"
	@$(CC) $(CFLAGS) $(TEST_OBJS) -o $@ $(LDFLAGS)
	@printf '        [$(MODULE_NAME_TESTS)] Build complete\n'

$(LIBFT): ensure_libft
	@if $(MAKE) -C $(LIBFT_DIR) $(LIBFT_MAKE_TARGET) --question >/dev/null 2>&1; then \
                printf '        [Libft] Library up to date\n'; \
        else \
                printf '        [Libft] Rebuilding library\n'; \
                $(MAKE) -C $(LIBFT_DIR) $(LIBFT_MAKE_TARGET); \
        fi

initialize:
	@printf '        [$(MODULE_NAME)] Initializing submodules\n'
	@git submodule update --init --recursive

ensure_libft:
	@if [ ! -f $(SUBMODULE_SENTINEL) ]; then \
		printf '        [Libft] Submodule missing. Initializing automatically.\n'; \
		git submodule update --init --recursive $(LIBFT_DIR); \
	fi
	@if [ ! -f $(SUBMODULE_SENTINEL) ]; then \
		printf '        [Libft] Submodule initialization failed. Run "make initialize" manually.\n'; \
		exit 1; \
	fi

$(OBJ_DIR)/%.o: %.cpp $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@count=$$(find $(OBJ_DIR) -maxdepth 1 -name '*.o' 2>/dev/null | wc -l); \
                printf '        [$(MODULE_NAME)] Files built: %d/%d\n' $$count $(TOTAL_SRCS)

$(OBJ_DIR_TEST)/%.o: %.cpp $(HEADER)
	@-$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@count=$$(find $(OBJ_DIR_TEST) -name '*.o' 2>/dev/null | wc -l); \
                printf '        [$(MODULE_NAME_TESTS)] Files built: %d/%d\n' $$count $(TOTAL_TEST_SRCS)

clean:
	@-$(RM) $(OBJ_DIR)/*.o $(OBJ_DIR_DEBUG)/*.o
	@-$(RM) $(OBJ_DIR_TEST)/*.o $(OBJ_DIR_TEST)/tests/*.o
	@if [ -f $(SUBMODULE_SENTINEL) ]; then \
                printf '        [Libft] Cleaning submodule\n'; \
                $(MAKE) -C $(LIBFT_DIR) fclean; \
        else \
                printf '        [Libft] Skipping clean, submodule missing. Run "make initialize".\n'; \
        fi
	@printf '        [$(MODULE_NAME)] clean: complete\n'

fclean: clean
	@-$(RM) $(NAME) $(NAME_DEBUG) $(TEST_NAME)
	@-$(RMDIR) $(OBJ_DIR) $(OBJ_DIR_DEBUG) $(OBJ_DIR_TEST) data
	@printf '        [$(MODULE_NAME)] fclean: complete\n'

re: fclean all

test: $(TEST_NAME)
	@printf '        [$(MODULE_NAME_TESTS)] Running automated tests\n'
	@./$(TEST_NAME)

both: all debug

re_both: re both

.PHONY: all dirs clean fclean re debug both re_both tests test initialize ensure_libft
