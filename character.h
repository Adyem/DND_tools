#ifndef CHARACTER_H
# define CHARACTER_H

#include <stddef.h>
#include "include.h"

typedef struct	s_char t_char;
typedef struct	s_name t_name;

typedef void	(*c_action)(t_char *);
typedef void	(*c_turn)(t_char *);

typedef t_char	*(*c_name)(int, char **, t_name *, int);

typedef struct s_name
{
	char	*name;
	c_name	function;
	t_name	*next;
} t_name;

typedef struct	s_stats
{
	int	phase;
	int	turn;
	int	health;
	int	temp_hp;
	int	ac;
	int	str;
	int	dex;
	int	con;
	int inte;
	int	wis;
	int cha;
} t_stats;

typedef struct	s_skillsm
{
	int	athletics;
	int	acrobatics;
	int	sleight_of_hand;
	int	stealth;
	int	arcana;
	int	history;
	int	investigation;
	int	nature;
	int	religion;
	int	animal_handling;
	int	insight;
	int	medicine;
	int	perception;
	int	survival;
	int	deception;
	int	intimidation;
	int	performance;
	int	persuasion;
} t_skillsm;

typedef struct	s_savem
{
	int	str;
	int	dex;
	int	inte;
	int	wis;
	int	cha;
	int	con;
} t_savem;

typedef struct	s_attack
{
	int	attack_bonus;
	int	ranged_bonus;
} t_attack;

typedef struct	s_f_attack
{
	c_action	attack;
	c_action	ranged_attack;
} t_f_attack;

typedef struct	s_bless
{
	int		duration;
	int		dice_amount_mod;
	int		dice_faces_mod;
	int		base_mod;
	char	**target;
} t_bless;

typedef struct	s_protective_winds
{
	int	duration;
} t_protective_winds;

typedef struct	s_lightning_strike
{
	int	duration;
	int	amount;
	int distance;
	int	dice_amount;
	int	dice_faces;
	int	extra_damage;
} t_lightning_strike;

typedef struct	s_air_totem
{
	char	*save_file;
	int		health;
	int		ac;
	int		knock_back_distance;
	int		erea_of_effect;
} t_air_totem;

typedef struct	s_bufs
{
	t_bless				bless;
	t_protective_winds	protective_winds;
	t_lightning_strike	lightning_strike;
} t_bufs;

typedef struct	s_hunters_mark
{
	int		amount;
	char	**caster_name;
} t_hunters_mark;

typedef struct s_debufs
{
	t_hunters_mark hunters_mark;
} t_debufs;

typedef struct s_crit_mod
{
	int	attack;
	int	attack_d;
	int	save;
	int	skill;
	int	attack_fail;
	int	save_fail;
	int	skill_fail;
} t_crit_mod;

#define HUNTERS_MARK_ID 1
#define HUNTERS_MARK_NAME "hunters mark"
#define BLESS_ID 2
#define BLESS_NAME "bless"

typedef struct	s_concentration
{
	int		concentration;
	int		spell_id;
	int		dice_amount_mod;
	int		dice_faces_mod;
	int		base_mod;
	int		duration;
	char	**targets;
} t_concentration;

typedef struct	s_resistance
{
	int	acid;
	int	bludgeoning;
	int	cold;
	int	fire;
	int	force;
	int	lightning;
	int	necrotic;
	int	piercing;
	int	poison;
	int	psychic;
	int	radiant;
	int	slashing;
	int	thunder;
} t_resistance;

typedef struct	s_char
{
	int				passive_perception;
	int				initiative;
	int				version_number;
	int				free_save;
	char			*save_file;
	char			*name;
	int				advantage;
	c_turn			turn;
	t_crit_mod		crit;
	t_attack		attack_bonus;
	t_bufs			bufs;
	t_debufs		debufs;
	t_concentration	concentration;
	t_resistance	d_resistance;
	t_resistance	c_resistance;
	t_f_attack		f_attack;
	t_skillsm		skill_mod;
	t_savem			save_mod;
	t_stats			stats;
	t_stats			dstats;
	t_name			*struct_name;
} t_char;

#endif
