#ifndef DND_TOOLS_H
#define DND_TOOLS_H

# include "include.h"

#ifndef DEBUG
# define DEBUG 0
#endif

typedef struct	s_name t_name;
typedef void	(*c_name)(int, char **);

typedef struct s_name
{
	char	*name;
	c_name	function;
	t_name	*next;
} t_name;

//NPC
void	ft_npc_change_stats(t_char *info, int index, char **input);
void	ft_npc_set_stat(t_char *info, char **input);
int		ft_npc_open_file(t_char *info);
void	ft_npc_init_stats(t_char *info);

//Maverick (BOSS)
void	ft_maverick(int index, char **input);
void	ft_maverick_turn(t_char *info);
void	ft_maverick_attack(t_char *info);
void	ft_maverick_print_f(int first, int second);
void	ft_maverick_print_s(int first, int second);

//Zephyr (BOSS)
void	ft_zephyr(int index, char **input);
void	ft_zephyr_attack(t_char *info);
void	ft_zephyr_ranged_attack(t_char *info);
void	ft_zephyr_turn(t_char *info);
void	ft_zephyr_spells(t_char *info);

//Air Goblin (NPC)
void	ft_air_goblin(int index, char **input);
void	ft_air_goblin_attack(t_char *info);
void	ft_air_goblin_ranged_attack(t_char *info);
void	ft_air_goblin_turn(t_char *info);

//Goblin (NPC)
void	ft_goblin(int index, char **input);
void	ft_goblin_attack(t_char *info);
void	ft_goblin_ranged_attack(t_char *info);
void	ft_goblin_turn(t_char *info);

//Grizzletooth (BOSS)
void	ft_grizzletooth(int index, char **input);
void	ft_grizzletooth_attack(t_char *info);
void	ft_grizzletooth_ranged_attack(t_char *info);
void	ft_grizzletooth_turn(t_char *info);


//Air Goblin Shaman (NPC)
void	ft_air_goblin_shaman(int index, char **input);
void	ft_air_goblin_shaman_attack(t_char *info);
void	ft_air_goblin_shaman_ranged_attack(t_char *info);
void	ft_air_goblin_shaman_turn(t_char *info);

//Air Totem (Totem)
void	ft_air_totem(int index, char **input);

//buff update
void	ft_npc_update_buff(t_char *info, char **input, int *buff, char *name);
void	ft_update_buff_status(t_char *info, int current_dur, int duration, char *buff_name);

//saving throws buffs
int		ft_save_check_buff(t_char *info, int *roll, char *ability_score);

//attack rolls buffs
int		ft_attack_roll_check_buffs(t_char *info, int *roll);

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

//advantage or disadvantage
void	ft_reroll(t_char *info, int *result);

//utils
int		ft_strcmp_dnd(char *string1, char *string2);
char	**ft_read_file_dnd(int fd);
int		ft_initialize_info(t_char *info, char **content);
int		ft_check_value(char *input);
void	ft_print_character_status(t_char *info, int number, int temp);
void	ft_skill_throw(t_char *info, char *skill, int ability_mod, int save_mod);
int		ft_set_stats(t_char *info, char **content);
int		ft_check_stat(t_char *info, char *stat, int index);

//readline checks
int		ft_read_line_confirm(char *mesage);

//dice rolling
void	ft_saving_throw(t_char *info, char *ability_score, int ability_mod, int save_mod);
int		ft_dice_roll(int number, int faces);

//free memory
void	ft_free_content(char **content);

//debug
void	ft_print_content(char **content);

//name struct
t_name	*ft_allocate_memory_name();
void	ft_free_memory_name(t_name *name, int exit_failure);

//attacking
void	ft_npc_check_ac(t_char *info, char **input);

//save file
int		ft_npc_check_info(t_char *info);
void	ft_npc_write_file(t_char *info, t_stats *stats, t_resistance *resistance);

//fclean
void	ft_fclean(void);

//initiative
void	ft_check_initiative(t_char *info);
void	ft_roll_initiative(t_char *info);

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

#endif
