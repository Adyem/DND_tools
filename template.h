#ifndef TEMPLATE_H
# define TEMPLATE_H
//the guards above only capital letters

#include "character.h"
#include "initialize.h"
#include "include.h"
#include "dnd_tools.h"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

//change Template, template, TEMPLATE to the name of the mob
//functions that are used in the struct need to be defined here
void	ft_template_turn(t_char *info);
void	ft_template_attack(t_char *info);
void	ft_template_ranged_attack(t_char *info);

//don't change the values in this struct they need to be all at -1!!!
static const	t_stats TEMPLATE_STATS =
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
static const	t_stats TEMPLATE_DEFAULT_STATS =
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
static const	t_savem TEMPLATE_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
	.inte = 0,
	.wis = 0, 
    .cha = 0,
	.con = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm TEMPLATE_SKILL_MODS =
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
static const	t_attack TEMPLATE_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};

static const	t_f_attack TEMPLATE_F_ATTACK =
{
	.attack = ft_template_attack,
	.ranged_attack = ft_template_ranged_attack,
};

static const	t_crit_mod TEMPLATE_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance TEMPLATE_DEFAULT_RESISTANCE =
{
	.acid = 0,
	.bludgeoning = 0,
	.cold = 0,
	.fire = 0,
	.force = 0,
	.lightning = 0,
	.necrotic = 0,
	.piercing = 0,
	.poison = 0,
	.psychic = 0,
	.radiant = 0,
	.slashing = 0,
	.thunder = 0,
};

static const	t_resistance TEMPLATE_CURRENT_RESISTANCE =
{
	.acid = -501,
	.bludgeoning = -501,
	.cold = -501,
	.fire = -501,
	.force = -501,
	.lightning = -501,
	.necrotic = -501,
	.piercing = -501,
	.poison = -501,
	.psychic = -501,
	.radiant = -501,
	.slashing = -501,
	.thunder = -501,
};

static const t_char TEMPLATE_INFO =
{
    .passive_perception = 15,
    .initiative = -1,
    .version_number = 2,
    .free_save = 1,
    .save_file = "data/template",
    .name = "template",
    .advantage = 0,
    .turn = ft_template_turn,
    .crit = TEMPLATE_CRIT,
    .attack_bonus = TEMPLATE_ATTACK,
    .bufs = INITIALIZE_BUFFS,
    .debufs = INITIALIZE_DEBUFFS,
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = TEMPLATE_DEFAULT_RESISTANCE,
    .c_resistance = TEMPLATE_CURRENT_RESISTANCE,
    .f_attack = TEMPLATE_F_ATTACK,
    .skill_mod = TEMPLATE_SKILL_MODS,
    .save_mod = TEMPLATE_SAVE_MODS,
    .stats = TEMPLATE_STATS,
    .dstats = TEMPLATE_DEFAULT_STATS,
    .struct_name = NULL,
};


//Abilities
#endif
