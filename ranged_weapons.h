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
	.skill_mod = INITIALIZE_SKILLSM,
	.resistance = INITIALIZE_RESISTANCE,
	.flat_dr = INITIALIZE_RESISTANCE,
	.skill_advantage = INITIALIZE_SKILLSM,
	.save = INITIALIZE_SAVES,
	.save_advantage = INITIALIZE_SAVES,
	.type = WTYPE_SHORTBOW,
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
};

static const t_equipment_id CHAOS_WAND =
{
	.name = "chaos wand",
	.projectile_name = "chaos bolt",
	.equipment_id = CHAOS_WAND_ID,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = {
		.function = ft_weapon_attack,
		.damage_type = DAMAGE_TYPE_NECROTIC,
		.stat = STAT_INT,
		.effect_type = 0,
		.effect_dice_amount = 2,
		.effect_dice_faces = 4,
		.bonus_mod = 0,
	},
	.skill_mod = INITIALIZE_SKILLSM,
	.resistance = INITIALIZE_RESISTANCE,
	.flat_dr = INITIALIZE_RESISTANCE,
	.type = WTYPE_WAND,
	.dex_ac_max_bonus = 0,
	.ac = 0,
	.str = 0,
	.dex = 0,
	.con = 0,
	.wis = 0,
	.cha = 0,
	.initiative = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
};

#endif
