#ifndef DORGAR_STONEGUARD_HPP
# define DORGAR_STONEGUARD_HPP

#include "libft/CPP_class/class_nullptr.hpp"
#include "ranged_weapons.hpp"
#include "melee_weapons.hpp"
#include "character.hpp"
#include "initialize.hpp"

typedef struct  s_name t_name;
typedef struct  s_char t_char;

void    ft_dorgar_stoneguard_turn(t_char * info);

static const    t_stats DORGAR_STONEGUARD_DEFAULT_STATS =
{
    .phase = 0,
    .turn = 0,
    .health = 20,
    .temp_hp = 0,
    .str = 14,
    .dex = 10,
    .con = 14,
    .inte = 12,
    .wis = 10,
    .cha = 8,
};

static const    t_save DORGAR_STONEGUARD_SAVE_MODS =
{
    .str = 2,
    .dex = 0,
    .inte = 1,
    .wis = 0, 
    .cha = 0,
    .con = 2,
};

static const    t_skills DORGAR_STONEGUARD_SKILL_MODS =
{
    .athletics = 3,
    .acrobatics = 0,
    .sleight_of_hand = 0,
    .stealth = 0,
    .arcana = 1,
    .history = 1,
    .investigation = 1,
    .nature = 1,
    .religion = 0,
    .animal_handling = 0,
    .insight = 0,
    .medicine = 0,
    .perception = 2,
    .survival = 2,
    .deception = 0,
    .intimidation = 0,
    .performance = 0,
    .persuasion = 0,
};

static const    t_attack DORGAR_STONEGUARD_ATTACK =
{
    .attack_bonus = 2,
    .ranged_bonus = 0,
};

static const    t_crit_mod DORGAR_STONEGUARD_CRIT =
{
    .attack = 0,
    .attack_d = 0,
    .save = 0,
    .skill = 0,
    .attack_fail = 0,
    .save_fail = 0,
    .skill_fail = 0,
};

static const    t_resistance DORGAR_STONEGUARD_DEFAULT_RESISTANCE =
{
    .acid = 0,
    .bludgeoning = 0,
    .cold = 0,
    .fire = 0,
    .force = 0,
    .lightning = 0,
    .necrotic = 0,
    .piercing = 0,
    .poison = 20,
    .psychic = 0,
    .radiant = 0,
    .slashing = 0,
    .thunder = 0,
};

static const    t_equipment DORGAR_STONEGUARD_EQUIPMENT =
{
    .weapon = STEEL_BATTLE_AXE,
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

static const    t_physical DORGAR_STONEGUARD_PHYSICAL =
{
    .height = 48,
    .weight = 150,
    .age = 100,
    .speed = 25,
};

static const    t_char DORGAR_STONEGUARD_INFO =
{
    .level = 0,
    .mechanical = 0,
    .passive_perception = 12,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_dorgar_stoneguard_turn,
    .drop_loot = ft_nullptr,
    .loot = INITIALIZE_LOOT,
    .hit_dice = INITIALIZ_HIT_DICE,
    .inventory = INITIALIZE_INVENTORY,
    .spells = INITIALIZE_SPELLS,
    .spell_slots = INITIALIZE_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = DORGAR_STONEGUARD_CRIT,
    .attack_bonus = DORGAR_STONEGUARD_ATTACK,
    .bufs = ft_initialize_buffs(),
    .debufs = ft_initialize_debuffs(),
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = DORGAR_STONEGUARD_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = DORGAR_STONEGUARD_EQUIPMENT,
    .skill_mod = DORGAR_STONEGUARD_SKILL_MODS,
    .save_mod = DORGAR_STONEGUARD_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = DORGAR_STONEGUARD_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = DORGAR_STONEGUARD_PHYSICAL,
    .position = INITIALIZE_POSITION,
};

#endif
