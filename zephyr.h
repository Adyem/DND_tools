#ifndef ZEPHYR_H
# define ZEPHYR_H
//the guards above only capital letters

#include "character.h"
#include "include.h"
#include "dnd_tools.h"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

//functions that are used in the struct need to be defined here
void	ft_zephyr_turn(t_char *info);
void	ft_zephyr_attack(t_char *info);
void	ft_zephyr_ranged_attack(t_char *info);

//don't change the values in this struct they need to be all at -1!!!
static const	t_stats ZEPHYR_STATS =
{
	.phase = -1,
	.turn = -1,
	.health = -1,
	.temp_hp = -1,
	.ac = -1,
	.str = -1,
	.dex = -1,
	.con = -1,
	.inte = -1,
	.wis = -1,
	.cha = -1,
};

//these are the default stats u can change these
static const	t_stats ZEPHYR_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 100,
	.temp_hp = 0,
	.ac = 14,
	.str = 16,
	.dex = 16,
	.con = 16,
	.inte = 12,
	.wis = 12,
	.cha = 8,
};

//possible modifiers for saving throws u can change these
static const	t_savem ZEPHYR_SAVE_MODS =
{
    .str = 2,
    .dex = 4,
    .con = 2,
    .inte = 0,
    .wis = 0,
    .cha = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm ZEPHYR_SKILL_MODS =
{
    .athletics = 0,
    .acrobatics = 0,
    .sleight_of_hand = 4,
    .stealth = 4,
    .arcana = 0,
    .history = 0,
    .investigation = 0,
    .nature = 0,
    .religion = 0,
    .animal_handling = 0,
    .insight = 0,
    .medicine = 0,
    .perception = 0,
    .survival = 0,
    .deception = 0,
    .intimidation = 0,
    .performance = 0,
    .persuasion = 0,
};

//possible attack modifiers change here
static const	t_attack ZEPHYR_ATTACK =
{
	.attack_bonus = 1,
	.ranged_bonus = 1,
};

static const	t_f_attack ZEPHYR_F_ATTACK =
{
	.attack = ft_zephyr_attack,
	.ranged_attack = ft_zephyr_ranged_attack,
};

static const	t_bless ZEPHYR_BLESS =
{
	.duration = 0,
};

static const	t_protective_winds ZEPHYR_PROTECTIVE_WINDS =
{
	.duration = 0,
};

static const	t_lightning_strike ZEPHYR_LIGHTNING_STRIKE =
{
	.duration = 0,
	.amount = 3,
	.distance = 5,
	.dice_amount = 1,
	.dice_faces = 8,
	.extra_damage = 3,
};

static const	t_air_totem ZEPHYR_AIR_TOTEM =
{
	.save_file = "data/air_totem",
	.knock_back_distance = 20,
	.erea_of_effect = 20,
};

static const	t_bufs ZEPHYR_BUFFS =
{
	.bless = ZEPHYR_BLESS,
	.protective_winds = ZEPHYR_PROTECTIVE_WINDS,
	.lightning_strike = ZEPHYR_LIGHTNING_STRIKE,
};

static const	t_debufs ZEPHYR_DEBUFFS =
{
};

static const	t_crit_mod ZEPHYR_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_char ZEPHYR_INFO =
{
	.initiative = -1,
	.version_number = 1,
	.free_save = 0,
	.save_file = "data/zephyr",
	.name = "zephyr",
	.advantage = 0,
	.turn = ft_zephyr_turn,
	.crit = ZEPHYR_CRIT,
	.bufs = ZEPHYR_BUFFS,
	.debufs = ZEPHYR_DEBUFFS,
	.attack_bonus = ZEPHYR_ATTACK,
	.f_attack = ZEPHYR_F_ATTACK,
	.skill_mod = ZEPHYR_SKILL_MODS,
	.save_mod = ZEPHYR_SAVE_MODS,
	.stats = ZEPHYR_STATS,
	.dstats = ZEPHYR_DEFAULT_STATS,
};

//ABILITIES
#define ZEPHYR_AIR_TOTEM "Air Totem:" \
	" Zephyr the swift summons a air elemental totem, when the totem" \
	" is summoned and at the beginning of zephyr his turn anyone within 20ft. of the" \
	" totem gets pushed back to 20 ft. distance from the totem, the totem has 5AC and" \
	" 20HP."
#define ZEPHYR_GUST_OF_WIND "Gust of wind:" \
	" The target is hit by a gust of wind and needs to make a" \
	" DC12 strength saving throw, on a fail the target is knocked back 10ft. and takes" \
	" 5 damage, on a roll of 5 or below tha target is knocked down."
#define ZEPHYR_LIHGTNING_STRIKE "Lightning strike:" \
	" A few indicators appear revealing 3 random locations" \
	" were lightning is about to strike, at the beginning of his next turn annyone" \
	" within 5ft. will take 1d8 + 3 lightning damage"
#define ZEPHYR_PROTECTIVE_WINDS "Protective winds:" \
	" Zephyr the swift creates protective winds around him," \
	" anny projectile launched at him will be fired back at the attacker using their own" \
	" to hit roll as an attack on that character. This barrier lasts untill his next turn"
#define ZEPHYR_CHAIN_LIGHTNING "Chain lightning:" \
	" Zephyr targets a player casting chain lightning dealing" \
	" 4 lightning damage, it bounces to a target within 15 ft. that hasn't been" \
	" targetted by the spell yet dealing 4 + 2 damage for each time it bounced." \
	" if the affected players succeed on a DC12 dex save they take half damage"

#define ZEPHYR_NIMBLE_ESCAPE "can use disengage as a bonus action"

#endif
