#ifndef SNOW_GOBLIN_HPP
# define SNOW_GOBLIN_HPP

#include "dnd_tools.hpp"
#include "identification.hpp"
#include "ranged_weapons.hpp"
#include "melee_weapons.hpp"
#include "armor.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "initialize.hpp"

typedef struct    s_name t_name;
typedef struct    s_char t_char;

void    ft_snow_goblin_turn(t_char * info);
void    ft_snow_goblin_loot(t_char * info);

static const    t_stats SNOW_GOBLIN_DEFAULT_STATS =
{
    .phase = 0,
    .turn = 1,
    .health = 25,
    .temp_hp = 0,
    .str = 14,
    .dex = 16,
    .con = 14,
    .inte = 10,
    .wis = 10,
    .cha = 8,
};

static const    t_save SNOW_GOBLIN_SAVE_MODS =
{
    .str = 1,
    .dex = 3,
    .inte = 0,
    .wis = 0, 
    .cha = 0,
    .con = 0,
};

static const    t_skills SNOW_GOBLIN_SKILL_MODS =
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

static const    t_attack SNOW_GOBLIN_ATTACK =
{
    .attack_bonus = 1,
    .ranged_bonus = 1,
};


static const    t_crit_mod SNOW_GOBLIN_CRIT =
{
    .attack = 0,
    .attack_d = 0,
    .save = 0,
    .skill = 0,
    .attack_fail = 0,
    .save_fail = 0,
    .skill_fail = 0,
};

static const    t_resistance SNOW_GOBLIN_DEFAULT_RESISTANCE =
{
    .acid = 0,
    .bludgeoning = 0,
    .cold = 50,
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

static const t_equipment_id ICY_BLADE =
{
    .name = "icy blade",
    .projectile_name = ft_nullptr,
    .equipment_id = ICY_BLADE_ID,
    .action_01 =
    {
        .function = ft_snow_goblin_attack_effects,
        .damage_type = DAMAGE_TYPE_COLD,
        .stat = ft_nullptr,
        .effect_type = ETYPE_SNOWBALL_WAND_SLOW,
        .effect_dice_amount = 0,
        .effect_dice_faces = 0,
        .effect_secund_dice_amount = 0,
        .effect_secund_dice_faces = 0,
        .bonus_mod = 10,
    },
    .action_02 = INITIALIZE_EQUIPMENT_EFFECT,
    .attack =
    {
        .function = ft_weapon_attack,
        .damage_type = DAMAGE_TYPE_COLD,
        .stat = FINESSE,
        .effect_type = NONE,
        .effect_dice_amount = 1,
        .effect_dice_faces = 6,
        .effect_secund_dice_amount = 1,
        .effect_secund_dice_faces = 6,
        .bonus_mod = 0,
    },
    .skill_mod = INITIALIZE_SKILLS,
    .resistance = INITIALIZE_RESISTANCE,
    .flat_dr = INITIALIZE_RESISTANCE,
    .skill_advantage = INITIALIZE_SKILLS,
    .save = INITIALIZE_SAVES,
    .save_advantage = INITIALIZE_SAVES,
    .crit_attack_fail_bonus = 0,
    .crit_attack_succes_bonus = 0,
    .type = WTYPE_CLAW,
    .dex_ac_max_bonus = 0,
    .ac = 0,
    .str = 0,
    .dex = 0,
    .con = 0,
    .inte = 0,
    .wis = 0,
    .cha = 0,
    .initiative = 0,
    .effect_id = 0,
    .effect_type = 0,
    .effect_dice_amount = 0,
    .effect_dice_faces = 0,
    .bonus_mod = 0,
    .slot = SLOT_WEAPON,
};

static const    t_equipment SNOW_GOBLIN_EQUIPMENT =
{
    .weapon = ICY_BLADE,
    .offhand_weapon = WOODEN_SHIELD,
    .ranged_weapon = INITIALIZE_EQUIPMENT_ID,
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

static const t_physical SNOW_GOBLIN_PHYSICAL =
{
    .height = 0,
    .weight = 0,
    .age = 10,
    .speed = 30,
};

static const t_spell_slot SNOW_GOBLIN_SPELL_SLOT =
{
    .available = 0,
    .total = 0,
    .level = 0,
    .replenishing_slot = 0,
};

static const t_spell_slots SNOW_GOBLIN_SPELL_SLOTS =
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

static const t_inventory SNOW_GOBLIN_INVENTORY
{
    .gold = 0,
};

constexpr t_hit_dice SNOW_GOBLIN_HIT_DICE =
{
    .dice_amount = 0,
    .dice_faces = 0,
};

static const t_char SNOW_GOBLIN_INFO =
{
    .level = 0,
    .mechanical = 0,
    .passive_perception = 15,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_snow_goblin_turn,
    .drop_loot = ft_snow_goblin_loot,
    .loot = INITIALIZE_LOOT,
    .hit_dice = SNOW_GOBLIN_HIT_DICE,
    .inventory = SNOW_GOBLIN_INVENTORY,
    .spells = INITIALIZE_SPELLS,
    .spell_slots = SNOW_GOBLIN_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = SNOW_GOBLIN_CRIT,
    .attack_bonus = SNOW_GOBLIN_ATTACK,
    .bufs = INITIALIZE_BUFFS,
    .debufs = INITIALIZE_DEBUFFS,
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = SNOW_GOBLIN_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = SNOW_GOBLIN_EQUIPMENT,
    .skill_mod = SNOW_GOBLIN_SKILL_MODS,
    .save_mod = SNOW_GOBLIN_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = SNOW_GOBLIN_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = SNOW_GOBLIN_PHYSICAL,
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

inline ValidateHitDice<SNOW_GOBLIN_HIT_DICE.dice_amount, SNOW_GOBLIN_HIT_DICE.dice_faces> validation_instance;

#endif
