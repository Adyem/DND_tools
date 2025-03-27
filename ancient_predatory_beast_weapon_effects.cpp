#include "character.hpp"
#include "dnd_tools.hpp"
#include "ancient_predatory_beast.hpp"

void ft_ancient_predatory_beast_attack_effects(t_char *info, t_equipment_id *weapon, int is_crit)
{
	(void)is_crit;
	(void)weapon;
	t_equipment_id multiattack_weapon = ANCIENT_PREDATORY_BEAST_MULTI_1;
	ft_weapon_attack(info, &multiattack_weapon, 0);	
	multiattack_weapon = ANCIENT_PREDATORY_BEAST_MULTI_2;
	ft_weapon_attack(info, &multiattack_weapon, 0);
	return ;
}
