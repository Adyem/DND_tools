#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void	ft_shadow_claw_effect(t_char *info, t_equipment_id *weapon,
				t_equipment_effect *effect, t_attack_info *attack_info)
{
	(void)weapon;
	(void)info;
	if (attack_info->is_hit)
	{
		pf_printf("the targets armor class is reduced by %i for each stack of shadow touched" \
				"they have for the next %i turns, additional applications do not reset the " \
				"duration\n", effect->bonus_mod, effect->effect_dice_faces);
	}
	return ;
}
