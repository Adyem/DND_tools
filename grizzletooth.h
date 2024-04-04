#ifndef GRIZZLETOOTH_H
# define GRIZZLETOOTH_H
//the guards above only capital letters

#include "dnd_tools.h"
#include "include.h"
#include "character.h"
#include <stddef.h>

//functions that are used in the struct need to be defined here
void	ft_grizzletooth_turn(t_char *info);
void	ft_grizzletooth_attack(t_char *info);
void	ft_grizzletooth_ranged_attack(t_char *info);

//don't change the values in this struct they need to be all at -1!!!
static const	t_stats GRIZZLETOOTH_STATS =
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
static const	t_stats GRIZZLETOOTH_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 50,
	.temp_hp = 0,
	.ac = 14,
	.str = 12,
	.dex = 18,
	.con = 10,
	.inte = 10,
	.wis = 10,
	.cha = 8,
};

//possible modifiers for saving throws u can change these
static const	t_savem GRIZZLETOOTH_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
    .con = 0,
    .inte = 0,
    .wis = 0,
    .cha = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm GRIZZLETOOTH_SKILL_MODS =
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
static const	t_attack GRIZZLETOOTH_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};

static const	t_f_attack GRIZZLETOOTH_F_ATTACK =
{
	.attack = ft_grizzletooth_attack,
	.ranged_attack = ft_grizzletooth_ranged_attack,
};

static const	t_bless GRIZZLETOOTH_BLESS =
{
	.duration = 0,
};

static const	t_protective_winds GRIZZLETOOTH_PROTECTIVE_WINDS =
{
	.duration = 0,
};

static const	t_lightning_strike GRIZZLETOOTH_LIGHTNING_STRIKE =
{
	.duration = 0,
	.amount = 0,
	.distance = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
};

static const	t_air_totem GRIZZLETOOTH_AIR_TOTEM =
{
	.save_file = "air_totem.txt",
	.knock_back_distance = 0,
	.erea_of_effect = 0,
};

static const	t_bufs GRIZZLETOOTH_BUFFS =
{
	.bless = GRIZZLETOOTH_BLESS,
	.protective_winds = GRIZZLETOOTH_PROTECTIVE_WINDS,
	.lightning_strike = GRIZZLETOOTH_LIGHTNING_STRIKE,
};

static const	t_debufs GRIZZLETOOTH_DEBUFFS =
{
};

static const	t_crit_mod GRIZZLETOOTH_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_char GRIZZLETOOTH_INFO =
{
	.initiative = -1,
	.version_number = 1,
	.save_file = "data/grizzletooth.txt",
	.name = "Grizzletooth",
	.advantage = 0,
	.turn = ft_grizzletooth_turn,
	.crit = GRIZZLETOOTH_CRIT,
	.bufs = GRIZZLETOOTH_BUFFS,
	.debufs = GRIZZLETOOTH_DEBUFFS,
	.attack_bonus = GRIZZLETOOTH_ATTACK,
	.f_attack = GRIZZLETOOTH_F_ATTACK,
	.skill_mod = GRIZZLETOOTH_SKILL_MODS,
	.save_mod = GRIZZLETOOTH_SAVE_MODS,
	.stats = GRIZZLETOOTH_STATS,
	.dstats = GRIZZLETOOTH_DEFAULT_STATS,
};

//Abilities
#define GRIZZLETOOTH_NIMBLE_ESCAPE "can use disengage as a bonus action"

#endif
