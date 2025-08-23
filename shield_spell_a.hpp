#ifndef SHIELD_SPELL_A_HPP
# define SHIELD_SPELL_A_HPP

#include "ranged_weapons.hpp"
#include "melee_weapons.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "initialize.hpp"
#include <stddef.h>

typedef struct	s_name t_name;
typedef struct	s_char t_char;

void	ft_shield_spell_a_turn(t_char * info);
void	ft_shield_spell_a_loot(t_char * info);

static const	t_stats SHIELD_SPELL_A_DEFAULT_STATS =
{
	.phase = 0,
	.turn = 1,
    .health = 3,
	.temp_hp = 0,
	.str = 12,
	.dex = 18,
	.con = 10,
	.inte = 10,
	.wis = 10,
	.cha = 8,
};

static const	t_save SHIELD_SPELL_A_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
	.inte = 0,
	.wis = 0, 
    .cha = 0,
	.con = 0,
};

static const	t_skills SHIELD_SPELL_A_SKILL_MODS =
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

static const	t_attack SHIELD_SPELL_A_ATTACK =
{
	.attack_bonus = 0,
	.ranged_bonus = 0,
};


static const	t_crit_mod SHIELD_SPELL_A_CRIT =
{
	.attack = 0,
	.attack_d = 0,
	.save = 0,
	.skill = 0,
	.attack_fail = 0,
	.save_fail = 0,
	.skill_fail = 0,
};

static const	t_resistance SHIELD_SPELL_A_DEFAULT_RESISTANCE =
{
	.acid = 100,
	.bludgeoning = 100,
	.cold = 100,
	.fire = 100,
	.force = 100,
	.lightning = 100,
	.necrotic = 100,
	.piercing = 100,
	.poison = 100,
	.psychic = 100,
	.radiant = 100,
	.slashing = 100,
	.thunder = 100,
};

static const	t_equipment SHIELD_SPELL_A_EQUIPMENT =
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

static const t_physical SHIELD_SPELL_A_PHYSICAL =
{
    .height = 0,
    .weight = 0,
    .age = 0,
    .speed = 0,
};

static const t_spell_slot SHIELD_SPELL_A_SPELL_SLOT =
{
	.available = 0,
	.total = 0,
	.level = 0,
	.replenishing_slot = 0,
};

static const t_spell_slots SHIELD_SPELL_A_SPELL_SLOTS =
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

static const t_inventory SHIELD_SPELL_A_INVENTORY
{
	.gold = 0,
};

constexpr t_hit_dice SHIELD_SPELL_A_HIT_DICE =
{
	.dice_amount = 0,
	.dice_faces = 0,
};

static const t_char SHIELD_SPELL_A_INFO =
{
	.level = 0,
	.mechanical = 0,
	.passive_perception = 15,
	.initiative = -1,
	.version_number = 2,
	.save_file = ft_nullptr,
	.name = ft_nullptr,
	.turn = ft_shield_spell_a_turn,
	.drop_loot = ft_shield_spell_a_loot,
	.loot = INITIALIZE_LOOT,
	.hit_dice = SHIELD_SPELL_A_HIT_DICE,
	.inventory = SHIELD_SPELL_A_INVENTORY,
	.spells = INITIALIZE_SPELLS,
	.spell_slots = SHIELD_SPELL_A_SPELL_SLOTS,
	.flags = INITIALIZE_FLAGS,
	.crit = SHIELD_SPELL_A_CRIT,
	.attack_bonus = SHIELD_SPELL_A_ATTACK,
	.bufs = INITIALIZE_BUFFS,
	.debufs = INITIALIZE_DEBUFFS,
	.concentration = INITIALIZE_CONCENTRATION,
	.d_resistance = SHIELD_SPELL_A_DEFAULT_RESISTANCE,
	.c_resistance = INITIALIZE_CURRENT_RESISTANCE,
	.equipment = SHIELD_SPELL_A_EQUIPMENT,
	.skill_mod = SHIELD_SPELL_A_SKILL_MODS,
	.save_mod = SHIELD_SPELL_A_SAVE_MODS,
	.stats = INITIALIZE_STATS,
	.dstats = SHIELD_SPELL_A_DEFAULT_STATS,
	.feats = INITIALIZE_FEATS,
	.struct_name = ft_nullptr,
	.physical = SHIELD_SPELL_A_PHYSICAL,
};

template <int Amount, int Faces>
struct ValidateHitDice
{
    static_assert
	(
        ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
        (Amount <= 40 && Faces <= 12),
        "Invalid SHIELD_SPELL_A_HIT_DICE values: Either both must be 0 or both at least 1, " \
			"and the dice amount must not exceed 40, the dice faces must not exceed 12."
    );
};

inline ValidateHitDice<SHIELD_SPELL_A_HIT_DICE.dice_amount,
	   					SHIELD_SPELL_A_HIT_DICE.dice_faces> validation_instance;

#endif
