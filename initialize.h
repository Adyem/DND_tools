#ifndef INITIALIZE_H
# define INITIALIZE_H

#include <stddef.h>
#include "character.h"

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
	.save_file = "data/air_totem",
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
