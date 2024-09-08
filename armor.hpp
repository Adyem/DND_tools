#ifndef ARMOR_H
# define ARMOR_H

#include <stddef.h>
#include "character.hpp"
#include "identification.hpp"
#include "initialize.hpp"

static const t_equipment_id LEATHER_ARMOR =
{
	.name = "leather armor",
	.projectile_name = nullptr,
	.equipment_id = LEATHER_ARMOR_ID,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = INITIALIZE_EQUIPMENT_ACTION,
	.skill_mod = INITIALIZE_SKILLSM,
	.resistance = INITIALIZE_RESISTANCE,
	.flat_dr = INITIALIZE_RESISTANCE,
	.skill_advantage = INITIALIZE_SKILLSM,
	.save = INITIALIZE_SAVES,
	.save_advantage = INITIALIZE_SAVES,
	.type = ATYPE_LEATHER,
	.dex_ac_max_bonus = 2,
	.ac = 2,
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
};

#endif
