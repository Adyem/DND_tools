#ifndef MELEE_WEAPONS_H
# define MELEE_WEAPONS_H

#include <stddef.h>
#include "character.h"
#include "identification.h"

void	ft_steel_sword_attack(t_char *info);

static const	t_equipment_id STEEL_SWORD =
{
	.equipment_id = STEEL_SWORD_ID,
	.action_01 = NULL,
	.action_02 = NULL,
	.attack = ft_steel_sword_attack,
	.ac = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
};

#endif
