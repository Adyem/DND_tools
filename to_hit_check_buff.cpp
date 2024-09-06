#include "dnd_tools.hpp"
#include "identification.hpp"

static void	ft_to_hit_chaos_armor(t_char *info)
{
	(void)info;
}

void	ft_to_hit_check_buff(t_char *info)
{
	if (info->concentration.spell_id == CHAOS_ARMOR_ID)
		ft_to_hit_chaos_armor(info);
}
