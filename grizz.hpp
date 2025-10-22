#ifndef GRIZZ_HPP
# define GRIZZ_HPP

#include "armor.hpp"
#include "ranged_weapons.hpp"
#include "melee_weapons.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "character.hpp"
#include "initialize.hpp"

typedef struct    s_name t_name;
typedef struct    s_char t_char;

void    ft_grizz_turn(t_char * info);

static const    t_stats GRIZZ_DEFAULT_STATS =
{
    .phase = 0,
    .turn = 1,
    .health = 100,
    .temp_hp = 0,
    .str = 12,
    .dex = 18,
    .con = 10,
    .inte = 10,
    .wis = 10,
    .cha = 8,
};

static const    t_save GRIZZ_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
    .inte = 0,
    .wis = 0, 
    .cha = 0,
    .con = 0,
};

static const    t_skills GRIZZ_SKILL_MODS =
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

static const    t_attack GRIZZ_ATTACK =
{
    .attack_bonus = 0,
    .ranged_bonus = 0,
};


static const    t_crit_mod GRIZZ_CRIT =
{
    .attack = 0,
    .attack_d = 0,
    .save = 0,
    .skill = 0,
    .attack_fail = 0,
    .save_fail = 0,
    .skill_fail = 0,
};

static const    t_resistance GRIZZ_DEFAULT_RESISTANCE =
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


static const    t_equipment GRIZZ_EQUIPMENT =
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

static const t_physical GRIZZ_PHYSICAL =
{
    .height = 0,
    .weight = 0,
    .age = 0,
    .speed = 0,
};

static const t_char GRIZZ_INFO =
{
    .level = 0,
    .mechanical = 0,
    .passive_perception = 15,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_grizz_turn,
    .drop_loot = ft_nullptr,
    .loot = INITIALIZE_LOOT,
    .hit_dice = INITIALIZ_HIT_DICE,
    .inventory = INITIALIZE_INVENTORY,
    .spells = INITIALIZE_SPELLS,
    .spell_slots = INITIALIZE_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = GRIZZ_CRIT,
    .attack_bonus = GRIZZ_ATTACK,
    .bufs = ft_initialize_buffs(),
    .debufs = ft_initialize_debuffs(),
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = GRIZZ_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = GRIZZ_EQUIPMENT,
    .skill_mod = GRIZZ_SKILL_MODS,
    .save_mod = GRIZZ_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = GRIZZ_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = GRIZZ_PHYSICAL,
    .position = INITIALIZE_POSITION,
};

#endif
