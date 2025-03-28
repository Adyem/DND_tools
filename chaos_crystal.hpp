#ifndef CHAOS_CRYSTAL_H
# define CHAOS_CRYSTAL_H

# include "character.hpp"
# include "initialize.hpp"
# include "libft/CPP_class/nullptr.hpp"
# include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

void	ft_chaos_crystal_turn(t_char * info);

static const	t_stats CHAOS_CRYSTAL_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 5,
	.temp_hp = 0,
	.str = 20,
	.dex = 20,
	.con = 20,
	.inte = 20,
	.wis = 20,
	.cha = 20,
};

static const	t_save CHAOS_CRYSTAL_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
	.inte = 0,
	.wis = 0, 
    .cha = 0,
	.con = 0,
};

static const	t_skills CHAOS_CRYSTAL_SKILL_MODS =
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

static const	t_attack CHAOS_CRYSTAL_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};


static const	t_crit_mod CHAOS_CRYSTAL_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance CHAOS_CRYSTAL_DEFAULT_RESISTANCE =
{
	.acid = 99,
	.bludgeoning = 99,
	.cold = 99,
	.fire = 99,
	.force = 99,
	.lightning = 99,
	.necrotic = 99,
	.piercing = 99,
	.poison = 99,
	.psychic = 99,
	.radiant = 99,
	.slashing = 99,
	.thunder = 99,
};


static const	t_equipment CHAOS_CRYSTAL_EQUIPMENT =
{
	.weapon = INITIALIZE_EQUIPMENT_ID,
	.offhand_weapon = INITIALIZE_EQUIPMENT_ID,
	.ranged_weapon = INITIALIZE_EQUIPMENT_ID,
	.armor = INITIALIZE_EQUIPMENT_ID,
	.helmet = INITIALIZE_EQUIPMENT_ID,
	.shield = INITIALIZE_EQUIPMENT_ID,
	.boots = INITIALIZE_EQUIPMENT_ID,
	.gloves = INITIALIZE_EQUIPMENT_ID,
	.amulet = INITIALIZE_EQUIPMENT_ID,
	.ring_01 = INITIALIZE_EQUIPMENT_ID,
	.ring_02 = INITIALIZE_EQUIPMENT_ID,
	.belt = INITIALIZE_EQUIPMENT_ID,
};

static const t_physical CHAOS_CRYSTAL_PHYSICAL =
{
    .height = 60,
    .weight = 500,
    .age = 200,
    .speed = 0,
};

static const t_char CHAOS_CRYSTAL_INFO =
{
    .level = 2,
    .mechanical = 1,
    .passive_perception = 15,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_chaos_crystal_turn,
	.loot = ft_nullptr,
	.hit_dice = INITIALIZ_HIT_DICE,
	.inventory = INITIALIZE_INVENTORY,
	.spells = INITIALIZE_SPELLS,
	.spell_slots = INITIALIZE_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = CHAOS_CRYSTAL_CRIT,
    .attack_bonus = CHAOS_CRYSTAL_ATTACK,
    .bufs = INITIALIZE_BUFFS,
    .debufs = INITIALIZE_DEBUFFS,
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = CHAOS_CRYSTAL_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = CHAOS_CRYSTAL_EQUIPMENT,
    .skill_mod = CHAOS_CRYSTAL_SKILL_MODS,
    .save_mod = CHAOS_CRYSTAL_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = CHAOS_CRYSTAL_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = CHAOS_CRYSTAL_PHYSICAL,
};

#endif
