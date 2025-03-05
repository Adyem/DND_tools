#ifndef CHARACTER_H
# define CHARACTER_H

#include "libft/CPP_class/file.hpp"

# define ERROR_RESISTANCE 9999

struct s_char;
struct s_buff;
struct s_name;
struct s_equipment_id;

typedef struct s_char t_char;
typedef struct s_buff t_buff;
typedef struct s_name t_name;
typedef struct s_equipment_id t_equipment_id;

typedef void (*c_action)(t_char *, s_equipment_id *, int);
typedef void 	(*c_turn)(t_char *);
typedef void 	(*c_loot)(t_char *);

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

typedef struct	s_skills
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
}	t_skills;

typedef struct	s_save
{
	int	str;
	int	dex;
	int	inte;
	int	wis;
	int	cha;
	int	con;
}	t_save;

typedef struct	s_attack
{
	int		attack_bonus;
	int		ranged_bonus;
}	t_attack;

typedef struct	s_buff_bless
{
	int		duration;
	int		dice_amount_mod;
	int		dice_faces_mod;
	int		base_mod;
	char	**caster_name;
}	t_buff_bless;

typedef struct	s_buff_protective_winds
{
	int	duration;
}	t_buff_protective_winds;

typedef struct	s_buff_lightning_strike
{
	int	duration;
	int	amount;
	int distance;
	int	dice_amount;
	int	dice_faces;
	int	extra_damage;
}	t_buff_lightning_strike;

typedef struct s_buff_flame_geyser
{
	int	amount;
    int duration;
	int	close_to_tower_d;
	int	tower_explode_d;
}	t_buff_flame_geyser;

typedef struct s_buff_meteor_strike
{
    int		duration;
	int		one_target_d;
	int		two_targets_d;
	int		three_targets_d;
	int		four_targets_d;
	int		five_targets_d;
    char	*target_id;
}	t_buff_meteor_strike;

typedef struct s_buff_earth_pounce
{
	int		active;
	int		base_damage;
	char	*target_id;
}	t_buff_earth_pounce;

typedef struct s_buff_arcane_pounce
{	
	int		active;
	int		magic_damage;
	int		erea_damage;
	char	*target_id;
}	t_buff_arcane_pounce;

typedef struct s_buff_frost_breath
{
	int		active;
	int		damage;
	char	*target_id;
}	t_buff_frost_breath;

typedef struct	s_buff_air_totem
{
	char	*save_file;
	int		health;
	int		ac;
	int		knock_back_distance;
	int		erea_of_effect;
}	t_buff_air_totem;

typedef struct	s_buff_chaos_armor
{
	int	duration;
}	t_buff_chaos_armor;

typedef struct	s_buff_magic_drain
{
	char	*target;
	int		damage;
	int		spell_slot_total_level_drain;
}	t_buff_magic_drain;

typedef struct	s_bufs
{
	t_buff_bless				bless;
	t_buff_protective_winds		protective_winds;
	t_buff_lightning_strike		lightning_strike;
	t_buff_lightning_strike		lightning_strikeV2;
	t_buff_flame_geyser			flame_geyser;
	t_buff_meteor_strike		meteor_strike;
	t_buff_chaos_armor			chaos_armor;
	t_buff_arcane_pounce		arcane_pounce;
	t_buff_earth_pounce			earth_pounce;
	t_buff_frost_breath			frost_breath;
	t_buff_magic_drain			magic_drain;
}	t_bufs;

typedef struct	s_debuff_hunters_mark
{
	int		amount;
	char	**caster_name;
}	t_debuff_hunters_mark;

typedef struct	s_debuff_blinded
{
	int	duration;
}	t_debuff_blinded;

typedef struct s_debufs
{
	t_debuff_hunters_mark	hunters_mark;
	t_debuff_blinded		blinded;
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
	int		extra;
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

typedef struct s_crackback
{
	int	active;
}	t_crackback;

typedef struct s_feats
{
	t_crackback	crackback;
}	t_feats;

typedef struct s_equipment_action
{
	c_action	function;
	const char	*damage_type;
	const char	*stat;
	int			effect_type;
	int			effect_dice_amount;
	int			effect_dice_faces;
	int			effect_secund_dice_amount;
	int			effect_secund_dice_faces;
	int			bonus_mod;
}	t_equipment_action;

typedef struct	s_saves
{
	int	str;
	int	dex;
	int	con;
	int inte;
	int	wis;
	int cha;
}	t_saves;

typedef struct s_equipment_id
{
	const char			*name;
	const char			*projectile_name;
	int					equipment_id;
	t_equipment_action	action_01;
	t_equipment_action	action_02;
	t_equipment_action	attack;
	t_skills			skill_mod;
	t_resistance		resistance;
	t_resistance		flat_dr;
	t_skills			skill_advantage;
	t_saves				save;
	t_saves				save_advantage;
	int					crit_attack_fail_bonus;
	int					crit_attack_succes_bonus;
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
	int					effect_id;
	int					effect_type;
	int					effect_dice_amount;
	int					effect_dice_faces;
	int					bonus_mod;
	int					slot;
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
	int				reaction_used;
	int				dont_save;
}	t_flags;

typedef struct s_physical
{
    int height;
    int weight;
    int age;
    int speed;
}	t_physical;

typedef struct	s_spell_slot
{
	int available;
	int total;
	int	level;
	int	replenishing_slot;
}	t_spell_slot;

typedef struct	s_spell_slots
{
	t_spell_slot	level_1;
	t_spell_slot	level_2;
	t_spell_slot	level_3;
	t_spell_slot	level_4;
	t_spell_slot	level_5;
	t_spell_slot	level_6;
	t_spell_slot	level_7;
	t_spell_slot	level_8;
	t_spell_slot	level_9;
	t_spell_slot	warlock;
}	t_spell_slots;

typedef struct s_spell_hunters_mark
{
	int		learned;
	int		base_level;
	int		casting_at_level;
	int		duration;
	int		dice_amount;
	int		dice_faces;
	int		extra_damage;
	int		upcast_extra_dice_face;
	int		upcast_extra_dice_amount;
	int		upcast_extra_damage;
}	t_spell_hunters_mark;

typedef struct s_spell_divine_smite
{
	int		learned;
	int		base_level;
	int		casting_at_level;
	int		dice_amount;
	int		dice_faces;
	int		extra_damage;
	int		upcast_extra_dice_face;
	int		upcast_extra_dice_amount;
	int		upcast_extra_damage;	
}	t_spell_divine_smite;

typedef struct s_spell_cure_wounds
{
	int		learned;
	int		base_level;
	int		casting_at_level;
	int		dice_amount;
	int		dice_faces;
	int		extra_healing;
	int		upcast_extra_dice_face;
	int		upcast_extra_dice_amount;
	int		upcast_extra_healing;	
}	t_spell_cure_wounds;

typedef struct s_spell_bless
{
	int		learned;
	int		base_level;
	int		casting_at_level;
	int		duration;
	int		target_amount;
	int		dice_faces;
	int		dice_amount;
	int		upcast_extra_targets;
	int		upcast_extra_duration;
	int		upcast_extra_dice_faces;
	int		upcast_extra_dice_amount;
}	t_spell_bless;

typedef struct	s_spells
{
	t_spell_cure_wounds		cure_wounds;
	t_spell_divine_smite	divine_smite;
	t_spell_hunters_mark	hunters_mark;
	t_spell_bless			bless;
}	t_spells;

typedef struct s_inventory
{
	int		gold;
}	t_inventory;

typedef struct s_hit_dice
{
	int	dice_amount;
	int dice_faces;
} t_hit_dice;

typedef struct	s_char
{
	int				level;
	int				mechanical;
	int				passive_perception;
	int				initiative;
	int				version_number;
	char			*save_file;
	const char		*name;
	c_turn			turn;
	c_loot			loot;
	t_hit_dice		hit_dice;
	t_inventory		inventory;
	t_spells		spells;
	t_spell_slots	spell_slots;
	t_flags			flags;
	t_crit_mod		crit;
	t_attack		attack_bonus;
	t_bufs			bufs;
	t_debufs		debufs;
	t_concentration	concentration;
	t_resistance	d_resistance;
	t_resistance	c_resistance;
	t_equipment		equipment;
	t_skills		skill_mod;
	t_save			save_mod;
	t_stats			stats;
	t_stats			dstats;
	t_feats			feats;
	t_name			*struct_name;
    t_physical      physical;
}	t_char;

typedef int		(*cast_buff_debuff)(t_char * , const char **, t_buff *);
typedef t_char *(*c_name)(int, const char **, t_name *, int);
typedef void (*t_spellcast_func)(t_char * character, bool critical_strike);

typedef struct s_known_spell
{
    const char      *cmd;
    int             *learned;
    t_spellcast_func cast_func;
}   t_known_spell;

typedef struct s_damage_info
{
    int mod;
    int result;
    int damage;
    int stat_mod;
    int dice_amount;
    int dice_faces;
}   t_damage_info;

typedef struct s_target_data
{
	ft_file	file[20];
	char	*Pchar_name[20];
	t_char 	*target[20];
	t_char	*target_copy[20];
	t_buff	*buff_info;
}	t_target_data;

typedef struct s_buff
{
	int					target_amount;
    char				*target;
	const char			*spell_name;
    int					spell_id;
    int					dice_faces_mod;
    int					dice_amount_mod;
	int					extra_mod;
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

#endif
