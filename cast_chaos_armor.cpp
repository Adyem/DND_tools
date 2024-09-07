#include "dnd_tools.hpp"
#include "identification.hpp"
#include <iostream>

void	ft_cast_chaos_armor(t_char *info)
{
	ft_remove_concentration(info);
	info->concentration.concentration = 1;
	info->concentration.spell_id = CHAOS_ARMOR_ID;
	info->concentration.duration = 3;
	info->concentration.base_mod = 13;
	info->bufs.chaos_armor.duration = 3;
	std::cout << info->name << " cast chaos armor" << std::endl;
}
