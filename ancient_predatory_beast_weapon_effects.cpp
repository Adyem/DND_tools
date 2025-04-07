#include "character.hpp"
#include "dnd_tools.hpp"
#include "ancient_predatory_beast.hpp"
#include "libft/Printf/printf.hpp"

void ft_ancient_predatory_beast_attack_effects(t_char *info, t_equipment_id *weapon,
			t_equipment_effect *effect, int is_crit, int is_hit)
{
	(void)effect;
	(void)is_crit;
	(void)is_hit;
	(void)weapon;
	if (DEBUG == 1)
		pf_printf("going for a multi attack %s", info->name);
	t_equipment_id multiattack_weapon = ANCIENT_PREDATORY_BEAST_MULTI_1;
	ft_weapon_attack(info, &multiattack_weapon, 0);	
	multiattack_weapon = ANCIENT_PREDATORY_BEAST_MULTI_2;
	ft_weapon_attack(info, &multiattack_weapon, 0);
	return ;
}
