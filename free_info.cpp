#include "dnd_tools.hpp"
#include <cstdlib>
#include <iostream>

void	ft_free_info(t_char *info)
{
	if (info && DEBUG == 1)
		std::cout << "freeing info " << info->name << std::endl;
	if (info && info->version_number >= 2)
	{
		ft_free_double_char(info->debufs.hunters_mark.caster_name);
		ft_free_double_char(info->concentration.targets);
		free(info->save_file);
	}
	free(info);
	return ;
}