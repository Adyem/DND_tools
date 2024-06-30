#ifndef RANGED_WEAPONS_H
# define RANGED_WEAPONS_H

#include <stddef.h>
#include "character.h"
#include "identification.h"
#include "initialize.h"

#define WOODEN_BOW_NAME "wooden bow"

void	ft_weapon_attack(t_char *info, t_equipment_id *weapon);

static const t_equipment_id WOODEN_BOW =
{
	.name = WOODEN_BOW_NAME,
	.equipment_id = WOODEN_BOW_ID,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = {
		.function = ft_weapon_attack,
		.damage_type = DAMAGE_TYPE_PIERCING,
		.stat = STAT_DEX,
		.ac = 0,
		.effect_type = 0,
		.effect_dice_amount = 1,
		.effect_dice_faces = 8,
		.bonus_mod = 0,
	},
	.ac = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
};

#endif
