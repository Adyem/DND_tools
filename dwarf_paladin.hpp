#ifndef DWARF_PALADIN_HPP
# define DWARF_PALADIN_HPP

#include "ranged_weapons.hpp"
#include "melee_weapons.hpp"
#include "armor.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "character.hpp"
#include "initialize.hpp"

typedef struct    s_name t_name;
typedef struct    s_char t_char;

void    ft_dwarf_paladin_turn(t_char * info);

static const    t_stats DWARF_PALADIN_DEFAULT_STATS =
{
    .phase = 0,
    .turn = 1,
    .health = 90,
    .temp_hp = 0,
    .str = 16,
    .dex = 14,
    .con = 14,
    .inte = 10,
    .wis = 10,
    .cha = 14,
};

static const    t_save DWARF_PALADIN_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
    .inte = 0,
    .wis = 0, 
    .cha = 0,
    .con = 0,
};

static const    t_skills DWARF_PALADIN_SKILL_MODS =
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

static const    t_attack DWARF_PALADIN_ATTACK =
{
    .attack_bonus = 0,
    .ranged_bonus = 0,
};


static const    t_crit_mod DWARF_PALADIN_CRIT =
{
    .attack = 0,
    .attack_d = 0,
    .save = 0,
    .skill = 0,
    .attack_fail = 0,
    .save_fail = 0,
    .skill_fail = 0,
};

static const    t_resistance DWARF_PALADIN_DEFAULT_RESISTANCE =
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

static const    t_equipment DWARF_PALADIN_EQUIPMENT =
{
    .weapon = STEEL_SWORD,
    .offhand_weapon = INITIALIZE_EQUIPMENT_ID,
    .ranged_weapon = WOODEN_BOW,
    .armor = STEEL_ARMOR,
    .helmet = INITIALIZE_EQUIPMENT_ID,
    .shield = INITIALIZE_EQUIPMENT_ID,
    .boots = INITIALIZE_EQUIPMENT_ID,
    .gloves = INITIALIZE_EQUIPMENT_ID,
    .amulet = INITIALIZE_EQUIPMENT_ID,
    .ring_01 = INITIALIZE_EQUIPMENT_ID,
    .ring_02 = INITIALIZE_EQUIPMENT_ID,
    .belt = INITIALIZE_EQUIPMENT_ID,
};

static const t_physical DWARF_PALADIN_PHYSICAL =
{
    .height = 48,
    .weight = 150,
    .age = 50,
    .speed = 25,
};

static const t_spell_slot DWARF_PALADION_FIRST_LEVEL_SLOT =
{
    .available = 4,
    .total = 4,
    .level = 0,
    .replenishing_slot = 0,
};

static const t_spell_slot DWARF_PALADION_SECOND_LEVEL_SLOT =
{
    .available = 1,
    .total = 1,
    .level = 0,
    .replenishing_slot = 0,
};

static const t_spell_slots DWARF_PALADIN_SPELL_SLOTS =
{
    .level_1 = DWARF_PALADION_FIRST_LEVEL_SLOT,
    .level_2 = DWARF_PALADION_SECOND_LEVEL_SLOT,
    .level_3 = INITIALIZE_SPELL_SLOT,
    .level_4 = INITIALIZE_SPELL_SLOT,
    .level_5 = INITIALIZE_SPELL_SLOT,
    .level_6 = INITIALIZE_SPELL_SLOT,
    .level_7 = INITIALIZE_SPELL_SLOT,
    .level_8 = INITIALIZE_SPELL_SLOT,
    .level_9 = INITIALIZE_SPELL_SLOT,
    .warlock = INITIALIZE_SPELL_SLOT,
};

static const t_spell_divine_smite DWARF_PALADIN_SPELL_DIVINE_SMITE =
{
    .learned = 1,
    .base_level = 1,
    .casting_at_level = 0,
    .dice_amount = 2,
    .dice_faces = 8,
    .extra_damage = 0,
    .upcast_extra_dice_face = 0,
    .upcast_extra_dice_amount = 1,
    .upcast_extra_damage = 0,
};

static const t_spell_cure_wounds DWARF_PALADIN_SPELL_CURE_WOUNDS =
{
    .learned = 1,
    .base_level = 1,
    .casting_at_level = 0,
    .dice_amount = 1,
    .dice_faces = 8,
    .extra_healing = 2,
    .upcast_extra_dice_face = 8,
    .upcast_extra_dice_amount = 1,
    .upcast_extra_healing = 0,
};

static const t_spell_bless DWARF_PALADIN_SPELL_BLESS =
{
    .learned = 1,
    .base_level = 1,
    .casting_at_level = 0,
    .duration = 60,
    .target_amount = 3,
    .dice_faces = 4,
    .dice_amount = 1,
    .upcast_extra_targets = 1,
    .upcast_extra_duration = 10,
    .upcast_extra_dice_faces = 0,
    .upcast_extra_dice_amount = 0,
};

static const t_char DWARF_PALADIN_INFO =
{
    .level = 0,
    .mechanical = 0,
    .passive_perception = 15,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_dwarf_paladin_turn,
    .drop_loot = ft_nullptr,
    .loot = INITIALIZE_LOOT,
    .hit_dice = INITIALIZ_HIT_DICE,
    .inventory = INITIALIZE_INVENTORY,
    .spells = INITIALIZE_SPELLS,
    .spell_slots = DWARF_PALADIN_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = DWARF_PALADIN_CRIT,
    .attack_bonus = DWARF_PALADIN_ATTACK,
    .bufs = ft_initialize_buffs(),
    .debufs = ft_initialize_debuffs(),
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = DWARF_PALADIN_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = DWARF_PALADIN_EQUIPMENT,
    .skill_mod = DWARF_PALADIN_SKILL_MODS,
    .save_mod = DWARF_PALADIN_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = DWARF_PALADIN_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = DWARF_PALADIN_PHYSICAL,
    .position = INITIALIZE_POSITION,
};

#endif
