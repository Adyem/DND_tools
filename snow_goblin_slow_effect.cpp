#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void ft_snow_goblin_attack_effects(t_char *info, t_equipment_id *weapon, int is_crit)
{
    (void)info;
    (void)weapon;
	if (is_crit)
        pf_printf("The target is slowed down by 20 feet\n");
	else
        pf_printf("The target is slowed down by 10 feet\n");
	return ;
}
