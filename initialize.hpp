#ifndef INITIALIZE_H
# define INITIALIZE_H

#include <stddef.h>
#include "character.hpp"

static const	t_saves INITIALIZE_SAVES =
{
	.str = 0,
	.dex = 0,
	.con = 0,
	.inte = 0,
	.wis = 0,
	.cha = 0,
};

static const	t_skillsm INITIALIZE_SKILLSM =
{
	.athletics = 0,
	.acrobatics = 0,
	.sleight_of_hand = 0,
	.stealth = 0,
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

static const	t_resistance INITIALIZE_RESISTANCE =
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

static const	t_resistance INITIALIZE_CURRENT_RESISTANCE =
{
	.acid = -501,
	.bludgeoning = -501,
	.cold = -501,
	.fire = -501,
	.force = -501,
	.lightning = -501,
	.necrotic = -501,
	.piercing = -501,
	.poison = -501,
	.psychic = -501,
	.radiant = -501,
	.slashing = -501,
	.thunder = -501,
};

static const t_equipment_action INITIALIZE_EQUIPMENT_ACTION =
{
	.function = nullptr,
	.damage_type = nullptr,
	.stat = nullptr,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.effect_secund_dice_amount = 0,
	.effect_secund_dice_faces = 0,
	.bonus_mod = 0,
};

static const t_equipment_id INITIALIZE_EQUIPMENT_ID =
{
	.name = nullptr,
	.projectile_name = nullptr,
	.equipment_id = 0,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = INITIALIZE_EQUIPMENT_ACTION,
	.skill_mod = INITIALIZE_SKILLSM,
	.resistance = INITIALIZE_RESISTANCE,
	.flat_dr = INITIALIZE_RESISTANCE,
	.skill_advantage = INITIALIZE_SKILLSM,
	.save = INITIALIZE_SAVES,
	.save_advantage = INITIALIZE_SAVES,
	.type = 0,
	.dex_ac_max_bonus = 0,
	.ac = 0,
	.str = 0,
	.dex = 0,
	.con = 0,
	.inte = 0,
	.wis = 0,
	.cha = 0,
	.initiative = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
	.slot = 0,
};

static const	t_stats INITIALIZE_STATS =
{
	.phase = -1,
	.turn = -1,
	.health = -1,
	.temp_hp = -1,
	.str = -1,
	.dex = -1,
	.con = -1,
	.inte = -1,
	.wis = -1,
	.cha = -1,
};

static const	t_concentration INITIALIZE_CONCENTRATION =
{
	.concentration = 0,
	.spell_id = 0,
	.dice_amount_mod = 0,
	.dice_faces_mod = 0,
	.base_mod = 0,
	.duration = 0,
	.targets = nullptr,
};


static const	t_bless INITIALIZE_BLESS =
{
	.duration = 0,
	.dice_amount_mod = 1,
	.dice_faces_mod = 4,
	.base_mod = 0,
	.target = nullptr,
};

static const	t_protective_winds INITIALIZE_PROTECTIVE_WINDS =
{
	.duration = 0,
};

static const	t_lightning_strike INITIALIZE_LIGHTNING_STRIKE =
{
	.duration = 0,
	.amount = 0,
	.distance = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
};

static const	t_air_totem INITIALIZE_AIR_TOTEM =
{
	.save_file = nullptr,
	.health = 0,
	.ac = 0,
	.knock_back_distance = 0,
	.erea_of_effect = 0,
};

static const	t_chaos_armor INITIALIZE_CHAOS_ARMOR =
{
	.duration = 0,
};

static const	t_bufs INITIALIZE_BUFFS =
{
	.bless = INITIALIZE_BLESS,
	.protective_winds = INITIALIZE_PROTECTIVE_WINDS,
	.lightning_strike = INITIALIZE_LIGHTNING_STRIKE,
	.chaos_armor = INITIALIZE_CHAOS_ARMOR,
};

static const	t_hunters_mark INITIALIZE_HUNTERS_MARK =
{
	.amount = 0,
	.caster_name = nullptr,
};

static const	t_blinded INITIALIZE_BLINDED =
{
	.duration = 0,
};

static const	t_debufs INITIALIZE_DEBUFFS =
{
	.hunters_mark = INITIALIZE_HUNTERS_MARK,
	.blinded = INITIALIZE_BLINDED,
};

static const	t_flags INITIALIZE_FLAGS =
{
	.alreaddy_saved = 0,
	.error = 0,
	.flanking = 0,
	.advantage = 0,
	.prone = 0,
};

static const	t_feats INITIALIZE_FEATS =
{
};

#endif
