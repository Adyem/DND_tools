#ifndef XAVIUS_HPP
# define XAVIUS_HPP

#include "armor.hpp"
#include "melee_weapons.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "initialize.hpp"
#include "ranged_weapons.hpp"
#include <stddef.h>

typedef struct    s_name t_name;
typedef struct    s_char t_char;

void    ft_xavius_turn(t_char * info);
void    ft_xavius_loot(t_char * info);

static const    t_stats XAVIUS_DEFAULT_STATS =
{
    .phase = 0,
    .turn = 1,
    .health = 250,
    .temp_hp = 0,
    .str = 12,
    .dex = 18,
    .con = 10,
    .inte = 10,
    .wis = 10,
    .cha = 8,
};

static const    t_save XAVIUS_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
    .inte = 0,
    .wis = 0, 
    .cha = 0,
    .con = 0,
};

static const    t_skills XAVIUS_SKILL_MODS =
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

static const    t_attack XAVIUS_ATTACK =
{
    .attack_bonus = 0,
    .ranged_bonus = 0,
};


static const    t_crit_mod XAVIUS_CRIT =
{
    .attack = 0,
    .attack_d = 0,
    .save = 0,
    .skill = 0,
    .attack_fail = 0,
    .save_fail = 0,
    .skill_fail = 0,
};

static const    t_resistance XAVIUS_DEFAULT_RESISTANCE =
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

static const    t_equipment XAVIUS_EQUIPMENT =
{
    .weapon = NIGHTMARE_CLAW,
    .offhand_weapon = INITIALIZE_EQUIPMENT_ID,
    .ranged_weapon = SHADOW_WAND,
    .armor = XAVIUS_MAGE_ARMOR,
    .helmet = INITIALIZE_EQUIPMENT_ID,
    .shield = INITIALIZE_EQUIPMENT_ID,
    .boots = INITIALIZE_EQUIPMENT_ID,
    .gloves = INITIALIZE_EQUIPMENT_ID,
    .amulet = INITIALIZE_EQUIPMENT_ID,
    .ring_01 = INITIALIZE_EQUIPMENT_ID,
    .ring_02 = INITIALIZE_EQUIPMENT_ID,
    .belt = INITIALIZE_EQUIPMENT_ID,
};

static const t_physical XAVIUS_PHYSICAL =
{
    .height = 0,
    .weight = 0,
    .age = 0,
    .speed = 0,
};

static const t_spell_slot XAVIUS_SPELL_SLOT =
{
    .available = 0,
    .total = 0,
    .level = 0,
    .replenishing_slot = 0,
};

static const t_spell_slots XAVIUS_SPELL_SLOTS =
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

static const t_inventory XAVIUS_INVENTORY
{
    .gold = 0,
};

constexpr t_hit_dice XAVIUS_HIT_DICE =
{
    .dice_amount = 0,
    .dice_faces = 0,
};

static const t_char XAVIUS_INFO =
{
    .level = 0,
    .mechanical = 0,
    .passive_perception = 15,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_xavius_turn,
    .drop_loot = ft_xavius_loot,
    .loot = INITIALIZE_LOOT,
    .hit_dice = XAVIUS_HIT_DICE,
    .inventory = XAVIUS_INVENTORY,
    .spells = INITIALIZE_SPELLS,
    .spell_slots = XAVIUS_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = XAVIUS_CRIT,
    .attack_bonus = XAVIUS_ATTACK,
    .bufs = INITIALIZE_BUFFS,
    .debufs = INITIALIZE_DEBUFFS,
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = XAVIUS_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = XAVIUS_EQUIPMENT,
    .skill_mod = XAVIUS_SKILL_MODS,
    .save_mod = XAVIUS_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = XAVIUS_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = XAVIUS_PHYSICAL,
    .position = INITIALIZE_POSITION,
};

template <int Amount, int Faces>
struct ValidateHitDice
{
    static_assert
    (
        ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
        (Amount <= 40 && Faces <= 12),
        "Invalid XAVIUS_HIT_DICE values: Either both must be 0 or both at least 1, " \
            "and the dice amount must not exceed 40, the dice faces must not exceed 12."
    );
};

inline ValidateHitDice<XAVIUS_HIT_DICE.dice_amount,
                           XAVIUS_HIT_DICE.dice_faces> validation_instance;

#endif
