#include "dnd_tools.h"

int	ft_save_check_buff(t_char *info, int *roll, const char *ability_score)
{
	(void)ability_score;
	int	return_value;

	return_value = 0;
	return_value += ft_check_bless(info);
	ft_reroll(info, roll);
	return (return_value);
}
