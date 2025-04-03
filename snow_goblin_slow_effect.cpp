#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "identification.hpp"

void ft_snow_goblin_attack_effects(t_char *info, t_equipment_id *weapon, int is_crit)
{
	(void)info;
	if (weapon->action_01.effect_type == ETYPE_SNOWBALL_WAND_SLOW)
	{
		if (is_crit)
			pf_printf("The target is slowed down by %i feet\n", weapon->action_01.bonus_mod * 2);
		else
			pf_printf("The target is slowed down by %i feet\n", weapon->action_01.bonus_mod);
	}
	return ;
}
