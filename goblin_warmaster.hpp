#ifndef GOBLIN_WARMASTER_H
# define GOBLIN_WARMASTER_H

# include "armor.hpp"
# include "ranged_weapons.hpp"
# include "melee_weapons.hpp"
# include "libft/CPP_class/nullptr.hpp"
# include "character.hpp"
# include "initialize.hpp"
# include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

void	ft_goblin_warmaster_turn(t_char * info);

static const	t_stats GOBLIN_WARMASTER_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 0,
	.health = 45,
	.temp_hp = 5,
	.str = 16,
	.dex = 14,
	.con = 14,
	.inte = 12,
	.wis = 10,
	.cha = 10,
};

static const	t_save GOBLIN_WARMASTER_SAVE_MODS =
{
    .str = 3,
    .dex = 1,
	.inte = 1,
	.wis = 0, 
    .cha = 0,
	.con = 2,
};

static const	t_skills GOBLIN_WARMASTER_SKILL_MODS =
{
    .athletics = 4,
    .acrobatics = 1,
    .sleight_of_hand = 0,
    .stealth = 1,
    .arcana = 0,
    .history = 0,
    .investigation = 0,
    .nature = 0,
    .religion = 0,
    .animal_handling = 0,
    .insight = 0,
    .medicine = 0,
    .perception = 2,
    .survival = 2,
    .deception = 0,
    .intimidation = 2,
    .performance = 0,
    .persuasion = 0,
};

static const	t_attack GOBLIN_WARMASTER_ATTACK =
{
	.attack_bonus = 4,
	.ranged_bonus = 2,
};

static const	t_crit_mod GOBLIN_WARMASTER_CRIT =
{
	.attack = 1,
	.attack_d = 1,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance GOBLIN_WARMASTER_DEFAULT_RESISTANCE =
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

static const	t_equipment GOBLIN_WARMASTER_EQUIPMENT =
{
	.weapon = WOODEN_CLUB,
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

static const t_physical GOBLIN_WARMASTER_PHYSICAL =
{
	.height = 52,
	.weight = 50,
	.age = 25,
	.speed = 25,
};

static const t_char GOBLIN_WARMASTER_INFO =
{
	.level = 4,
	.mechanical = 0,
	.passive_perception = 14,
	.initiative = -1,
	.version_number = 2,
	.save_file = ft_nullptr,
	.name = ft_nullptr,
	.turn = ft_goblin_warmaster_turn,
	.loot = ft_nullptr,
	.hit_dice = INITIALIZ_HIT_DICE,
	.inventory = INITIALIZE_INVENTORY,
	.spells = INITIALIZE_SPELLS,
	.spell_slots = INITIALIZE_SPELL_SLOTS,
	.flags = INITIALIZE_FLAGS,
	.crit = GOBLIN_WARMASTER_CRIT,
	.attack_bonus = GOBLIN_WARMASTER_ATTACK,
	.bufs = INITIALIZE_BUFFS,
	.debufs = INITIALIZE_DEBUFFS,
	.concentration = INITIALIZE_CONCENTRATION,
	.d_resistance = GOBLIN_WARMASTER_DEFAULT_RESISTANCE,
	.c_resistance = INITIALIZE_CURRENT_RESISTANCE,
	.equipment = GOBLIN_WARMASTER_EQUIPMENT,
	.skill_mod = GOBLIN_WARMASTER_SKILL_MODS,
	.save_mod = GOBLIN_WARMASTER_SAVE_MODS,
	.stats = INITIALIZE_STATS,
	.dstats = GOBLIN_WARMASTER_DEFAULT_STATS,
	.feats = INITIALIZE_FEATS,
	.struct_name = ft_nullptr,
	.physical = GOBLIN_WARMASTER_PHYSICAL,
};

#endif
