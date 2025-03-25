#ifndef ANCIENT_PREDATORY_BEAST_HPP
# define ANCIENT_PREDATORY_BEAST_HPP

#include "ranged_weapons.hpp"
#include "melee_weapons.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "initialize.hpp"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

void	ft_ancient_predatory_beast_turn(t_char * info);
void	ft_ancient_predatory_beast_loot(t_char * info);

static const	t_stats ANCIENT_PREDATORY_BEAST_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
	.health = 180,
	.temp_hp = 0,
	.str = 21,
	.dex = 14,
	.con = 15,
	.inte = 3,
	.wis = 12,
	.cha = 6,
};

static const	t_save ANCIENT_PREDATORY_BEAST_SAVE_MODS =
{
    .str = 0,
    .dex = 0,
	.inte = 0,
	.wis = 0, 
    .cha = 0,
	.con = 3,
};

static const	t_skills ANCIENT_PREDATORY_BEAST_SKILL_MODS =
{
    .athletics = 0,
    .acrobatics = 0,
    .sleight_of_hand = 0,
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

static const	t_attack ANCIENT_PREDATORY_BEAST_ATTACK =
{
	.attack_bonus = 2,
	.ranged_bonus = 0,
};


static const	t_crit_mod ANCIENT_PREDATORY_BEAST_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance ANCIENT_PREDATORY_BEAST_DEFAULT_RESISTANCE =
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

static const	t_equipment ANCIENT_PREDATORY_BEAST_EQUIPMENT =
{
	.weapon = STEEL_SWORD,
	.offhand_weapon = INITIALIZE_EQUIPMENT_ID,
	.ranged_weapon = WOODEN_BOW,
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

static const t_physical ANCIENT_PREDATORY_BEAST_PHYSICAL =
{
    .height = 0,
    .weight = 0,
    .age = 0,
    .speed = 0,
};

static const t_spell_slot ANCIENT_PREDATORY_BEAST_SPELL_SLOT =
{
	.available = 0,
	.total = 0,
	.level = 0,
	.replenishing_slot = 0,
};

static const t_spell_slots ANCIENT_PREDATORY_BEAST_SPELL_SLOTS =
{
	.level_1 = INITIALIZE_SPELL_SLOT,
	.level_2 = INITIALIZE_SPELL_SLOT,
	.level_3 = INITIALIZE_SPELL_SLOT,
	.level_4 = INITIALIZE_SPELL_SLOT,
	.level_5 = INITIALIZE_SPELL_SLOT,
	.level_6 = INITIALIZE_SPELL_SLOT,
	.level_7 = INITIALIZE_SPELL_SLOT,
	.level_8 = INITIALIZE_SPELL_SLOT,
	.level_9 = INITIALIZE_SPELL_SLOT,
	.warlock = INITIALIZE_SPELL_SLOT,
};

static const t_inventory ANCIENT_PREDATORY_BEAST_INVENTORY
{
	.gold = 0,
};

constexpr t_hit_dice ANCIENT_PREDATORY_BEAST_HIT_DICE =
{
	.dice_amount = 0,
	.dice_faces = 0,
};

static const t_char ANCIENT_PREDATORY_BEAST_INFO =
{
	.level = 0,
	.mechanical = 0,
	.passive_perception = 15,
	.initiative = -1,
	.version_number = 2,
	.save_file = ft_nullptr,
	.name = ft_nullptr,
	.turn = ft_ancient_predatory_beast_turn,
	.loot = ft_ancient_predatory_beast_loot,
	.hit_dice = ANCIENT_PREDATORY_BEAST_HIT_DICE,
	.inventory = ANCIENT_PREDATORY_BEAST_INVENTORY,
	.spells = INITIALIZE_SPELLS,
	.spell_slots = ANCIENT_PREDATORY_BEAST_SPELL_SLOTS,
	.flags = INITIALIZE_FLAGS,
	.crit = ANCIENT_PREDATORY_BEAST_CRIT,
	.attack_bonus = ANCIENT_PREDATORY_BEAST_ATTACK,
	.bufs = INITIALIZE_BUFFS,
	.debufs = INITIALIZE_DEBUFFS,
	.concentration = INITIALIZE_CONCENTRATION,
	.d_resistance = ANCIENT_PREDATORY_BEAST_DEFAULT_RESISTANCE,
	.c_resistance = INITIALIZE_CURRENT_RESISTANCE,
	.equipment = ANCIENT_PREDATORY_BEAST_EQUIPMENT,
	.skill_mod = ANCIENT_PREDATORY_BEAST_SKILL_MODS,
	.save_mod = ANCIENT_PREDATORY_BEAST_SAVE_MODS,
	.stats = INITIALIZE_STATS,
	.dstats = ANCIENT_PREDATORY_BEAST_DEFAULT_STATS,
	.feats = INITIALIZE_FEATS,
	.struct_name = ft_nullptr,
	.physical = ANCIENT_PREDATORY_BEAST_PHYSICAL,
};

template <int Amount, int Faces>
struct ValidateHitDice
{
    static_assert
	(
        ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
        (Amount <= 40 && Faces <= 12),
        "Invalid TEMPLATE_HIT_DICE values: Either both must be 0 or both at least 1, " \
			"and the dice amount must not exceed 40, the dice faces must not exceed 12."
    );
};

inline ValidateHitDice<ANCIENT_PREDATORY_BEAST_HIT_DICE.dice_amount, ANCIENT_PREDATORY_BEAST_HIT_DICE.dice_faces> validation_instance;

#endif
