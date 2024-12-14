#ifndef FRANK_HPP
# define FRANK_HPP

#include "melee_weapons.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "initialize.hpp"
#include "armor.hpp"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

void	ft_frank_turn(SharedPtr<t_char> info);

static const	t_stats FRANK_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 75,
	.temp_hp = 0,
	.str = 14,
	.dex = 18,
	.con = 14,
	.inte = 6,
	.wis = 6,
	.cha = 6,
};

static const	t_savem FRANK_SAVE_MODS =
{
    .str = 2,
    .dex = 3,
	.inte = -2,
	.wis = -2, 
    .cha = -2,
	.con = 2,
};

static const	t_skillsm FRANK_SKILL_MODS =
{
    .athletics = 5,
    .acrobatics = 5,
    .sleight_of_hand = 0,
    .stealth = 5,
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

static const	t_attack FRANK_ATTACK =
{
	.attack_bonus = 4,
	.ranged_bonus = 0,
};


static const	t_crit_mod FRANK_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance FRANK_DEFAULT_RESISTANCE =
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


static const	t_equipment FRANK_EQUIPMENT =
{
	.weapon = CLAW,
	.offhand_weapon = CLAW_OH,
	.ranged_weapon = INITIALIZE_EQUIPMENT_ID,
	.armor = WOLF_PELT,
	.helmet = INITIALIZE_EQUIPMENT_ID,
	.shield = INITIALIZE_EQUIPMENT_ID,
	.boots = INITIALIZE_EQUIPMENT_ID,
	.gloves = INITIALIZE_EQUIPMENT_ID,
	.amulet = INITIALIZE_EQUIPMENT_ID,
	.ring_01 = INITIALIZE_EQUIPMENT_ID,
	.ring_02 = INITIALIZE_EQUIPMENT_ID,
	.belt = INITIALIZE_EQUIPMENT_ID,
};

static const t_physical FRANK_PHYSICAL =
{
    .height = 110,
    .weight = 60,
    .age = 6,
    .speed = 50,
};

static const t_char FRANK_INFO =
{
	.level = 0,
	.mechanical = 0,
	.passive_perception = 15,
	.initiative = -1,
	.version_number = 2,
	.save_file = ft_nullptr,
	.name = ft_nullptr,
	.turn = ft_frank_turn,
	.spells = INITIALIZE_SPELLS,
	.spell_slots = INITIALIZE_SPELL_SLOTS,
	.flags = INITIALIZE_FLAGS,
	.crit = FRANK_CRIT,
	.attack_bonus = FRANK_ATTACK,
	.bufs = INITIALIZE_BUFFS,
	.debufs = INITIALIZE_DEBUFFS,
	.concentration = INITIALIZE_CONCENTRATION,
	.d_resistance = FRANK_DEFAULT_RESISTANCE,
	.c_resistance = INITIALIZE_CURRENT_RESISTANCE,
	.equipment = FRANK_EQUIPMENT,
	.skill_mod = FRANK_SKILL_MODS,
	.save_mod = FRANK_SAVE_MODS,
	.stats = INITIALIZE_STATS,
	.dstats = FRANK_DEFAULT_STATS,
	.feats = INITIALIZE_FEATS,
	.struct_name = ft_nullptr,
	.physical = FRANK_PHYSICAL,
};

#endif
