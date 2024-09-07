#ifndef GOBLIN_H
# define GOBLIN_H
//the guards above only capital letters

# include "armor.hpp"
# include "ranged_weapons.hpp"
# include "melee_weapons.hpp"
# include "character.hpp"
# include "initialize.hpp"
# include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

//functions that are used in the struct need to be defined here
void	ft_goblin_turn(t_char *info);

//these are the default stats u can change these
static const	t_stats GOBLIN_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 0,
	.health = 25,
	.temp_hp = 0,
	.str = 12,
	.dex = 16,
	.con = 10,
	.inte = 10,
	.wis = 10,
	.cha = 8,
};

//possible modifiers for saving throws u can change these
static const	t_savem GOBLIN_SAVE_MODS =
{
    .str = 1,
    .dex = 2,
	.inte = 0,
	.wis = 0, 
    .cha = 0,
	.con = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm GOBLIN_SKILL_MODS =
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
static const	t_attack GOBLIN_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};


static const	t_crit_mod GOBLIN_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance GOBLIN_DEFAULT_RESISTANCE =
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


static const	t_equipment GOBLIN_EQUIPMENT =
{
	.weapon = STEEL_SWORD,
	.offhand_weapon = INITIALIZE_EQUIPMENT_ID,
	.ranged_weapon = WOODEN_BOW,
	.armor = LEATHER_ARMOR,
	.helmet = INITIALIZE_EQUIPMENT_ID,
	.shield = INITIALIZE_EQUIPMENT_ID,
	.boots = INITIALIZE_EQUIPMENT_ID,
	.gloves = INITIALIZE_EQUIPMENT_ID,
	.amulet = INITIALIZE_EQUIPMENT_ID,
	.ring_01 = INITIALIZE_EQUIPMENT_ID,
	.ring_02 = INITIALIZE_EQUIPMENT_ID,
	.belt = INITIALIZE_EQUIPMENT_ID,
};

static const t_char GOBLIN_INFO =
{
	.level = 2,
	.mechanical = 0,
	.passive_perception = 12,
	.initiative = -1,
	.version_number = 2,
	.save_file = NULL,
	.name = NULL,
	.turn = ft_goblin_turn,
	.flags = INITIALIZE_FLAGS,
	.crit = GOBLIN_CRIT,
	.attack_bonus = GOBLIN_ATTACK,
	.bufs = INITIALIZE_BUFFS,
	.debufs = INITIALIZE_DEBUFFS,
	.concentration = INITIALIZE_CONCENTRATION,
	.d_resistance = GOBLIN_DEFAULT_RESISTANCE,
	.c_resistance = INITIALIZE_CURRENT_RESISTANCE,
	.equipment = GOBLIN_EQUIPMENT,
	.skill_mod = GOBLIN_SKILL_MODS,
	.save_mod = GOBLIN_SAVE_MODS,
	.stats = INITIALIZE_STATS,
	.dstats = GOBLIN_DEFAULT_STATS,
	.feats = INITIALIZE_FEATS,
	.struct_name = NULL,
};

#endif
