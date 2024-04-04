#ifndef AIR_GOBLIN_SHAMAN_H
# define AIR_GOBLIN_SHAMAN_H
//the guards above only capital letters

#include "dnd_tools.h"
#include "include.h"
#include "character.h"
#include <stddef.h>

//functions that are used in the struct need to be defined here
void	ft_air_goblin_turn(t_char *info);
void	ft_air_goblin_attack(t_char *info);
void	ft_air_goblin_ranged_attack(t_char *info);

//don't change the values in this struct they need to be all at -1!!!
static const	t_stats AIR_GOBLIN_SHAMAN_STATS =
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
static const	t_stats AIR_GOBLIN_SHAMAN_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 22,
	.temp_hp = 0,
	.ac = 12,
	.str = 14,
	.dex = 14,
	.con = 12,
	.inte = 16,
	.wis = 14,
	.cha = 8,
};

//possible modifiers for saving throws u can change these
static const	t_savem AIR_GOBLIN_SHAMAN_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
    .con = 0,
    .inte = 0,
    .wis = 0,
    .cha = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm AIR_GOBLIN_SHAMAN_SKILL_MODS =
{
    .athletics = 0,
    .acrobatics = 0,
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
static const	t_attack AIR_GOBLIN_SHAMAN_ATTACK =
{
	.attack_bonus = 1,
	.ranged_bonus = 1,
};

static const	t_f_attack AIR_GOBLIN_SHAMAN_F_ATTACK =
{
	.attack = ft_air_goblin_attack,
	.ranged_attack = ft_air_goblin_ranged_attack,
};

static const	t_bless AIR_GOBLIN_SHAMAN_BLESS =
{
	.duration = 0,
};

static const	t_protective_winds AIR_GOBLIN_SHAMAN_PROTECTIVE_WINDS =
{
	.duration = 0,
};

static const	t_lightning_strike AIR_GOBLIN_SHAMAN_LIGHTNING_STRIKE =
{
	.duration = 0,
	.amount = 0,
	.distance = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
};

static const	t_air_totem AIR_GOBLIN_SHAMAN_AIR_TOTEM =
{
	.save_file = "air_totem.txt",
	.knock_back_distance = 0,
	.erea_of_effect = 0,
};

static const	t_bufs AIR_GOBLIN_SHAMAN_BUFFS =
{
	.bless = AIR_GOBLIN_SHAMAN_BLESS,
	.protective_winds = AIR_GOBLIN_SHAMAN_PROTECTIVE_WINDS,
	.lightning_strike = AIR_GOBLIN_SHAMAN_LIGHTNING_STRIKE,
};

static const	t_debufs AIR_GOBLIN_SHAMAN_DEBUFFS =
{
};

static const	t_crit_mod AIR_GOBLIN_SHAMAN_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_char AIR_GOBLIN_SHAMAN_INFO =
{
	.initiative = -1,
	.version_number = 1,
	.save_file = "data/air_goblin_shaman.txt",
	.name = "Air_goblin_shaman",
	.advantage = 0,
	.turn = ft_air_goblin_turn,
	.crit = AIR_GOBLIN_SHAMAN_CRIT,
	.bufs = AIR_GOBLIN_SHAMAN_BUFFS,
	.debufs = AIR_GOBLIN_SHAMAN_DEBUFFS,
	.attack_bonus = AIR_GOBLIN_SHAMAN_ATTACK,
	.f_attack = AIR_GOBLIN_SHAMAN_F_ATTACK,
	.skill_mod = AIR_GOBLIN_SHAMAN_SKILL_MODS,
	.save_mod = AIR_GOBLIN_SHAMAN_SAVE_MODS,
	.stats = AIR_GOBLIN_SHAMAN_STATS,
	.dstats = AIR_GOBLIN_SHAMAN_DEFAULT_STATS,
};

//Abilities
#define AIR_GOBLIN_SHAMAN_NIMBLE_ESCAPE "can use disengage as a bonus action"

#endif
