#include "dnd_tools.hpp"

int	ft_attack_roll_check_buffs(SharedPtr<t_char>info, int *roll)
{
	int	return_value;

	return_value = 0;
	return_value += ft_check_bless(info);
	if (info->flags.flanking)
		info->flags.advantage++;
	if (info->debufs.blinded.duration)
		info->flags.advantage--;
	ft_reroll(info, roll);
	return (return_value);
}
