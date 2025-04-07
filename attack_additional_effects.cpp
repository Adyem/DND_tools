#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"

void	ft_attack_additional_effects(t_char *info, t_equipment_id *weapon, bool is_hit, int is_crit,
								int offhand)
{
	(void)offhand;
	(void)is_crit;
	if (is_hit && weapon->action_01.function
			&& (weapon->action_01.effect_type == ETYPE_FEL_POISON
				|| weapon->action_01.effect_type == ETYPE_SNOWBALL_WAND_SLOW))
		weapon->action_01.function(info, weapon, &weapon->action_01, is_crit, is_hit);
	else if (weapon->action_01.effect_type == ETYPE_ANCIENT_PREDATORY_BEAST_MULTI_ATTACK
			&& weapon->action_01.function)
		weapon->action_01.function(info, weapon, &weapon->action_01, is_crit, is_hit);
	return ;
}
