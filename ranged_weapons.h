#ifndef RANGED_WEAPONS_H
# define RANGED_WEAPONS_H

# include <stddef.h>
# include "character.h"
# include "identification.h"
# include "initialize.h"

void	ft_weapon_attack(t_char *info, t_equipment_id *weapon);

static const t_equipment_id WOODEN_BOW =
{
	.name = "wooden bow",
	.projectile_name = "arrow",
	.equipment_id = WOODEN_BOW_ID,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = {
		.function = ft_weapon_attack,
		.damage_type = DAMAGE_TYPE_PIERCING,
		.stat = STAT_DEX,
		.effect_type = 0,
		.effect_dice_amount = 1,
		.effect_dice_faces = 8,
		.bonus_mod = 0,
	},
	.dex_ac_max_bonus = 0,
	.ac = 0,
	.str = 0,
	.dex = 0,
	.con = 0,
	.inte = 0,
	.wis = 0,
	.cha = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
};

#endif
