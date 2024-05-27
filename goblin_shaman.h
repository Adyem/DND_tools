#ifndef GOBLIN_SHAMAN_H
# define GOBLIN_SHAMAN_H
//the guards above only capital letters

#include "character.h"
#include "include.h"
#include "dnd_tools.h"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

//functions that are used in the struct need to be defined here
void	ft_goblin_shaman_turn(t_char *info);
void	ft_goblin_shaman_attack(t_char *info);
void	ft_goblin_shaman_ranged_attack(t_char *info);

//don't change the values in this struct they need to be all at -1!!!
static const	t_stats GOBLIN_SHAMAN_STATS =
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
static const	t_stats GOBLIN_SHAMAN_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 20,
	.temp_hp = 0,
	.ac = 11,
	.str = 12,
	.dex = 12,
	.con = 10,
	.inte = 10,
	.wis = 10,
	.cha = 8,
};

//possible modifiers for saving throws u can change these
static const	t_savem GOBLIN_SHAMAN_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
    .con = 0,
    .inte = 0,
    .wis = 0,
    .cha = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm GOBLIN_SHAMAN_SKILL_MODS =
{
    .athletics = 2,
    .acrobatics = 2,
    .sleight_of_hand = 3,
    .stealth = 3,
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
static const	t_attack GOBLIN_SHAMAN_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};

static const	t_f_attack GOBLIN_SHAMAN_F_ATTACK =
{
	.attack = ft_goblin_shaman_attack,
	.ranged_attack = ft_goblin_shaman_ranged_attack,
};

static const	t_bless GOBLIN_SHAMAN_BLESS =
{
	.duration = 0,
};

static const	t_protective_winds GOBLIN_SHAMAN_PROTECTIVE_WINDS =
{
	.duration = 0,
};

static const	t_lightning_strike GOBLIN_SHAMAN_LIGHTNING_STRIKE =
{
	.duration = 0,
	.amount = 0,
	.distance = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
};

static const	t_air_totem GOBLIN_SHAMAN_AIR_TOTEM =
{
	.save_file = "data/air_totem",
	.knock_back_distance = 0,
	.erea_of_effect = 0,
};

static const	t_bufs GOBLIN_SHAMAN_BUFFS =
{
	.bless = GOBLIN_SHAMAN_BLESS,
	.protective_winds = GOBLIN_SHAMAN_PROTECTIVE_WINDS,
	.lightning_strike = GOBLIN_SHAMAN_LIGHTNING_STRIKE,
};

static const	t_debufs GOBLIN_SHAMAN_DEBUFFS =
{
};

static const	t_crit_mod GOBLIN_SHAMAN_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_char GOBLIN_SHAMAN_INFO =
{
	.initiative = -1,
	.version_number = 1,
	.free_save = 1,
	.save_file = "data/goblin_shaman_shaman",
	.name = "goblin_shaman_shaman",
	.advantage = 0,
	.turn = ft_goblin_shaman_turn,
	.crit = GOBLIN_SHAMAN_CRIT,
	.bufs = GOBLIN_SHAMAN_BUFFS,
	.debufs = GOBLIN_SHAMAN_DEBUFFS,
	.attack_bonus = GOBLIN_SHAMAN_ATTACK,
	.f_attack = GOBLIN_SHAMAN_F_ATTACK,
	.skill_mod = GOBLIN_SHAMAN_SKILL_MODS,
	.save_mod = GOBLIN_SHAMAN_SAVE_MODS,
	.stats = GOBLIN_SHAMAN_STATS,
	.dstats = GOBLIN_SHAMAN_DEFAULT_STATS,
};

//Abilities
#define GOBLIN_SHAMAN_NIMBLE_ESCAPE "can use disengage as a bonus action"

#endif
