#include "dnd_tools.h"

int	ft_attack_roll_check_buffs(t_char *info, int *roll)
{
	int	return_value;

	return_value = 0;
	return_value += ft_check_bless(info);
	ft_reroll(info, roll);
	return (return_value);
}
