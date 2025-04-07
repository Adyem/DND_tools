#include "character.hpp"
#include "dnd_tools.hpp"

void	ft_attack_additional_effects(t_char *info, t_equipment_id *weapon, bool is_hit, int is_crit,
								int offhand)
{
	(void)offhand;
	if (weapon->action_01.function)
		weapon->action_01.function(info, weapon, &weapon->action_01, is_crit, is_hit);
	return ;
}
