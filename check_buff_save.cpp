#include "dnd_tools.hpp"

int	ft_save_check_buff(t_char *info, int *roll, const char *ability_score)
{
	int	return_value;

	return_value = 0;
	return_value += ft_check_bless(info);
	if (info->feats.mighty_resilience.active &&
	    (ft_strcmp_dnd(ability_score, "strength") == 0 ||
	     ft_strcmp_dnd(ability_score, "constitution") == 0))
	        info->flags.advantage++;
	ft_reroll(info, roll);
	return (return_value);
}
