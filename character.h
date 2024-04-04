#ifndef CHARACTER_H
# define CHARACTER_H

typedef struct s_char t_char;

typedef void	(*c_action)(t_char *);
typedef void	(*c_turn)(t_char *);

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
	int	duration;
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

typedef struct s_debufs
{
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

typedef struct	s_char
{
	int			initiative;
	int			version_number;
	char		*save_file;
	char		*name;
	int			advantage;
	c_turn		turn;
	t_crit_mod	crit;
	t_attack	attack_bonus;
	t_bufs		bufs;
	t_debufs	debufs;
	t_f_attack	f_attack;
	t_skillsm	skill_mod;
	t_savem		save_mod;
	t_stats		stats;
	t_stats		dstats;
} t_char;

#endif
