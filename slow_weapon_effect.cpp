#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "identification.hpp"

void ft_snow_goblin_attack_effects(t_char *info, t_equipment_id *weapon,
		t_equipment_effect *effect, t_attack_info *attack_info)
{
	(void)effect;
	(void)info;
	if (!attack_info->is_hit)
		return ;
	if (weapon->action_01.effect_type == ETYPE_SNOWBALL_WAND_SLOW)
	{
		if (attack_info->is_crit)
			pf_printf("The target is slowed down by %i feet\n", weapon->action_01.bonus_mod * 2);
		else
			pf_printf("The target is slowed down by %i feet\n", weapon->action_01.bonus_mod);
	}
	return ;
}
