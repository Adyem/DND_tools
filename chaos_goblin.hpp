#ifndef CHAOS_GOBLIN_H
# define CHAOS_GOBLIN_H

# include "libft/CPP_class/nullptr.hpp"
# include "armor.hpp"
# include "ranged_weapons.hpp"
# include "melee_weapons.hpp"
# include "character.hpp"
# include "initialize.hpp"
# include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

void	ft_chaos_goblin_turn(t_char * info);

static const	t_stats CHAOS_GOBLIN_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 40,
	.temp_hp = 0,
	.str = 12,
	.dex = 16,
	.con = 10,
	.inte = 8,
	.wis = 10,
	.cha = 8,
};

static const	t_save CHAOS_GOBLIN_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
	.inte = 0,
	.wis = 0, 
    .cha = 0,
	.con = 0,
};

static const	t_skills CHAOS_GOBLIN_SKILL_MODS =
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

static const	t_attack CHAOS_GOBLIN_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};


static const	t_crit_mod CHAOS_GOBLIN_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance CHAOS_GOBLIN_DEFAULT_RESISTANCE =
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


static const	t_equipment CHAOS_GOBLIN_EQUIPMENT =
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

static const t_physical CHAOS_GOBLIN_PHYSICAL =
{
    .height = 48,
    .weight = 40,
    .age = 70,
    .speed = 30,
};

static const t_char CHAOS_GOBLIN_INFO =
{
    .level = 2,
    .mechanical = 0,
    .passive_perception = 15,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_chaos_goblin_turn,
	.loot = ft_nullptr,
	.hit_dice = INITIALIZ_HIT_DICE,
	.inventory = INITIALIZE_INVENTORY,
	.spells = INITIALIZE_SPELLS,
	.spell_slots = INITIALIZE_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = CHAOS_GOBLIN_CRIT,
    .attack_bonus = CHAOS_GOBLIN_ATTACK,
    .bufs = INITIALIZE_BUFFS,
    .debufs = INITIALIZE_DEBUFFS,
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = CHAOS_GOBLIN_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = CHAOS_GOBLIN_EQUIPMENT,
    .skill_mod = CHAOS_GOBLIN_SKILL_MODS,
    .save_mod = CHAOS_GOBLIN_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = CHAOS_GOBLIN_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = CHAOS_GOBLIN_PHYSICAL,
};

#endif
