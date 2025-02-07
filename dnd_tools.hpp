#ifndef DND_TOOLS_H
# define DND_TOOLS_H

#include <cstdio>
#include "character.hpp"
#include "libft/Template/shared_ptr.hpp"
#include "player_character.hpp"
#include "libft/CPP_class/file.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define MAX_ERROR_COUNT 5
# define MAX_PLAYERS 8
# define CRIT_SUCCES 999
# define CRIT_FAIL -999

extern bool g_dnd_test;

//NPC
void		ft_npc_change_stats(ft_sharedptr<t_char> &info, int argument_count, const char **argument_vector);
void		ft_npc_set_stat(ft_sharedptr<t_char> &info, const char **input);
int			ft_npc_open_file(ft_sharedptr<t_char> &info);
void		ft_npc_init_stats(ft_sharedptr<t_char> &info);

//Template
ft_sharedptr<t_char> ft_template(const int index, const char **input, t_name *name,
				int exception);
void		ft_template_turn(ft_sharedptr<t_char> &info);

//Ghost
ft_sharedptr<t_char> ft_ghost(const int index, const char **input, t_name *name, int exception);
void		ft_ghost(ft_sharedptr<t_char> &info);

//Frank
ft_sharedptr<t_char> ft_frank(const int index, const char **input, t_name *name, int exception);
void		ft_frank_turn(ft_sharedptr<t_char> &info);

//Goblin Warmaster
ft_sharedptr<t_char> ft_goblin_warmaster(const int index, const char **input, t_name *name,
				int exception);
void		ft_goblin_warmaster_turn(ft_sharedptr<t_char> &info);

// Gundren Rockseeker
ft_sharedptr<t_char> ft_gundren_rockseeker(const int index, const char **input, t_name *name,
				int exception);
void		ft_gundren_rockseeker_turn(ft_sharedptr<t_char> &info);

// Thorbald Ironpocket
ft_sharedptr<t_char> ft_thorbald_ironpocket(const int index, const char **input, t_name *name,
				int exception);
void		ft_thorbald_ironpocket_turn(ft_sharedptr<t_char> &info);

// Murna Claygrip
ft_sharedptr<t_char> ft_murna_claygrip(const int index, const char **input, t_name *name,
				int exception);
void		ft_murna_claygrip_turn(ft_sharedptr<t_char> &info);

// Dorgar Stoneguard
ft_sharedptr<t_char> ft_dorgar_stoneguard(const int index, const char **input, t_name *name,
				int exception);
void		ft_dorgar_stoneguard_turn(ft_sharedptr<t_char> &info);

// Hilda Stormshield
ft_sharedptr<t_char> ft_hilda_stormshield(const int index, const char **input, t_name *name,
				int exception);
void		ft_hilda_stormshield_turn(ft_sharedptr<t_char> &info);

//Gundren Rockseeker
ft_sharedptr<t_char> ft_gundren_rockseeker(const int index, const char **input, t_name *name,
				int exception);
void		ft_gundren_rockseeker_turn(ft_sharedptr<t_char> &info);

//Goblin
ft_sharedptr<t_char> ft_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_goblin_turn(ft_sharedptr<t_char> &info);

//Chaos Goblin
ft_sharedptr<t_char> ft_chaos_crystal(const int index, const char **input, t_name *name,
				int exception);
void		ft_chaos_crystal_turn(ft_sharedptr<t_char> &info);

//Chaos Crystal
ft_sharedptr<t_char> ft_chaos_goblin(const int index, const char **input, t_name *name,
				int exception);
void		ft_chaos_goblin_turn(ft_sharedptr<t_char> &info);

//Grizz
ft_sharedptr<t_char> ft_grizz(const int index, const char **input, t_name *name, int exception);
void		ft_grizz_turn(ft_sharedptr<t_char> &info);

//Veraak
ft_sharedptr<t_char> ft_veraak(const int index, const char **input, t_name *name, int exception);
void		ft_veraak_check_phase(ft_sharedptr<t_char> &info);
void		ft_veraak_turn(ft_sharedptr<t_char> &info);

//Dwarf Paladin
ft_sharedptr<t_char> ft_dwarf_paladin(const int index, const char **input, t_name *name,
										int exception);
void		ft_dwarf_paladin_turn(ft_sharedptr<t_char> &info);

//Maverick
ft_sharedptr<t_char> ft_maverick(const int index, const char **input, t_name *name, int exception);
void		ft_maverick_turn(ft_sharedptr<t_char> &info);
void		ft_maverick_print_s(int first, int second, ft_sharedptr<t_char> &info,
				char **player_list);
void		ft_maverick_print_f(int first, int second, ft_sharedptr<t_char> &info,
				char **player_list);

//Commands
void		ft_request_input(t_name *name);

//Print Abilities
void		print_meteor_strike(const ft_sharedptr<t_char> &info);
void		print_lightning_strike(const ft_sharedptr<t_char> &info);
void		print_flame_geyser(const ft_sharedptr<t_char> &info);
void		print_frost_breath(const ft_sharedptr<t_char> &info);
void		print_lightning_strike_v2(const ft_sharedptr<t_char> &info);
void		print_arcane_pounce(const ft_sharedptr<t_char> &info);
void		print_earth_pounce(const ft_sharedptr<t_char> &info);

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
void		ft_weapon_attack(ft_sharedptr<t_char> &info, t_equipment_id *weapon, int offhand);
int			ft_readline_prompt_hit_or_miss(void);
void		ft_prompt_on_attack_success(ft_sharedptr<t_char> &character, bool critical_strike);
int			ft_weapon_find_stat(ft_sharedptr<t_char> &info, t_equipment_id *weapon);
void 		ft_check_dice_amount_and_faces(t_equipment_id *weapon, t_damage_info *d_info,
                                           int offhand, ft_sharedptr<t_char> &info);
void 		ft_calculate_damage(t_equipment_id *weapon, t_damage_info *d_info, bool is_crit);

//buff update
void		ft_npc_update_buff(ft_sharedptr<t_char> &info, const char **input, int *buff,
				const char *name);
void		ft_update_buff_status(ft_sharedptr<t_char> &info, int current_dur, int duration,
				const char *buff_name);

//damage buffs
int			ft_check_buff_damage(ft_sharedptr<t_char> &info);

//saving throws buffs
int			ft_save_check_buff(ft_sharedptr<t_char> &info, int *roll, const char *ability_score);

//attack rolls buffs
int			ft_attack_roll_check_buffs(ft_sharedptr<t_char> &info, int *roll);

//to_hit check buffs
void		ft_to_hit_check_buff(ft_sharedptr<t_char> &info);

//cast spell
void		ft_cast_divine_smite(ft_sharedptr<t_char> &character, bool critical_strike);
void		ft_cast_cure_wounds(ft_sharedptr<t_char> &character);

//spells utils
int			ft_prompt_spell_level(ft_sharedptr<t_char> &character, int base_level);
int			ft_calculate_spell_damage(int total_dice, int dice_faces, int extra_damage);
int			ft_calculate_spell_healing(int total_dice, int dice_faces, int extra_damage);
void		ft_remove_spell_slot(t_spell_slots *spell_slots, int level_spell_used);

//calculate stats
int			ft_calculate_str(ft_sharedptr<t_char> &info);
int			ft_calculate_dex(ft_sharedptr<t_char> &info);
int			ft_calculate_con(ft_sharedptr<t_char> &info);
int			ft_calculate_inte(ft_sharedptr<t_char> &info);
int			ft_calculate_wis(ft_sharedptr<t_char> &info);
int			ft_calculate_cha(ft_sharedptr<t_char> &info);
int			ft_calculate_ac(ft_sharedptr<t_char> &info);

//calculate skill mods
int			ft_calculate_athletics(ft_sharedptr<t_char> &info);
int			ft_calculate_acrobatics(ft_sharedptr<t_char> &info);
int			ft_calculate_sleight_of_hand(ft_sharedptr<t_char> &info);
int			ft_calculate_stealth(ft_sharedptr<t_char> &info);
int			ft_calculate_arcana(ft_sharedptr<t_char> &info);
int			ft_calculate_history(ft_sharedptr<t_char> &info);
int			ft_calculate_investigation(ft_sharedptr<t_char> &info);
int			ft_calculate_nature(ft_sharedptr<t_char> &info);
int			ft_calculate_religion(ft_sharedptr<t_char> &info);
int			ft_calculate_animal_handling(ft_sharedptr<t_char> &info);
int			ft_calculate_insight(ft_sharedptr<t_char> &info);
int			ft_calculate_medicine(ft_sharedptr<t_char> &info);
int			ft_calculate_perception(ft_sharedptr<t_char> &info);
int			ft_calculate_survival(ft_sharedptr<t_char> &info);
int			ft_calculate_deception(ft_sharedptr<t_char> &info);
int			ft_calculate_intimidation(ft_sharedptr<t_char> &info);
int			ft_calculate_performance(ft_sharedptr<t_char> &info);
int			ft_calculate_persuasion(ft_sharedptr<t_char> &info);

//calculate resistance
int			ft_calculate_acid_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_bludgeoning_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_cold_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_fire_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_force_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_lightning_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_necrotic_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_piercing_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_poison_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_psychic_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_radiant_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_slashing_resistance(ft_sharedptr<t_char> &info);
int			ft_calculate_thunder_resistance(ft_sharedptr<t_char> &info);

//calculate damage reduction
int			ft_calculate_acid_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_bludgeoning_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_cold_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_fire_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_force_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_lightning_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_necrotic_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_piercing_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_poison_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_psychic_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_radiant_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_slashing_dr(ft_sharedptr<t_char> &info);
int			ft_calculate_thunder_dr(ft_sharedptr<t_char> &info);

//calculate utility stats
int 		ft_calculate_crit_attack_fail_bonus(ft_sharedptr<t_char> &info);
int 		ft_calculate_crit_attack_success_bonus(ft_sharedptr<t_char> &info);

//damage
void		ft_deal_damage(ft_sharedptr<t_char> &info, const char *input, const char *d_type,
				int resistance, int concentration);
int			ft_request_damage(ft_sharedptr<t_char> &info);

//skill roll buffs
int			ft_skill_check_buff(ft_sharedptr<t_char> &info, int *roll, const char *skill);

//change stats
void		ft_npc_sstuff(ft_sharedptr<t_char> &info, const char **input);
void		ft_change_stats_04(ft_sharedptr<t_char> &info, const char **input);
void		ft_kill(ft_sharedptr<t_char> &info);

//update debuf
void		ft_set_debuf_blinded(ft_sharedptr<t_char> &info, const char **input);

//update buff
void		ft_update_buf(ft_sharedptr<t_char> &info);
void		ft_update_lightning_strike(ft_sharedptr<t_char> &info);
void		ft_update_lightningV2_strike(ft_sharedptr<t_char> &info);
void		ft_npc_update_lightning_strike(ft_sharedptr<t_char> &info, const char **input);
void		ft_update_flame_geyser(ft_sharedptr<t_char> &info);
void		ft_update_meteor_strike(ft_sharedptr<t_char> &info);
void		ft_update_earth_pounce(ft_sharedptr<t_char> &info);
void		ft_update_arcane_pounce(ft_sharedptr<t_char> &info);
void		ft_update_frost_breath(ft_sharedptr<t_char> &info);

//feats
void		ft_crackback(ft_sharedptr<t_char> &info, int number);

//general buffs
int			ft_check_bless(ft_sharedptr<t_char> &info);

//concentration
void		ft_cast_hunters_mark(ft_sharedptr<t_char> &info, const char **input);
int			ft_cast_concentration(ft_sharedptr<t_char> &info, const char **input, t_buff *buff);
void		ft_check_concentration(ft_sharedptr<t_char> &info, int  damage);
int			ft_remove_concentration(ft_sharedptr<t_char> &info);
void		ft_cast_chaos_armor(ft_sharedptr<t_char> &info);
int			ft_update_caster_name(char ***caster_name, const char *input_name);
int			ft_cast_concentration_multi_target_01(ft_sharedptr<t_char> &info, t_buff *buff,
				const char **input);
void		ft_cast_concentration_multi_target_02(ft_sharedptr<t_char> &info,
				t_target_data *target_data, const char **input);

//hunters mark
void 		ft_cast_bless(ft_sharedptr<t_char> &info, const char **input);
void		ft_concentration_remove_hunters_mark(ft_sharedptr<t_char> &character,
				t_target_data *targets_data);
int			ft_cast_hunters_mark_apply_debuf(ft_sharedptr<t_char> &target, const char **input,
				t_buff *buff);

//bless
int 		ft_cast_bless_apply_debuf(ft_sharedptr<t_char> &target, const char **input,
				t_buff *buff);
void		ft_concentration_remove_bless(ft_sharedptr<t_char> &character,
				t_target_data *targets_data);

//resistance
int			ft_get_resistance(ft_sharedptr<t_char> &info, const char *type);

//advantage or disadvantage
void		ft_reroll(ft_sharedptr<t_char> &info, int *result);

//open and read
char		**ft_read_file_lines(ft_file &file);
char		**ft_open_and_read_file(const char *file_name);
int			ft_open_file_write_only(const char *filename, ft_file &file);

//utils
int			ft_create_data_dir();
int			ft_strcmp_dnd(const char *string1, const char *string2);
int			ft_initialize_info(ft_sharedptr<t_char> &character, char **content);
int			ft_check_value(const char *input);
void		ft_print_character_status(ft_sharedptr<t_char> &info, int number, int temp);
void		ft_skill_throw(ft_sharedptr<t_char> &info, const char *skill, int ability_mod,
				int save_mod);
int			ft_set_stats(ft_sharedptr<t_char> &info, char **content);
int			ft_check_stat(ft_sharedptr<t_char> &info, const char *stat, const int index);
char		**ft_set_stats_con_targets(char *content, int ofset, char **data,
										ft_sharedptr<t_char> &info);
char		**ft_resize_double_char(char **double_string, const char *string, int size);
int			ft_double_char_length(const char **double_char);
void		ft_dual_save_file(ft_sharedptr<t_char> &info, ft_sharedptr<t_char> &target);
char		*ft_strtrim_prefix(const char *s1, const char *prefix);
const char	*ft_ordinal_suffix(int number);
int			ft_check_equipment_slots(ft_sharedptr<t_char> &character);
void		ft_initialize_suggestions_readline();
char		**ft_get_pc_list();
void		ft_remove_element(char **array, char *element, bool free_element);
void		ft_add_element(const char ***array, const char *element);
void		ft_get_random_target(char **player_list, char **target_field);
int			ft_check_player_entry(const char *entry);
int			ft_set_stat_player(size_t key_len, const char **field, const char *content);
int			ft_check_write_permissions(const char *filepath);
ft_sharedptr<t_char> ft_validate_and_fetch_target(char *target_name, ft_sharedptr<t_char> &info,
													int *error_code);
void		ft_initialize_variables(t_target_data *target_data);
int			initialize_stat_key_value_pairs(ft_sharedptr<t_char> &info);
ft_sharedptr<t_char> ft_get_info(const char *tf_name, t_name *name);

//check name
int			ft_set_stats_check_name(const char *name);
int			ft_check_player_character(const char *name);

//readline checks
int			ft_readline_confirm(const char *mesage);
int			ft_readline_spell_level(const char *message, ft_sharedptr<t_char> &character,
				int *invalid_input_amount);

//dice rolling
int			ft_saving_throw(ft_sharedptr<t_char> &info, const char *ability_score,
								int ability_mod, int save_mod);
int			ft_dice_roll(int number, int faces);

//free memory
void		ft_free_pc(t_pc *player);
int			ft_free_players(t_pc *players);
void		ft_free_info(ft_sharedptr<t_char> &info);
void		ft_free_input(char **input, char *input_string);
void		ft_free_memory_cmt(t_target_data *target_data, int amount);

//debug
void		ft_print_content(char **content);

//name struct
t_name		*ft_allocate_memory_name();
void		ft_free_memory_name(t_name *name, int exit_failure);

//attacking
void		ft_npc_check_ac(ft_sharedptr<t_char> &info, const char **input);

//save file
int			ft_npc_check_info(ft_sharedptr<t_char> &info);
void		ft_npc_write_file(ft_sharedptr<t_char> &info, t_stats *stats, t_resistance *resistance,
				ft_file &file);
void		ft_save_pc(t_pc *player, ft_file &file);
void		ft_cast_concentration_save_files(ft_sharedptr<t_char> &info, t_target_data *target_data,
				ft_file &file);
ft_file		ft_check_and_open(t_target_data *target_data, ft_sharedptr<t_char> &info);

//fclean
void		ft_fclean(void);
void		ft_clean(void);

//initiative
void		ft_check_initiative(ft_sharedptr<t_char> &info);
void		ft_roll_initiative(ft_sharedptr<t_char> &info);
void		ft_open_all_files(t_name *name);
int			ft_check_stat_pc(t_pc *player, char **content, char *filename);
int			ft_request_initiative(t_pc *player);
void		ft_initiative_sort(ft_file &file);
void		ft_initiative_sort_2(t_pc *players);
void		ft_initiative_print(void);
t_pc		*ft_initiative_players_am(char **content);
 
//initiative update file
void		ft_initiative_remove(ft_sharedptr<t_char> &info);
void		ft_initiative_add(ft_sharedptr<t_char> &info);

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
