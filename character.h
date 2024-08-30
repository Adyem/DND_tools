#ifndef CHARACTER_H
# define CHARACTER_H

# define ERROR_RESISTANCE 9999

typedef struct	s_buff t_buff;
typedef struct	s_char t_char;
typedef struct	s_name t_name;
typedef struct s_equipment_id t_equipment_id;

typedef int		(*cast_buff_debuff)(t_char *, const char **, t_buff *);
typedef void	(*c_action)(t_char *, t_equipment_id *);
typedef void	(*c_turn)(t_char *);

typedef t_char	*(*c_name)(int, const char **, t_name *, int);

typedef struct s_buff
{
	int					target_amount;
    char				*target;
    int					spell_id;
    int					dice_faces_mod;
    int					dice_amount_mod;
    int					duration;
	int					buff;
	int					error;
	cast_buff_debuff	cast_spell;
}	t_buff;


typedef struct s_name
{
	char	*name;
	c_name	function;
	t_name	*next;
}	t_name;

typedef struct	s_stats
{
	int	phase;
	int	turn;
	int	health;
	int	temp_hp;
	int	str;
	int	dex;
	int	con;
	int inte;
	int	wis;
	int cha;
}	t_stats;

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
}	t_skillsm;

typedef struct	s_savem
{
	int	str;
	int	dex;
	int	inte;
	int	wis;
	int	cha;
	int	con;
}	t_savem;

typedef struct	s_attack
{
	int	attack_bonus;
	int	ranged_bonus;
}	t_attack;

typedef struct	s_bless
{
	int		duration;
	int		dice_amount_mod;
	int		dice_faces_mod;
	int		base_mod;
	char	**target;
}	t_bless;

typedef struct	s_protective_winds
{
	int	duration;
}	t_protective_winds;

typedef struct	s_lightning_strike
{
	int	duration;
	int	amount;
	int distance;
	int	dice_amount;
	int	dice_faces;
	int	extra_damage;
}	t_lightning_strike;

typedef struct	s_air_totem
{
	char	*save_file;
	int		health;
	int		ac;
	int		knock_back_distance;
	int		erea_of_effect;
}	t_air_totem;

typedef struct	s_chaos_armor
{
	int	duration;
}	t_chaos_armor;

typedef struct	s_bufs
{
	t_bless				bless;
	t_protective_winds	protective_winds;
	t_lightning_strike	lightning_strike;
	t_chaos_armor		chaos_armor;
}	t_bufs;

typedef struct	s_hunters_mark
{
	int		amount;
	char	**caster_name;
}	t_hunters_mark;

typedef struct	s_blinded
{
	int	duration;
}	t_blinded;

typedef struct s_debufs
{
	t_hunters_mark	hunters_mark;
	t_blinded		blinded;
}	t_debufs;

typedef struct s_crit_mod
{
	int	attack;
	int	attack_d;
	int	save;
	int	skill;
	int	attack_fail;
	int	save_fail;
	int	skill_fail;
}	t_crit_mod;

typedef struct	s_concentration
{
	int		concentration;
	int		spell_id;
	int		dice_amount_mod;
	int		dice_faces_mod;
	int		base_mod;
	int		duration;
	char	**targets;
}	t_concentration;

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
}	t_resistance;

typedef struct s_feats
{
}	t_feats;

typedef struct s_equipment_action
{
	c_action	function;
	const char	*damage_type;
	const char	*stat;
	int			effect_type;
	int			effect_dice_amount;
	int			effect_dice_faces;
	int			bonus_mod;
}	t_equipment_action;


typedef struct s_equipment_id
{
	const char			*name;
	const char			*projectile_name;
	int					equipment_id;
	t_equipment_action	action_01;
	t_equipment_action	action_02;
	t_equipment_action	attack;
	t_skillsm			skill_mod;
	t_resistance		resistance;
	t_resistance		flat_dr;
	int					type;
	int					dex_ac_max_bonus;
	int					ac;
	int					str;
	int					dex;
	int					con;
	int					inte;
	int					wis;
	int					cha;
	int					initiative;
	int					effect_type;
	int					effect_dice_amount;
	int					effect_dice_faces;
	int					bonus_mod;
}	t_equipment_id;

typedef struct s_equipment
{
	t_equipment_id	weapon;
	t_equipment_id	offhand_weapon;
	t_equipment_id	ranged_weapon;
	t_equipment_id	armor;
	t_equipment_id	helmet;
	t_equipment_id	shield;
	t_equipment_id	boots;
	t_equipment_id	gloves;
	t_equipment_id	amulet;
	t_equipment_id	ring_01;
	t_equipment_id	ring_02;
	t_equipment_id	belt;
}	t_equipment;

typedef struct s_flags
{
	int				alreaddy_saved;
	int				error;
	int				flanking;
	int				advantage;
	int				prone;
}	t_flags;

typedef struct	s_char
{
	int				mechanical;
	int				passive_perception;
	int				initiative;
	int				version_number;
	char			*save_file;
	const char		*name;
	c_turn			turn;
	t_flags			flags;
	t_crit_mod		crit;
	t_attack		attack_bonus;
	t_bufs			bufs;
	t_debufs		debufs;
	t_concentration	concentration;
	t_resistance	d_resistance;
	t_resistance	c_resistance;
	t_equipment		equipment;
	t_skillsm		skill_mod;
	t_savem			save_mod;
	t_stats			stats;
	t_stats			dstats;
	t_feats			feats;
	t_name			*struct_name;
} t_char;

#endif
