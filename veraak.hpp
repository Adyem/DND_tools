#ifndef VERAAK_H
# define VERAAK_H
//the guards above only capital letters

#include "armor.hpp"
#include "ranged_weapons.hpp"
#include "melee_weapons.hpp"
#include "identification.hpp"
#include "character.hpp"
#include "initialize.hpp"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

//change Veraak, veraak, VERAAK to the name of the mob
//functions that are used in the struct need to be defined here
void	ft_veraak_turn(t_char *info);

//these are the default stats u can change these
static const	t_stats VERAAK_DEFAULT_STATS =
{
	.phase = 1,
	.turn = 1,
	.health = 240,
	.temp_hp = 0,
	.str = 12,
	.dex = 18,
	.con = 12,
	.inte = 16,
	.wis = 8,
	.cha = 8,
};

//possible modifiers for saving throws u can change these
static const	t_savem VERAAK_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
	.inte = 0,
	.wis = 0, 
    .cha = 0,
	.con = 0,
};

//possible modifiers for skills u can change these
static const	t_skillsm VERAAK_SKILL_MODS =
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
static const	t_attack VERAAK_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};


static const	t_crit_mod VERAAK_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance VERAAK_DEFAULT_RESISTANCE =
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


static const	t_equipment VERAAK_EQUIPMENT =
{
	.weapon = STEEL_SWORD,
	.offhand_weapon = INITIALIZE_EQUIPMENT_ID,
	.ranged_weapon = CHAOS_WAND,
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

static const t_char VERAAK_INFO =
{
	.level = 2,
	.mechanical = 0,
	.passive_perception = 15,
	.initiative = -1,
	.version_number = 2,
	.save_file = nullptr,
	.name = nullptr,
	.turn = ft_veraak_turn,
	.flags = INITIALIZE_FLAGS,
	.crit = VERAAK_CRIT,
	.attack_bonus = VERAAK_ATTACK,
	.bufs = INITIALIZE_BUFFS,
	.debufs = INITIALIZE_DEBUFFS,
	.concentration = INITIALIZE_CONCENTRATION,
	.d_resistance = VERAAK_DEFAULT_RESISTANCE,
	.c_resistance = INITIALIZE_CURRENT_RESISTANCE,
	.equipment = VERAAK_EQUIPMENT,
	.skill_mod = VERAAK_SKILL_MODS,
	.save_mod = VERAAK_SAVE_MODS,
	.stats = INITIALIZE_STATS,
	.dstats = VERAAK_DEFAULT_STATS,
	.feats = INITIALIZE_FEATS,
	.struct_name = nullptr,
};

//Abilities
#define CHAOS_SMASH "Veraak conjures a hammer made out of dark energy hitting his" \
	" target with it dealing damage based on his armor class\n" \
	"10-12 ac -> 15 " DAMAGE_TYPE_FORCE " damage\n" \
	"13-15 ac -> 10 " DAMAGE_TYPE_FORCE " damage\n" \
	"16-17 ac -> 8 " DAMAGE_TYPE_FORCE " damage\n" \
	"18-19 ac -> 6 " DAMAGE_TYPE_FORCE " damage\n" \
	"20-21 ac -> 4 " DAMAGE_TYPE_FORCE " damage\n" \
	"22->23 ac -> 2 " DAMAGE_TYPE_FORCE " damage\n" \
	"24 ac and higher -> 0 damage\n"
#define CHAOS_BREATH "annyone in a 90 degree cone in front of veraak needs to make a" \
    " dc 12 dex save, on a failed save takes 10 " DAMAGE_TYPE_NECROTIC " damage and half on a succesfull one\n"

#endif