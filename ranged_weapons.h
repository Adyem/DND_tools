#ifndef RANGED_WEAPONS_H
# define RANGED_WEAPONS_H

#include <stddef.h>
#include "character.h"
#include "identification.h"

void	ft_wooden_bow_attack(t_char *info);

static const	t_equipment_id WOODEN_BOW =
{
	.equipment_id = WOODEN_BOW_ID,
	.action_01 = ft_wooden_bow_attack,
	.action_02 = NULL,
	.ac = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
};

#endif
