#ifndef DND_TOOLS_H
#define DND_TOOLS_H

#include "include.h"

#ifndef DEBUG
# define DEBUG 0
#endif

#define CRIT_SUCCES 999
#define CRIT_FAIL -999

//NPC
void	ft_npc_change_stats(t_char *info, int index, char **input);
void	ft_npc_set_stat(t_char *info, char **input);
int		ft_npc_open_file(t_char *info);
void	ft_npc_init_stats(t_char *info);

//Template
t_char	*ft_template(int index, char **input, t_name *name, int exception);
void	ft_template_turn(t_char *info);

//Goblin
t_char	*ft_goblin(int index, char **input, t_name *name, int exception);
void	ft_goblin_turn(t_char *info);

//Chaos Goblin
t_char	*ft_chaos_crystal(int index, char **input, t_name *name, int exception);
void	ft_chaos_crystal_turn(t_char *info);

//Chaos Crystal
t_char	*ft_chaos_goblin(int index, char **input, t_name *name, int exception);
void	ft_chaos_goblin_turn(t_char *info);

//Veraak
t_char	*ft_veraak(int index, char **input, t_name *name, int exception);
void	ft_veraak_turn(t_char *info);

//Turn
void	ft_turn_next(t_name *name);

//attack
void	ft_weapon_attack(t_char *info, t_equipment_id *weapon);

//buff update
void	ft_npc_update_buff(t_char *info, char **input, int *buff, char *name);
void	ft_update_buff_status(t_char *info, int current_dur, int duration, char *buff_name);

//damage buffs
int		ft_check_buff_damage(t_char *info);

//saving throws buffs
int		ft_save_check_buff(t_char *info, int *roll, char *ability_score);

//attack rolls buffs
int		ft_attack_roll_check_buffs(t_char *info, int *roll);

//damage
void	ft_deal_damage(t_char *info, char *input, char *d_type, int resistance,
			int concentration);
int		ft_request_damage(t_char *info);

//skill roll buffs
int		ft_skill_check_buff(t_char *info, int *roll, char *skill);

//change stats
void	ft_npc_sstuff(t_char *info, char **input);
void	ft_change_stats_04(t_char *info, char **input);

//update buff
void	ft_update_buf(t_char *info);
void	ft_update_lightning_strike(t_char *info);
void	ft_npc_update_lightning_strike(t_char *info, char **input);

//general buffs
int		ft_check_bless(t_char *info);

//concentration
void	ft_cast_hunters_mark(t_char *info, char **input);
void	ft_check_concentration(t_char *info, int  damage);
int		ft_remove_concentration(t_char *info);
void	ft_concentration_remove_hunters_mark(t_char *info, t_char *target);
void	ft_cast_chaos_armor(t_char *info);

//resistance
int		ft_get_resistance(t_char *info, char *type);

//advantage or disadvantage
void	ft_reroll(t_char *info, int *result);

//open and read
char	**ft_read_file_dnd(int fd);
char	**ft_open_and_read(char *file);
int		ft_open_file(const char *filename);

//utils
int		ft_strcmp_dnd(const char *string1, const char *string2);
int		ft_initialize_info(t_char *info, char **content);
int		ft_check_value(char *input);
void	ft_print_character_status(t_char *info, int number, int temp);
void	ft_skill_throw(t_char *info, char *skill, int ability_mod, int save_mod);
int		ft_set_stats(t_char *info, char **content);
int		ft_check_stat(t_char *info, char *stat, int index);
char	**ft_set_stats_con_targets(char *content, int ofset, char **data, t_char *info);
t_char	*ft_get_info(char *tf_name, t_name *name);
char	**ft_resize_double_char(char **double_string, char *string, int size);
int		ft_double_char_length(char **double_char);
void	ft_dual_save_file(t_char *info, t_char *target);

//check name
int		ft_set_stats_check_name(char *name);
int		ft_check_player_character(char *name);

//readline checks
int		ft_read_line_confirm(char *mesage);

//dice rolling
int		ft_saving_throw(t_char *info, char *ability_score, int ability_mod, int save_mod);
int		ft_dice_roll(int number, int faces);

//free memory
void	ft_free_double_char(char **content);
void	ft_free_pc(t_pc *player);
int 	ft_free_players(t_pc *players);
void	ft_free_info(t_char *info);

//debug
void	ft_print_content(char **content);

//name struct
t_name	*ft_allocate_memory_name();
void	ft_free_memory_name(t_name *name, int exit_failure);

//attacking
void	ft_npc_check_ac(t_char *info, char **input);

//save file
int		ft_npc_check_info(t_char *info);
void	ft_npc_write_file(t_char *info, t_stats *stats, t_resistance *resistance, int fd);
void	ft_save_pc(t_pc *player, int fd);

//fclean
void	ft_fclean(void);
void	ft_clean(void);

//initiative
void	ft_check_initiative(t_char *info);
void	ft_roll_initiative(t_char *info);
void	ft_open_all_files(t_name *name);
int		ft_check_stat_pc(t_pc *player, char **content, char *filename);
int		ft_request_initiative(t_pc *player);
void	ft_initiative_sort(int fd);
void	ft_initiative_sort_2(t_pc *players);
void	ft_initiative_print(void);
t_pc	*ft_initiative_players_am(char **content);
 
//initiative update file
void	ft_initiative_remove(t_char *info);
void	ft_initiative_add(t_char *info);

//command roll
void	ft_command_roll(char **argv);
void	ft_free_parse(char **to_parse);
int		ft_command_roll_validate(char *string);
int		ft_check_string_number(char *string);
int		ft_roll_itoa(int result, int *i, char *string);
int		ft_roll_check_character(char c);
int		ft_roll_check_number_next(char *string, int i);
int		ft_roll_check_number_previous(char *string, int i);

//roll parser
int		ft_roll_excecute_droll(char *string, int *i, int j);
int		ft_roll_excecute_md(char *string, int *i, int j);
int		ft_roll_excecute_pm(char *string, int *i, int j);
int		ft_roll_parse_brackets(char *string, int *i, int j);

//roll convert numbers
int		ft_roll_convert_previous(char *string, int *i);
int		ft_roll_convert_next(char *string, int i);

//player
void	ft_player(char **input);

#endif
