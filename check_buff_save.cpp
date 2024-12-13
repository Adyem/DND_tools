#include "dnd_tools.hpp"

int	ft_save_check_buff(SharedPtr<t_char>info, int *roll, const char *ability_score)
{
	(void)ability_score;
	int	return_value;

	return_value = 0;
	return_value += ft_check_bless(info);
	ft_reroll(info, roll);
	return (return_value);
}
