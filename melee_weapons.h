#ifndef MELEE_WEAPONS_H
# define MELEE_WEAPONS_H

#include <stddef.h>
#include "character.h"
#include "identification.h"
#include "initialize.h"

void	ft_weapon_attack(t_char *info, t_equipment_id *weapon);

static const t_equipment_id STEEL_SWORD =
{
	.equipment_id = STEEL_SWORD_ID,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = {
		.function = ft_weapon_attack,
		.damage_type = DAMAGE_TYPE_SLASHING,
		.stat = STAT_DEX,
		.ac = 0,
		.effect_type = 0,
		.effect_dice_amount = 0,
		.effect_dice_faces = 0,
		.bonus_mod = 0,
	},
	.ac = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
};

#endif
