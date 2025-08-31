#ifndef MAVERICK_HPP
# define MAVERICK_HPP

# include "melee_weapons.hpp"
# include "libft/CPP_class/nullptr.hpp"
# include "character.hpp"
# include "initialize.hpp"
# include <stddef.h>

typedef struct    s_name t_name;
typedef struct    s_char t_char;

void    ft_maverick_turn(t_char * info);

static const    t_stats MAVERICK_DEFAULT_STATS =
{
    .phase = 0,
    .turn = 1,
    .health = 350,
    .temp_hp = 0,
    .str = 16,
    .dex = 18,
    .con = 10,
    .inte = 10,
    .wis = 10,
    .cha = 8,
};

static const    t_save MAVERICK_SAVE_MODS =
{
    .str = 3,
    .dex = 3,
    .inte = 0,
    .wis = 0, 
    .cha = 0,
    .con = 0,
};

static const    t_skills MAVERICK_SKILL_MODS =
{
    .athletics = 2,
    .acrobatics = 2,
    .sleight_of_hand = 0,
    .stealth = 7,
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

static const    t_attack MAVERICK_ATTACK =
{
    .attack_bonus = 0,
    .ranged_bonus = 0,
};


static const    t_crit_mod MAVERICK_CRIT =
{
    .attack = 0,
    .attack_d = 0,
    .save = 0,
    .skill = 0,
    .attack_fail = 0,
    .save_fail = 0,
    .skill_fail = 0,
};

static const    t_resistance MAVERICK_DEFAULT_RESISTANCE =
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


static const    t_equipment MAVERICK_EQUIPMENT =
{
    .weapon = CLAW,
    .offhand_weapon = CLAW_OH,
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

static const t_physical MAVERICK_PHYSICAL =
{
    .height = 0,
    .weight = 0,
    .age = 0,
    .speed = 35,
};

static const t_char MAVERICK_INFO =
{
    .level = 0,
    .mechanical = 0,
    .passive_perception = 20,
    .initiative = -1,
    .version_number = 2,
    .save_file = ft_nullptr,
    .name = ft_nullptr,
    .turn = ft_maverick_turn,
    .drop_loot = ft_nullptr,
    .loot = INITIALIZE_LOOT,
    .hit_dice = INITIALIZ_HIT_DICE,
    .inventory = INITIALIZE_INVENTORY,
    .spells = INITIALIZE_SPELLS,
    .spell_slots = INITIALIZE_SPELL_SLOTS,
    .flags = INITIALIZE_FLAGS,
    .crit = MAVERICK_CRIT,
    .attack_bonus = MAVERICK_ATTACK,
    .bufs = INITIALIZE_BUFFS,
    .debufs = INITIALIZE_DEBUFFS,
    .concentration = INITIALIZE_CONCENTRATION,
    .d_resistance = MAVERICK_DEFAULT_RESISTANCE,
    .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
    .equipment = MAVERICK_EQUIPMENT,
    .skill_mod = MAVERICK_SKILL_MODS,
    .save_mod = MAVERICK_SAVE_MODS,
    .stats = INITIALIZE_STATS,
    .dstats = MAVERICK_DEFAULT_STATS,
    .feats = INITIALIZE_FEATS,
    .struct_name = ft_nullptr,
    .physical = MAVERICK_PHYSICAL,
    .position = INITIALIZE_POSITION,
};

#define MAVERICK_MASS_TELEPORT "Mass Teleport: Teleport all players to random locations"\
    " across the arena depending on what ability it is paired with"
#define MAVERICK_METEOR_STRIKE "Meteor Strike: Create a circle around the target with arrows"\
    " pointing towards the center (10ft.radius), at the start of the next turn a meteor hits"\
    " the target dealing damage dependent on the number of targets hit."\
    " (Cannot be the same target as Arcane Pounce or Earth Pounce)\n"\
    "1 target         22 fire damage\n"\
    "2 targets        9 fire damage each\n"\
    "3 targets        5 fire damage each\n"\
    "4 or more targets    3 fire damage each"
#define MAVERICK_LIGHTNING_STRIKE "Lightning Strike: the bosses skin will flare with"\
    " electricity at the start of the boss his next turn will deal 12 lightning damage"\
    " to anyone within 20 ft. "
#define MAVERICK_FLAME_GEYSER "Flame Geyser: 2 red towers spawn at random locations, if no one"\
    " stood underneath a tower at the start of the boss his next turn it will explode,"\
    " dealing 6 fire damage to every member in the party, if one or more players stood"\
    " underneath a tower it deals 2 fire damage to each of those players."\
    " (be careful with placement on the flame geyser’s so they don’t appear in areas were"\
    " other abilities are going to hit)"
#define MAVERICK_FORST_BREATH "Frost Breath: the boss takes a deep breath, at the start of"\
    " the boss his next turn breathes out dealing 12 cold damage to anyone in a 90 degree"\
    " cone in front of him.  (Be clear about what way the boss is facing when he starts"\
    " casting the ability)"
#define MAVERICK_LIGHTNING_STRIKE_V2 "Lightning Strike V2: A marker appears at a random"\
    " location, it looks like lightning is going to strike there. At the start of"\
    " the boss his next turn it deals 12 lightning damage to everyone, this damage"\
    " is reduced by 2 for each 5ft. of distance from the marker up to a minimum of"\
    " 4. (Be careful with placement on Lightning Strike V2 so it isn’t on top of"\
    " flame geyser)"
#define MAVERICK_ARCANE_POUNCE "Arcane Pounce: Targets a random player, at the start of"\
    " the boss his next turn leap to that player landing in front of them and pounce"\
    " them dealing 4 magic damage and 8 magic damage to anyone within 5ft. (Cannot be"\
    " the same target as Meteor Strike or Earth Pounce)"
#define MAVERICK_EARTH_POUNCE "Earth Pounce: Targets the player with the highest Armor, At the"\
    " start of the boss his next turn he jumps towards the target and deals 24 bludgeoning"\
    " damage reduced by 1 for each AC the target has (Cannot be the same target as Meteor"\
    " Strike or Arcane Pounce)"

#define MAVERICK_MTP_METEOR_STRIKE "Meteor Strike: Teleports all players spreading them"\
    " 30-60ft. away from one another"
#define MAVERICK_MTP_LIGHTNING_STRIKE "Lightning Strike: Teleports the players close to the"\
    " boss"
#define MAVERICK_MTP_FROST_BREATH "Frost Breath: Teleports all players in front of the boss"
#define MAVERICK_MTP_FLAME_GEYSER "Flame Geyser: Teleports the players to random locations"\
    " 30-60ft. away from the flame geyser’s"
#define MAVERICK_MTP_LIGHTNING_STRIKE_V2 "Lightning Strike V2: Teleports all players to"\
    "the marker"
#define MAVERICK_MTP_ARCANE_POUNCE "Arcane Pounce: Teleports all players to around the target"
#define MAVERICK_MTP_EARTH_POUNCE "Earth Pounce: Teleports all players to around the target"

#endif
