#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"

void	ft_cast_chaos_armor(ft_sharedptr<t_char> &info)
{
	if (ft_remove_concentration(info))
		return ;
	info->concentration.concentration = 1;
	info->concentration.spell_id = CHAOS_ARMOR_ID;
	info->concentration.duration = 3;
	info->concentration.base_mod = 13;
	info->bufs.chaos_armor.duration = 3;
	pf_printf("%s cast chaos armor\n", info->name);
}
