#ifndef DND_TOOLS_H
# define DND_TOOLS_H

#include <cstdio>
#include "character.hpp"
#include "player_character.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define CRIT_SUCCES 999
# define CRIT_FAIL -999

extern bool dnd_test;

//NPC
void		ft_npc_change_stats(t_char *info, int index, const char **input);
void		ft_npc_set_stat(t_char *info, const char **input);
int			ft_npc_open_file(t_char *info);
void		ft_npc_init_stats(t_char *info);

//Template
t_char		*ft_template(const int index, const char **input, t_name *name, int exception);
void		ft_template_turn(t_char *info);

//Goblin Warmaster
t_char		*ft_goblin_warmaster(const int index, const char **input, t_name *name, int exception);
void		ft_goblin_warmaster_turn(t_char *info);

//Gundren Rockseeker
t_char		*ft_gundren_rockseeker(const int index, const char **input, t_name *name, int exception);
void		ft_gundren_rockseeker_turn(t_char *info);

//Goblin
t_char		*ft_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_goblin_turn(t_char *info);

//Chaos Goblin
t_char		*ft_chaos_crystal(const int index, const char **input, t_name *name, int exception);
void		ft_chaos_crystal_turn(t_char *info);

//Chaos Crystal
t_char		*ft_chaos_goblin(const int index, const char **input, t_name *name, int exception);
void		ft_chaos_goblin_turn(t_char *info);

//Veraak
t_char		*ft_veraak(const int index, const char **input, t_name *name, int exception);
void		ft_veraak_check_phase(t_char *info);
void		ft_veraak_turn(t_char *info);

//Maverick
t_char		*ft_maverick(const int index, const char **input, t_name *name, int exception);
void		ft_maverick_turn(t_char *info);
void		ft_maverick_print_s(int first, int second, t_char *info);
void		ft_maverick_print_f(int first, int second, t_char *info);

//Commands
void		ft_request_input(t_name *name);

//Print Abilities
void		print_meteor_strike(const t_char *info);
void		print_lightning_strike(const t_char *info);
void		print_flame_geyser(const t_char *info);
void		print_frost_breath(const t_char *info);
void		print_lightning_strike_v2(const t_char *info);
void		print_arcane_pounce(const t_char *info);
void		print_earth_pounce(const t_char *info);

//Tester
void		ft_test(t_name *name);
int			ft_test_excecute(const char **input, int argc, t_name *name);

//Tester Make input strings
void		ft_excecute_test(const char *string1, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3, const char *string4, t_name *name);
void		ft_excecute_test(const char *string1, const char *string2, const char *string3, const char *string4, const char *string5, t_name *name);

//Turn
void		ft_turn_next(t_name *name);

//attack
void		ft_weapon_attack(t_char *info, t_equipment_id *weapon, int offhand);

//buff update
void		ft_npc_update_buff(t_char *info, const char **input, int *buff, const char *name);
void		ft_update_buff_status(t_char *info, int current_dur, int duration, const char *buff_name);

//damage buffs
int			ft_check_buff_damage(t_char *info);

//saving throws buffs
int			ft_save_check_buff(t_char *info, int *roll, const char *ability_score);

//attack rolls buffs
int			ft_attack_roll_check_buffs(t_char *info, int *roll);

//to_hit check buffs
void		ft_to_hit_check_buff(t_char *info);

//calculate stats
int			ft_calculate_str(t_char *info);
int			ft_calculate_dex(t_char *info);
int			ft_calculate_con(t_char *info);
int			ft_calculate_inte(t_char *info);
int			ft_calculate_wis(t_char *info);
int			ft_calculate_cha(t_char *info);

//calculate skill mods
int			ft_calculate_athletics(t_char *info);
int			ft_calculate_acrobatics(t_char *info);
int			ft_calculate_sleight_of_hand(t_char *info);
int			ft_calculate_stealth(t_char *info);
int			ft_calculate_arcana(t_char *info);
int			ft_calculate_history(t_char *info);
int			ft_calculate_investigation(t_char *info);
int			ft_calculate_nature(t_char *info);
int			ft_calculate_religion(t_char *info);
int			ft_calculate_animal_handling(t_char *info);
int			ft_calculate_insight(t_char *info);
int			ft_calculate_medicine(t_char *info);
int			ft_calculate_perception(t_char *info);
int			ft_calculate_survival(t_char *info);
int			ft_calculate_deception(t_char *info);
int			ft_calculate_intimidation(t_char *info);
int			ft_calculate_performance(t_char *info);
int			ft_calculate_persuasion(t_char *info);

//calculate resistance
int			ft_calculate_acid_resistance(t_char *info);
int			ft_calculate_bludgeoning_resistance(t_char *info);
int			ft_calculate_cold_resistance(t_char *info);
int			ft_calculate_fire_resistance(t_char *info);
int			ft_calculate_force_resistance(t_char *info);
int			ft_calculate_lightning_resistance(t_char *info);
int			ft_calculate_necrotic_resistance(t_char *info);
int			ft_calculate_piercing_resistance(t_char *info);
int			ft_calculate_poison_resistance(t_char *info);
int			ft_calculate_psychic_resistance(t_char *info);
int			ft_calculate_radiant_resistance(t_char *info);
int			ft_calculate_slashing_resistance(t_char *info);
int			ft_calculate_thunder_resistance(t_char *info);

//calculate damage reduction
int			ft_calculate_acid_dr(t_char *info);
int			ft_calculate_bludgeoning_dr(t_char *info);
int			ft_calculate_cold_dr(t_char *info);
int			ft_calculate_fire_dr(t_char *info);
int			ft_calculate_force_dr(t_char *info);
int			ft_calculate_lightning_dr(t_char *info);
int			ft_calculate_necrotic_dr(t_char *info);
int			ft_calculate_piercing_dr(t_char *info);
int			ft_calculate_poison_dr(t_char *info);
int			ft_calculate_psychic_dr(t_char *info);
int			ft_calculate_radiant_dr(t_char *info);
int			ft_calculate_slashing_dr(t_char *info);
int			ft_calculate_thunder_dr(t_char *info);

//damage
void		ft_deal_damage(t_char *info, const char *input, const char *d_type, int resistance,
				int concentration);
int			ft_request_damage(t_char *info);

//skill roll buffs
int			ft_skill_check_buff(t_char *info, int *roll, const char *skill);

//change stats
void		ft_npc_sstuff(t_char *info, const char **input);
void		ft_change_stats_04(t_char *info, const char **input);
void		ft_kill(t_char *info);

//update debuf
void		ft_set_debuf_blinded(t_char *info, const char **input);

//update buff
void		ft_update_buf(t_char *info);
void		ft_update_lightning_strike(t_char *info);
void		ft_update_lightningV2_strike(t_char *info);
void		ft_npc_update_lightning_strike(t_char *info, const char **input);
void		ft_update_flame_geyser(t_char *info);
void		ft_update_meteor_strike(t_char *info);
void		ft_update_earth_pounce(t_char *info);
void		ft_update_arcane_pounce(t_char *info);

//general buffs
int			ft_check_bless(t_char *info);

//concentration
void		ft_cast_hunters_mark(t_char *info, const char **input);
int			ft_cast_concentration(t_char *info, const char **input, t_buff *buff);
void		ft_check_concentration(t_char *info, int  damage);
int			ft_remove_concentration(t_char *info);
void		ft_cast_chaos_armor(t_char *info);
int			ft_update_caster_name(char ***caster_name, const char *input_name);
void		ft_cast_concentration_multi_target(t_char *info, const char **input, t_buff *buff);

//hunters mark
void		ft_concentration_remove_hunters_mark(t_char *info, t_char *target);
int			ft_cast_hunters_mark_apply_debuf(t_char *target, const char **input, t_buff *buff);
void		ft_cleanup_hunters_mark(t_char *info, t_char *target, t_buff *buff);

//resistance
int			ft_get_resistance(t_char *info, const char *type);

//advantage or disadvantage
void		ft_reroll(t_char *info, int *result);

//open and read
char		**ft_read_file_dnd(int fd);
char		**ft_open_and_read(const char *file);
int			ft_open_file_write_only(const char *filename);

//utils
int			ft_create_data_dir();
int			ft_strcmp_dnd(const char *string1, const char *string2);
int			ft_initialize_info(t_char *info, char **content);
int			ft_check_value(const char *input);
void		ft_print_character_status(t_char *info, int number, int temp);
void		ft_skill_throw(t_char *info, const char *skill, int ability_mod, int save_mod);
int			ft_set_stats(t_char *info, char **content);
int			ft_check_stat(t_char *info, const char *stat, const int index);
char		**ft_set_stats_con_targets(char *content, int ofset, char **data, t_char *info);
t_char		*ft_get_info(const char *tf_name, t_name *name);
char		**ft_resize_double_char(char **double_string, const char *string, int size);
int			ft_double_char_length(char **double_char);
void		ft_dual_save_file(t_char *info, t_char *target);
char		*ft_strtrim_prefix(const char *s1, const char *prefix);
const char	*ft_ordinal_suffix(int number);
int			ft_check_equipment_slots(t_char *character);
void		ft_initialize_suggestions_readline();
char		**get_random_pc_file();

//check name
int			ft_set_stats_check_name(const char *name);
int			ft_check_player_character(const char *name);

//readline checks
int			ft_read_line_confirm(const char *mesage);

//dice rolling
int			ft_saving_throw(t_char *info, const char *ability_score, int ability_mod, int save_mod);
int			ft_dice_roll(int number, int faces);

//free memory
void		ft_free_pc(t_pc *player);
int			ft_free_players(t_pc *players);
void		ft_free_info(t_char *info);
void		ft_free_input(char **input, char *input_string);

//debug
void		ft_print_content(char **content);

//name struct
t_name		*ft_allocate_memory_name();
void		ft_free_memory_name(t_name *name, int exit_failure);

//attacking
void		ft_npc_check_ac(t_char *info, const char **input);

//save file
int			ft_npc_check_info(t_char *info);
void		ft_npc_write_file(t_char *info, t_stats *stats, t_resistance *resistance, int fd);
void		ft_save_pc(t_pc *player, int fd);

//fclean
void		ft_fclean(void);
void		ft_clean(void);

//initiative
void		ft_check_initiative(t_char *info);
void		ft_roll_initiative(t_char *info);
void		ft_open_all_files(t_name *name);
int			ft_check_stat_pc(t_pc *player, char **content, char *filename);
int			ft_request_initiative(t_pc *player);
void		ft_initiative_sort(int fd);
void		ft_initiative_sort_2(t_pc *players);
void		ft_initiative_print(void);
t_pc		*ft_initiative_players_am(char **content);
 
//initiative update file
void		ft_initiative_remove(t_char *info);
void		ft_initiative_add(t_char *info);

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

#endif
