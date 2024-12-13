#ifndef DND_TOOLS_H
# define DND_TOOLS_H

#include "libft/CPP_class/string.hpp"
class ft_file;

#include <cstdio>
#include "character.hpp"
#include "player_character.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define MAX_ERROR_COUNT 5
# define MAX_PLAYERS 8
# define CRIT_SUCCES 999
# define CRIT_FAIL -999

extern bool dnd_test;

//NPC
void		ft_npc_change_stats(SharedPtr<t_char>info, int index, const char **input);
void		ft_npc_set_stat(SharedPtr<t_char>info, const char **input);
int			ft_npc_open_file(SharedPtr<t_char>info);
void		ft_npc_init_stats(SharedPtr<t_char>info);

//Template
SharedPtr<t_char>ft_template(const int index, const char **input, t_name *name, int exception);
void		ft_template_turn(SharedPtr<t_char>info);

//Ghost
SharedPtr<t_char>ft_ghost(const int index, const char **input, t_name *name, int exception);
void		ft_ghost(SharedPtr<t_char>info);

//Frank
SharedPtr<t_char>ft_frank(const int index, const char **input, t_name *name, int exception);
void		ft_frank_turn(SharedPtr<t_char>info);

//Goblin Warmaster
SharedPtr<t_char>ft_goblin_warmaster(const int index, const char **input, t_name *name,
				int exception);
void		ft_goblin_warmaster_turn(SharedPtr<t_char>info);

// Gundren Rockseeker
SharedPtr<t_char>ft_gundren_rockseeker(const int index, const char **input, t_name *name,
				int exception);
void		ft_gundren_rockseeker_turn(SharedPtr<t_char>info);

// Thorbald Ironpocket
SharedPtr<t_char>ft_thorbald_ironpocket(const int index, const char **input, t_name *name,
				int exception);
void		ft_thorbald_ironpocket_turn(SharedPtr<t_char>info);

// Murna Claygrip
SharedPtr<t_char>ft_murna_claygrip(const int index, const char **input, t_name *name,
				int exception);
void		ft_murna_claygrip_turn(SharedPtr<t_char>info);

// Dorgar Stoneguard
SharedPtr<t_char>ft_dorgar_stoneguard(const int index, const char **input, t_name *name,
				int exception);
void		ft_dorgar_stoneguard_turn(SharedPtr<t_char>info);

// Hilda Stormshield
SharedPtr<t_char>ft_hilda_stormshield(const int index, const char **input, t_name *name,
				int exception);
void		ft_hilda_stormshield_turn(SharedPtr<t_char>info);

//Gundren Rockseeker
SharedPtr<t_char>ft_gundren_rockseeker(const int index, const char **input, t_name *name,
				int exception);
void		ft_gundren_rockseeker_turn(SharedPtr<t_char>info);

//Goblin
SharedPtr<t_char>ft_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_goblin_turn(SharedPtr<t_char>info);

//Chaos Goblin
SharedPtr<t_char>ft_chaos_crystal(const int index, const char **input, t_name *name, int exception);
void		ft_chaos_crystal_turn(SharedPtr<t_char>info);

//Chaos Crystal
SharedPtr<t_char>ft_chaos_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_chaos_goblin_turn(SharedPtr<t_char>info);

//Grizz
SharedPtr<t_char>ft_grizz(const int index, const char **input, t_name *name, int exception);
void		ft_grizz_turn(SharedPtr<t_char>info);

//Veraak
SharedPtr<t_char>ft_veraak(const int index, const char **input, t_name *name, int exception);
void		ft_veraak_check_phase(SharedPtr<t_char>info);
void		ft_veraak_turn(SharedPtr<t_char>info);

//Maverick
SharedPtr<t_char>ft_maverick(const int index, const char **input, t_name *name, int exception);
void		ft_maverick_turn(SharedPtr<t_char>info);
void		ft_maverick_print_s(int first, int second, SharedPtr<t_char>info, char **player_list);
void		ft_maverick_print_f(int first, int second, SharedPtr<t_char>info, char **player_list);

//Commands
void		ft_request_input(t_name *name);

//Print Abilities
void		print_meteor_strike(const SharedPtr<t_char>info);
void		print_lightning_strike(const SharedPtr<t_char>info);
void		print_flame_geyser(const SharedPtr<t_char>info);
void		print_frost_breath(const SharedPtr<t_char>info);
void		print_lightning_strike_v2(const SharedPtr<t_char>info);
void		print_arcane_pounce(const SharedPtr<t_char>info);
void		print_earth_pounce(const SharedPtr<t_char>info);

//Tester
void		ft_test(t_name *name);
int			ft_test_excecute(const char **input, int argc, t_name *name);

//Tester Make input strings
void		ft_excecute_test(const char *string1, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3,
				t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3,
				const char *string4, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3,
				const char *string4, const char *string5, t_name *name);

//Turn
void		ft_turn_next(t_name *name);

//attack
void		ft_weapon_attack(SharedPtr<t_char>info, t_equipment_id *weapon, int offhand);

//buff update
void		ft_npc_update_buff(SharedPtr<t_char>info, const char **input, int *buff, const char *name);
void		ft_update_buff_status(SharedPtr<t_char>info, int current_dur, int duration,
				const char *buff_name);

//damage buffs
int			ft_check_buff_damage(SharedPtr<t_char>info);

//saving throws buffs
int			ft_save_check_buff(SharedPtr<t_char>info, int *roll, const char *ability_score);

//attack rolls buffs
int			ft_attack_roll_check_buffs(SharedPtr<t_char>info, int *roll);

//to_hit check buffs
void		ft_to_hit_check_buff(SharedPtr<t_char>info);

//cast spell
void		ft_cast_divine_smite(SharedPtr<t_char>character);

//spells utils
int			ft_prompt_spell_level(SharedPtr<t_char>character, int base_level);
int			ft_calculate_spell_damage(int total_dice, int dice_faces, int extra_damage);
void		ft_remove_spell_slot(t_spell_slots *spell_slots, int level_spell_used);

//calculate stats
int			ft_calculate_str(SharedPtr<t_char>info);
int			ft_calculate_dex(SharedPtr<t_char>info);
int			ft_calculate_con(SharedPtr<t_char>info);
int			ft_calculate_inte(SharedPtr<t_char>info);
int			ft_calculate_wis(SharedPtr<t_char>info);
int			ft_calculate_cha(SharedPtr<t_char>info);
int			ft_calculate_ac(SharedPtr<t_char>info);

//calculate skill mods
int			ft_calculate_athletics(SharedPtr<t_char>info);
int			ft_calculate_acrobatics(SharedPtr<t_char>info);
int			ft_calculate_sleight_of_hand(SharedPtr<t_char>info);
int			ft_calculate_stealth(SharedPtr<t_char>info);
int			ft_calculate_arcana(SharedPtr<t_char>info);
int			ft_calculate_history(SharedPtr<t_char>info);
int			ft_calculate_investigation(SharedPtr<t_char>info);
int			ft_calculate_nature(SharedPtr<t_char>info);
int			ft_calculate_religion(SharedPtr<t_char>info);
int			ft_calculate_animal_handling(SharedPtr<t_char>info);
int			ft_calculate_insight(SharedPtr<t_char>info);
int			ft_calculate_medicine(SharedPtr<t_char>info);
int			ft_calculate_perception(SharedPtr<t_char>info);
int			ft_calculate_survival(SharedPtr<t_char>info);
int			ft_calculate_deception(SharedPtr<t_char>info);
int			ft_calculate_intimidation(SharedPtr<t_char>info);
int			ft_calculate_performance(SharedPtr<t_char>info);
int			ft_calculate_persuasion(SharedPtr<t_char>info);

//calculate resistance
int			ft_calculate_acid_resistance(SharedPtr<t_char>info);
int			ft_calculate_bludgeoning_resistance(SharedPtr<t_char>info);
int			ft_calculate_cold_resistance(SharedPtr<t_char>info);
int			ft_calculate_fire_resistance(SharedPtr<t_char>info);
int			ft_calculate_force_resistance(SharedPtr<t_char>info);
int			ft_calculate_lightning_resistance(SharedPtr<t_char>info);
int			ft_calculate_necrotic_resistance(SharedPtr<t_char>info);
int			ft_calculate_piercing_resistance(SharedPtr<t_char>info);
int			ft_calculate_poison_resistance(SharedPtr<t_char>info);
int			ft_calculate_psychic_resistance(SharedPtr<t_char>info);
int			ft_calculate_radiant_resistance(SharedPtr<t_char>info);
int			ft_calculate_slashing_resistance(SharedPtr<t_char>info);
int			ft_calculate_thunder_resistance(SharedPtr<t_char>info);

//calculate damage reduction
int			ft_calculate_acid_dr(SharedPtr<t_char>info);
int			ft_calculate_bludgeoning_dr(SharedPtr<t_char>info);
int			ft_calculate_cold_dr(SharedPtr<t_char>info);
int			ft_calculate_fire_dr(SharedPtr<t_char>info);
int			ft_calculate_force_dr(SharedPtr<t_char>info);
int			ft_calculate_lightning_dr(SharedPtr<t_char>info);
int			ft_calculate_necrotic_dr(SharedPtr<t_char>info);
int			ft_calculate_piercing_dr(SharedPtr<t_char>info);
int			ft_calculate_poison_dr(SharedPtr<t_char>info);
int			ft_calculate_psychic_dr(SharedPtr<t_char>info);
int			ft_calculate_radiant_dr(SharedPtr<t_char>info);
int			ft_calculate_slashing_dr(SharedPtr<t_char>info);
int			ft_calculate_thunder_dr(SharedPtr<t_char>info);

//damage
void		ft_deal_damage(SharedPtr<t_char>info, const char *input, const char *d_type, int resistance,
				int concentration);
int			ft_request_damage(SharedPtr<t_char>info);

//skill roll buffs
int			ft_skill_check_buff(SharedPtr<t_char>info, int *roll, const char *skill);

//change stats
void		ft_npc_sstuff(SharedPtr<t_char>info, const char **input);
void		ft_change_stats_04(SharedPtr<t_char>info, const char **input);
void		ft_kill(SharedPtr<t_char>info);

//update debuf
void		ft_set_debuf_blinded(SharedPtr<t_char>info, const char **input);

//update buff
void		ft_update_buf(SharedPtr<t_char>info);
void		ft_update_lightning_strike(SharedPtr<t_char>info);
void		ft_update_lightningV2_strike(SharedPtr<t_char>info);
void		ft_npc_update_lightning_strike(SharedPtr<t_char>info, const char **input);
void		ft_update_flame_geyser(SharedPtr<t_char>info);
void		ft_update_meteor_strike(SharedPtr<t_char>info);
void		ft_update_earth_pounce(SharedPtr<t_char>info);
void		ft_update_arcane_pounce(SharedPtr<t_char>info);
void		ft_update_frost_breath(SharedPtr<t_char>info);

//feats
void		ft_crackback(SharedPtr<t_char>info, int number);

//general buffs
int			ft_check_bless(SharedPtr<t_char>info);

//concentration
void		ft_cast_hunters_mark(SharedPtr<t_char>info, const char **input);
int			ft_cast_concentration(SharedPtr<t_char>info, const char **input, t_buff *buff);
void		ft_check_concentration(SharedPtr<t_char>info, int  damage);
int			ft_remove_concentration(SharedPtr<t_char>info);
void		ft_cast_chaos_armor(SharedPtr<t_char>info);
int			ft_update_caster_name(char ***caster_name, const char *input_name);
void		ft_cast_concentration_multi_target_01(SharedPtr<t_char>info, t_buff *buff,
				const char **input);
void		ft_cast_concentration_multi_target_02(SharedPtr<t_char>info, t_target_data *target_data,
				const char **input);

//hunters mark
void		ft_concentration_remove_hunters_mark(SharedPtr<t_char>character, t_target_data *targets_data);
int			ft_cast_hunters_mark_apply_debuf(SharedPtr<t_char>target, const char **input, t_buff *buff);

//resistance
int			ft_get_resistance(SharedPtr<t_char>info, const char *type);

//advantage or disadvantage
void		ft_reroll(SharedPtr<t_char>info, int *result);

//open and read
char		**ft_read_file_lines(ft_file &file);
char		**ft_open_and_read_file(const char *file_name);
int			ft_open_file_write_only(const char *filename, ft_file &file);

//utils
int			ft_create_data_dir();
int			ft_strcmp_dnd(const char *string1, const char *string2);
int			ft_initialize_info(SharedPtr<t_char>info, char **content);
int			ft_check_value(const char *input);
void		ft_print_character_status(SharedPtr<t_char>info, int number, int temp);
void		ft_skill_throw(SharedPtr<t_char>info, const char *skill, int ability_mod, int save_mod);
int			ft_set_stats(SharedPtr<t_char>info, char **content);
int			ft_check_stat(SharedPtr<t_char>info, const char *stat, const int index);
char		**ft_set_stats_con_targets(char *content, int ofset, char **data, SharedPtr<t_char>info);
SharedPtr<t_char>ft_get_info(const char *tf_name, t_name *name);
char		**ft_resize_double_char(char **double_string, const char *string, int size);
int			ft_double_char_length(const char **double_char);
void		ft_dual_save_file(SharedPtr<t_char>info, SharedPtr<t_char>target);
char		*ft_strtrim_prefix(const char *s1, const char *prefix);
const char	*ft_ordinal_suffix(int number);
int			ft_check_equipment_slots(SharedPtr<t_char>character);
void		ft_initialize_suggestions_readline();
char		**ft_get_pc_list();
void		ft_remove_element(char **array, char *element, bool free_element);
void		ft_add_element(const char ***array, const char *element, bool critical);
void		ft_get_random_target(char **player_list, char **target_field);
int			ft_check_player_entry(const char *entry);
int			ft_set_stat_player(size_t key_len, const char **field, const char *content);
int			ft_check_write_permissions(const char *filepath);
SharedPtr<t_char>ft_validate_and_fetch_target(char *target_name, SharedPtr<t_char>info, int *error_code);
void		ft_initialize_variables(t_target_data *target_data);

//check name
int			ft_set_stats_check_name(const char *name);
int			ft_check_player_character(const char *name);

//readline checks
int			ft_readline_confirm(const char *mesage);
int			ft_readline_spell_level(const char *message, SharedPtr<t_char>character,
				int *invalid_input_amount);

//dice rolling
int			ft_saving_throw(SharedPtr<t_char>info, const char *ability_score, int ability_mod, int save_mod);
int			ft_dice_roll(int number, int faces);

//free memory
void		ft_free_pc(t_pc *player);
int			ft_free_players(t_pc *players);
void		ft_free_info(SharedPtr<t_char>info);
void		ft_free_input(char **input, char *input_string);
void		ft_free_memory_cmt(t_target_data *target_data, int amount);

//debug
void		ft_print_content(char **content);

//name struct
t_name		*ft_allocate_memory_name();
void		ft_free_memory_name(t_name *name, int exit_failure);

//attacking
void		ft_npc_check_ac(SharedPtr<t_char>info, const char **input);

//save file
int			ft_npc_check_info(SharedPtr<t_char>info);
void		ft_npc_write_file(SharedPtr<t_char>info, t_stats *stats, t_resistance *resistance,
				ft_file &file);
void		ft_save_pc(t_pc *player, ft_file &file);
void		ft_cast_concentration_save_files(SharedPtr<t_char>info, t_target_data *target_data,
				ft_file &file);
ft_file		ft_check_and_open(t_target_data *target_data, SharedPtr<t_char>info);

//fclean
void		ft_fclean(void);
void		ft_clean(void);

//initiative
void		ft_check_initiative(SharedPtr<t_char>info);
void		ft_roll_initiative(SharedPtr<t_char>info);
void		ft_open_all_files(t_name *name);
int			ft_check_stat_pc(t_pc *player, char **content, char *filename);
int			ft_request_initiative(t_pc *player);
void		ft_initiative_sort(ft_file &file);
void		ft_initiative_sort_2(t_pc *players);
void		ft_initiative_print(void);
t_pc		*ft_initiative_players_am(char **content);
 
//initiative update file
void		ft_initiative_remove(SharedPtr<t_char>info);
void		ft_initiative_add(SharedPtr<t_char>info);

//command roll
void		ft_command_roll(char **argv);
void		ft_free_parse(char **to_parse);
int			ft_command_roll_validate(char *string);
int			ft_check_string_number(char *string);
int			ft_roll_itoa(int result, int *i, char *string);
int			ft_roll_check_character(char c);
int			ft_roll_check_number_next(char *string, int i);
int			ft_roll_check_number_previous(char *string, int i);
void		ft_calculate_j(char *string, int *j);

//roll parser
int			ft_roll_excecute_droll(char *string, int *i, int j);
int			ft_roll_excecute_md(char *string, int *i, int j);
int			ft_roll_excecute_pm(char *string, int *i, int j);
int			ft_roll_parse_brackets(char *string);
int			ft_process_sign(char *string, int *i, int j, int *error);

//roll convert numbers
int			ft_roll_convert_previous(char *string, int *i, int *error);
int			ft_roll_convert_next(char *string, int i, int *error);

//player
void		ft_player(const char **input);
char		**retrieve_player_list();

#endif
