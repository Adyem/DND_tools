#include "dnd_tools.h"

void ft_check_concentration(t_char *info, int damage)
{
	int	difficulty;
	int	result;

	if (info->version_number < 2 || !info->concentration.concentration)
		return ;
	result = ft_saving_throw(info, "constituion", info->stats.con, info->save_mod.con);
	difficulty = 10;
	if (difficulty < damage / 2)
		difficulty = damage / 2;
	if (result < difficulty)
	{
		ft_printf("%s failed on his/her concentration save\n", info->name);
		info->concentration.concentration = 0;
		info->concentration.spell_id = 0;
		info->concentration.dice_amount_mod = 0;
		info->concentration.dice_faces_mod = 0;
		info->concentration.base_mod = 0;
		info->concentration.targets = NULL;
	}
	else
		ft_printf("%s made his/her concentration save\n", info->name);
	return ;
}
