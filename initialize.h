#ifndef INITIALIZE_H
# define INITIALIZE_H

#include <stddef.h>
#include "character.h"

static const t_equipment_action INITIALIZE_EQUIPMENT_ACTION =
{
	.function = NULL,
	.ac = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
};

static const t_equipment_id INITIALIZE_EQUIPMENT_ID =
{
	.equipment_id = 0,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = INITIALIZE_EQUIPMENT_ACTION,
	.ac = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
};

static const	t_stats INITIALIZE_STATS =
{
	.phase = -1,
	.turn = -1,
	.health = -1,
	.temp_hp = -1,
	.ac = -1,
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
	.targets = NULL,
};


static const	t_bless INITIALIZE_BLESS =
{
	.duration = 0,
	.dice_amount_mod = 1,
	.dice_faces_mod = 4,
	.base_mod = 0,
	.target = NULL,
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
	.save_file = NULL,
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
	.caster_name = NULL,
};

static const	t_debufs INITIALIZE_DEBUFFS =
{
	.hunters_mark = INITIALIZE_HUNTERS_MARK,
};


#endif
