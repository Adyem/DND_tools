#ifndef DND_TOOLS_H
# define DND_TOOLS_H

static_assert(sizeof(int) == 4, "Expected int to be 4 bytes");

#include <cstdio>
#include "character.hpp"
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

// NPC
void		ft_npc_change_stats(t_char * info, int argument_count, const char **argument_vector);
void		ft_npc_set_stat(t_char * info, const char **input);
int			ft_npc_open_file(t_char * info);
void		ft_npc_init_stats(t_char * info);

// Template
t_char 		*ft_template(const int index, const char **input, t_name *name, int exception);
void		ft_template_turn(t_char * info);
void		ft_template_loot(t_char * info);

// Shield_spell_a
t_char 		*ft_shield_spell_a(const int index, const char **input, t_name *name, int exception);
void		ft_shield_spell_a_turn(t_char * info);
void		ft_shield_spell_a_loot(t_char * info);

// Demonic_portal_a
t_char 		*ft_demonic_portal_a(const int index, const char **input, t_name *name, int exception);
void		ft_demonic_portal_a_turn(t_char * info);
void		ft_demonic_portal_a_loot(t_char * info);

// Malfurion
t_char 		*ft_malfurion(const int index, const char **input, t_name *name, int exception);
void		ft_malfurion_turn(t_char * info);
void		ft_malfurion_loot(t_char * info);

// Xavius
t_char 		*ft_xavius(const int index, const char **input, t_name *name, int exception);
void		ft_xavius_turn(t_char * info);
void		ft_xavius_loot(t_char * info);

// Night Elven Guard
t_char 		*ft_night_elven_guard(const int index, const char **input, t_name *name, int exception);
void		ft_night_elven_guard_turn(t_char * info);
void		ft_night_elven_guard_loot(t_char * info);

// Snow Goblin
t_char		*ft_snow_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_snow_goblin(t_char * info);
void		ft_snow_goblin(t_char * info);

// Ghost
t_char 		*ft_ghost(const int index, const char **input, t_name *name, int exception);
void		ft_ghost(t_char * info);

// Frank
t_char 		*ft_felbeast(const int index, const char **input, t_name *name, int exception);
void		ft_felbeast_turn(t_char * info);

// Frank
t_char 		*ft_frank(const int index, const char **input, t_name *name, int exception);
void		ft_frank_turn(t_char * info);

// Goblin Warmaster
t_char 		*ft_goblin_warmaster(const int index, const char **input, t_name *name,
				int exception);
void		ft_goblin_warmaster_turn(t_char * info);

// Gundren Rockseeker
t_char 		*ft_gundren_rockseeker(const int index, const char **input, t_name *name,
				int exception);
void		ft_gundren_rockseeker_turn(t_char * info);

// Thorbald Ironpocket
t_char 		*ft_thorbald_ironpocket(const int index, const char **input, t_name *name,
				int exception);
void		ft_thorbald_ironpocket_turn(t_char * info);

// Murna Claygrip
t_char 		*ft_murna_claygrip(const int index, const char **input, t_name *name, int exception);
void		ft_murna_claygrip_turn(t_char * info);

// Dorgar Stoneguard
t_char 		*ft_dorgar_stoneguard(const int index, const char **input, t_name *name, int exception);
void		ft_dorgar_stoneguard_turn(t_char * info);

// Hilda Stormshield
t_char 		*ft_hilda_stormshield(const int index, const char **input, t_name *name, int exception);
void		ft_hilda_stormshield_turn(t_char * info);

// Gundren Rockseeker (duplicate declaration)
t_char 		*ft_gundren_rockseeker(const int index, const char **input, t_name *name, int exception);
void		ft_gundren_rockseeker_turn(t_char * info);

// Goblin
t_char 		*ft_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_goblin_turn(t_char * info);

// Chaos Crystal
t_char 		*ft_chaos_crystal(const int index, const char **input, t_name *name, int exception);
void		ft_chaos_crystal_turn(t_char * info);

// Chaos Goblin
t_char 		*ft_chaos_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_chaos_goblin_turn(t_char * info);

// Grizz
t_char 		*ft_grizz(const int index, const char **input, t_name *name, int exception);
void		ft_grizz_turn(t_char * info);

// Veraak
t_char 		*ft_veraak(const int index, const char **input, t_name *name, int exception);
void		ft_veraak_check_phase(t_char * info);
void		ft_veraak_turn(t_char * info);

// Dwarf Paladin
t_char 		*ft_dwarf_paladin(const int index, const char **input, t_name *name, int exception);
void		ft_dwarf_paladin_turn(t_char * info);

// Ancient Predatory Beast
t_char 		*ft_ancient_predatory_beast(const int index, const char **input, t_name *name,
				int exception);
void		ft_ancient_predatory_beast_turn(t_char * info);

// Maverick
t_char 		*ft_maverick(const int index, const char **input, t_name *name, int exception);
void		ft_maverick_turn(t_char * info);
void		ft_maverick_print_s(int first, int second, t_char * info, char **player_list);
void		ft_maverick_print_f(int first, int second, t_char * info, char **player_list);

// Commands
void		ft_request_input(t_name *name);

// Print Abilities
void		print_meteor_strike(const t_char * info);
void		print_lightning_strike(const t_char * info);
void		print_flame_geyser(const t_char * info);
void		print_frost_breath(const t_char * info);
void		print_lightning_strike_v2(const t_char * info);
void		print_arcane_pounce(const t_char * info);
void		print_earth_pounce(const t_char * info);

// Tester
void		ft_test(t_name *name);
int			ft_test_excecute(const char **input, int argc, t_name *name);

// Tester Make input strings
void		ft_excecute_test(const char *string1, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3,
				t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3,
				const char *string4, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3,
				const char *string4, const char *string5, t_name *name);

// Turn
void		ft_turn_next(t_name *name);

// Attack
void		ft_attack_additional_effects(t_char *info, t_equipment_id *weapon,
				t_attack_info *attack_info);
void		ft_weapon_attack(t_char * info, t_equipment_id *weapon, int offhand);
int			ft_readline_prompt_hit_or_miss(void);
void		ft_prompt_on_attack_success(t_char * character, bool critical_strike);
int			ft_weapon_find_stat(t_char * info, t_equipment_id *weapon);
void 		ft_check_dice_amount_and_faces(t_equipment_id *weapon, t_damage_info *d_info,
				int offhand, t_char * info);
void 		ft_calculate_damage(t_equipment_id *weapon, t_damage_info *d_info, bool is_crit);

// Attack effects
void 		ft_strength_drain(t_char *info, t_equipment_id *weapon,
				t_equipment_effect *effect, t_attack_info *attack_info);
void		ft_felbeast_attack_effects(t_char *info, t_equipment_id *weapon,
				t_equipment_effect *effect, t_attack_info *attack_info);
void 		ft_ancient_predatory_beast_attack_effects(t_char *info, t_equipment_id *weapon,
				t_equipment_effect *effect, t_attack_info *attack_info);
void 		ft_snow_goblin_attack_effects(t_char *info, t_equipment_id *weapon,
				t_equipment_effect *effect, t_attack_info *attack_info);
void		ft_shadow_claw_effect(t_char *info, t_equipment_id *weapon,
				t_equipment_effect *effect, t_attack_info *attack_info);

// Buff update
void		ft_npc_update_buff(t_char * info, const char **input, int *buff, const char *name);
void		ft_update_buff_status(t_char * info, int current_dur, int duration,
				const char *buff_name);

// Init Encounter
void		ft_encounter(const char *encounter_name, t_name *name);

// Damage buffs
int			ft_check_buff_damage(t_char * info);

// Saving throws buffs
int			ft_save_check_buff(t_char * info, int *roll, const char *ability_score);

// Attack rolls buffs
int			ft_attack_roll_check_buffs(t_char * info, int *roll);

// To-hit check buffs
void		ft_to_hit_check_buff(t_char * info);

// Cast spell
void		ft_cast_divine_smite(t_char * character, bool critical_strike);
void		ft_cast_cure_wounds(t_char * character);
void		ft_cast_rejuvenation(const char **input, t_char *info);

// Spells utils
int			ft_prompt_spell_level(t_char * character, int base_level);
int			ft_calculate_spell_damage(int total_dice, int dice_faces, int extra_damage);
int			ft_calculate_spell_healing(int total_dice, int dice_faces, int extra_damage);
void		ft_remove_spell_slot(t_spell_slots *spell_slots, int level_spell_used);

// Calculate stats
int			ft_calculate_str(t_char * info);
int			ft_calculate_dex(t_char * info);
int			ft_calculate_con(t_char * info);
int			ft_calculate_inte(t_char * info);
int			ft_calculate_wis(t_char * info);
int			ft_calculate_cha(t_char * info);
int			ft_calculate_ac(t_char * info);

// Calculate skill mods
int			ft_calculate_athletics(t_char * info);
int			ft_calculate_acrobatics(t_char * info);
int			ft_calculate_sleight_of_hand(t_char * info);
int			ft_calculate_stealth(t_char * info);
int			ft_calculate_arcana(t_char * info);
int			ft_calculate_history(t_char * info);
int			ft_calculate_investigation(t_char * info);
int			ft_calculate_nature(t_char * info);
int			ft_calculate_religion(t_char * info);
int			ft_calculate_animal_handling(t_char * info);
int			ft_calculate_insight(t_char * info);
int			ft_calculate_medicine(t_char * info);
int			ft_calculate_perception(t_char * info);
int			ft_calculate_survival(t_char * info);
int			ft_calculate_deception(t_char * info);
int			ft_calculate_intimidation(t_char * info);
int			ft_calculate_performance(t_char * info);
int			ft_calculate_persuasion(t_char * info);

// Calculate resistance
int			ft_calculate_acid_resistance(t_char * info);
int			ft_calculate_bludgeoning_resistance(t_char * info);
int			ft_calculate_cold_resistance(t_char * info);
int			ft_calculate_fire_resistance(t_char * info);
int			ft_calculate_force_resistance(t_char * info);
int			ft_calculate_lightning_resistance(t_char * info);
int			ft_calculate_necrotic_resistance(t_char * info);
int			ft_calculate_piercing_resistance(t_char * info);
int			ft_calculate_poison_resistance(t_char * info);
int			ft_calculate_psychic_resistance(t_char * info);
int			ft_calculate_radiant_resistance(t_char * info);
int			ft_calculate_slashing_resistance(t_char * info);
int			ft_calculate_thunder_resistance(t_char * info);

// Calculate damage reduction
int			ft_calculate_acid_dr(t_char * info);
int			ft_calculate_bludgeoning_dr(t_char * info);
int			ft_calculate_cold_dr(t_char * info);
int			ft_calculate_fire_dr(t_char * info);
int			ft_calculate_force_dr(t_char * info);
int			ft_calculate_lightning_dr(t_char * info);
int			ft_calculate_necrotic_dr(t_char * info);
int			ft_calculate_piercing_dr(t_char * info);
int			ft_calculate_poison_dr(t_char * info);
int			ft_calculate_psychic_dr(t_char * info);
int			ft_calculate_radiant_dr(t_char * info);
int			ft_calculate_slashing_dr(t_char * info);
int			ft_calculate_thunder_dr(t_char * info);

// Calculate utility stats
int 		ft_calculate_crit_attack_fail_bonus(t_char * info);
int 		ft_calculate_crit_attack_success_bonus(t_char * info);

// Damage
void		ft_deal_damage(t_char * info, const char *input, const char *d_type,
				int resistance, int concentration);
int			ft_request_damage(t_char * info);

// Skill roll buffs
int			ft_skill_check_buff(t_char * info, int *roll, const char *skill);

// Change stats
void		ft_npc_sstuff(t_char * info, const char **input);
void		ft_change_stats_04(t_char * info, const char **input);
void		ft_kill(t_char * info);

// Update debuf
void		ft_set_debuf_blinded(t_char * info, const char **input);

// Update buff
void		ft_update_buf(t_char * info);
void		ft_update_lightning_strike(t_char * info);
void		ft_update_lightningV2_strike(t_char * info);
void		ft_npc_update_lightning_strike(t_char * info, const char **input);
void		ft_update_flame_geyser(t_char * info);
void		ft_update_meteor_strike(t_char * info);
void		ft_update_earth_pounce(t_char * info);
void		ft_update_arcane_pounce(t_char * info);
void		ft_update_frost_breath(t_char * info);
void		ft_update_buff_rejuvenation(t_char *info);

// Feats
void		ft_crackback(t_char * info, int number);

// General buffs
int			ft_check_bless(t_char * info);

// Concentration
void		ft_cast_hunters_mark(t_char *info, const char **input);
int			ft_cast_concentration(t_char *info, const char **input, t_buff *buff);
void		ft_check_concentration(t_char *info, int  damage);
int			ft_remove_concentration(t_char *info);
void		ft_cast_chaos_armor(t_char *info);
int			ft_update_caster_name(char ***caster_name, const char *input_name);
int			ft_cast_concentration_multi_target_01(t_char *info, t_buff *buff, const char **input);
void		ft_cast_concentration_multi_target_02(t_char *info, t_target_data *target_data,
				const char **input);
int 		ft_is_caster_name_present(char **caster_name_list, const char *name);

// Hunters mark
void		ft_concentration_remove_hunters_mark(t_char *character, t_target_data *targets_data);
int			ft_cast_hunters_mark_apply_debuf(t_char *target, const char **input, t_buff *buff);

// Bless
void 		ft_cast_bless(t_char *info, const char **input);
int 		ft_cast_bless_apply_debuf(t_char *target, const char **input, t_buff *buff);
void		ft_concentration_remove_bless(t_char *character, t_target_data *targets_data);

// Magic Drain
void		ft_cast_magic_drain(t_char *info, const char **input);
int			ft_magic_drain_apply_debuff(t_char *target, const char **input, t_buff *buff);
void		ft_concentration_remove_magic_drain(t_char *character, t_target_data *targets_data);

// Resistance
int			ft_get_resistance(t_char * info, const char *type);

// Advantage or disadvantage
void		ft_reroll(t_char * info, int *result);

// Open and read
int			ft_open_file_write_only(const char *filename, ft_file &file);

// Utils
int			ft_create_data_dir();
int			ft_strcmp_dnd(const char *string1, const char *string2);
int			ft_initialize_info(t_char * character, char **content);
int			ft_check_value(const char *input);
void		ft_print_character_status(t_char * info, int number, int temp);
void		ft_skill_throw(t_char * info, const char *skill, int ability_mod, int save_mod);
int			ft_set_stats(t_char * info, char **content);
int			ft_check_stat(t_char * info, const char *stat, const size_t index);
char		**ft_set_stats_con_targets(char *content, size_t ofset, char **data, t_char *info);
char		**ft_resize_double_char(char **double_string, const char *string, size_t size);
int			ft_double_char_length(const char **double_char);
void		ft_dual_save_file(t_char * info, t_char * target);
char		*ft_strtrim_prefix(const char *s1, const char *prefix);
const char	*ft_ordinal_suffix(int number);
int			ft_check_equipment_slots(t_char * character);
void		ft_initialize_suggestions_readline();
char		**ft_get_pc_list();
void		ft_remove_element(char **array, char *element, bool free_element);
void		ft_add_element(const char ***array, const char *element);
void		ft_get_random_target(char **player_list, char **target_field);
int			ft_check_player_entry(const char *entry);
int			ft_set_stat_player(size_t key_len, const char **field, const char *content);
int			ft_check_write_permissions(const char *filepath);
t_char *	ft_validate_and_fetch_target(char *target_name, t_char * info, int *error_code);
void		ft_initialize_variables(t_target_data *target_data);
int			initialize_stat_key_value_pairs(t_char * info);
t_char *	ft_get_info(const char *tf_name, t_name *name);

// Check name
int			ft_set_stats_check_name(const char *name);
int			ft_check_player_character(const char *name);

// Readline checks
int			ft_readline_confirm(const char *mesage);
int			ft_readline_spell_level(const char *message, t_char * character,
				int *invalid_input_amount);

// Dice rolling
int			ft_saving_throw(t_char * info, const char *ability_score, int ability_mod, int save_mod);

// Free memory
void		ft_free_pc(t_pc *player);
int			ft_free_players(t_pc *players);
void		ft_free_info(t_char * info);
void		ft_free_input(char **input, char *input_string);
void		ft_free_memory_cmt(t_target_data *target_data, int amount);

// Debug
void		ft_print_content(char **content);

// Name struct
t_name		*ft_allocate_memory_name();
void		ft_free_memory_name(t_name *name, int exit_failure);

// Attacking
void		ft_npc_check_ac(t_char * info, const char **input);

// Save file
int			ft_npc_check_info(t_char * info);
void		ft_npc_write_file(t_char * info, t_stats *stats, t_resistance *resistance,
				ft_file &file);
void		ft_save_pc(t_pc *player, ft_file &file);
void		ft_cast_concentration_save_files(t_char * info, t_target_data *target_data,
				ft_file &file);
ft_file		ft_check_and_open(t_target_data *target_data, t_char * info);

// fclean
void		ft_fclean(void);
void		ft_clean(void);

// Initiative
void		ft_check_initiative(t_char * info);
void		ft_roll_initiative(t_char * info);
void		ft_open_all_files(t_name *name);
int			ft_check_stat_pc(t_pc *player, char **content, char *filename);
int			ft_request_initiative(t_pc *player);
void		ft_initiative_sort(ft_file &file);
void		ft_initiative_sort_2(t_pc *players);
void		ft_initiative_print(void);
t_pc		*ft_initiative_players_am(char **content);
 
// Initiative update file
void		ft_initiative_remove(t_char * info);
void		ft_initiative_add(t_char * info);

// Command roll
void		ft_command_roll(char **argv);
void		ft_free_parse(char **to_parse);
int			ft_command_roll_validate(char *string);
int			ft_check_string_number(char *string);
int			ft_roll_itoa(int result, int *i, char *string);
int			ft_roll_check_character(char c);
int			ft_roll_check_number_next(char *string, int i);
int			ft_roll_check_number_previous(char *string, int i);
void		ft_calculate_j(char *string, int *j);

// Roll parser
int			ft_roll_excecute_droll(char *string, int *i, int j);
int			ft_roll_excecute_md(char *string, int *i, int j);
int			ft_roll_excecute_pm(char *string, int *i, int j);
int			ft_roll_parse_brackets(char *string);
int			ft_process_sign(char *string, int *i, int j, int *error);

// Roll convert numbers
int			ft_roll_convert_previous(char *string, int *i, int *error);
int			ft_roll_convert_next(char *string, int i, int *error);

// Player
void		ft_player(const char **input);
char		**retrieve_player_list();

#endif
