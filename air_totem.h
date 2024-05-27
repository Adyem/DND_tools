#ifndef AIR_TOTEM_H
# define AIR_TOTEM_H
//the guards above only capital letters

#include "character.h"
#include "include.h"
#include "dnd_tools.h"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

//functions that are used in the struct need to be defined here
void	ft_air_totem_turn(t_char *info);
void	ft_air_totem_attack(t_char *info);

//don't change the values in this struct they need to be all at -1!!!
static const	t_stats AIR_TOTEM_STATS =
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
static const	t_stats AIR_TOTEM_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 0,
	.health = 20,
	.temp_hp = 0,
	.ac = 5,
	.str = 0,
	.dex = 0,
	.con = 0,
	.inte = 0,
	.wis = 0,
	.cha = 0,
};

//possible modifiers for saving throws u can change these
static const	t_savem AIR_TOTEM_SAVE_MODS =
{
    .str = 0,
    .dex = 0,
    .con = 0,
    .inte = 0,
    .wis = 0,
    .cha = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm AIR_TOTEM_SKILL_MODS =
{
    .athletics = 0,
    .acrobatics = 0,
    .sleight_of_hand = 0,
    .stealth = 0,
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
static const	t_attack AIR_TOTEM_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};

static const	t_f_attack AIR_TOTEM_F_ATTACK =
{
	.attack = NULL,
	.ranged_attack = NULL,
};

static const	t_bless AIR_TOTEM_BLESS =
{
	.duration = 0,
};

static const	t_protective_winds AIR_TOTEM_PROTECTIVE_WINDS =
{
	.duration = 0,
};

static const	t_lightning_strike AIR_TOTEM_LIGHTNING_STRIKE =
{
	.duration = 0,
	.amount = 0,
	.distance = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
};

static const	t_air_totem AIR_TOTEM_AIR_TOTEM =
{
	.save_file = "data/air_totem",
	.health = 0,
	.ac = 0,
	.knock_back_distance = 0,
	.erea_of_effect = 0,
};

static const	t_bufs AIR_TOTEM_BUFFS =
{
	.bless = AIR_TOTEM_BLESS,
	.protective_winds = AIR_TOTEM_PROTECTIVE_WINDS,
	.lightning_strike = AIR_TOTEM_LIGHTNING_STRIKE,
};

static const	t_debufs AIR_TOTEM_DEBUFFS =
{
};

static const	t_crit_mod AIR_TOTEM_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_char AIR_TOTEM_INFO =
{
	.initiative = -1,
	.version_number = 1,
	.free_save = 0,
	.save_file = "data/air_totem",
	.name = "air_totem",
	.advantage = 0,
	.turn = NULL,
	.crit = AIR_TOTEM_CRIT,
	.bufs = AIR_TOTEM_BUFFS,
	.debufs = AIR_TOTEM_DEBUFFS,
	.attack_bonus = AIR_TOTEM_ATTACK,
	.f_attack = AIR_TOTEM_F_ATTACK,
	.skill_mod = AIR_TOTEM_SKILL_MODS,
	.save_mod = AIR_TOTEM_SAVE_MODS,
	.stats = AIR_TOTEM_STATS,
	.dstats = AIR_TOTEM_DEFAULT_STATS,
};

#endif
