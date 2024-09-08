#include "dnd_tools.hpp"
#include <iostream>

void ft_set_debuf_blinded(t_char *info, const char **input)
{
	int result;

	result = ft_check_stat(info, input[2], 0);
	if (result < 0 || result > 50)
	{
		std::cerr << "230-Error blinded value out of bounds or not found\n";
		return ;
	}
	info->debufs.blinded.duration = result;
	return ;
}
