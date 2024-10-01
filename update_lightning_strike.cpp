#include "dnd_tools.hpp"
#include <iostream>
#include "libft/Libft/libft.hpp"

void ft_npc_update_lightning_strike(t_char *info, const char **input)
{
	int number;

	if (ft_check_value(input[2]))
	{
		std::cerr << "1-Lightning strike expecting a number between 0 and 1\n";
		return ;
	}
	number = ft_atoi(input[2]);
	if (number >= 0 && number <= 1)
	{
		if (info->bufs.lightning_strike.duration == 0 && number == 0)
			std::cout << info->name << " has lightning markers up at the moment\n";
		else if (info->bufs.lightning_strike.duration == 0 && number > 0)
		{
			if (info->bufs.lightning_strike.amount == 1)
				std::cout << info->name << " made a lightning strike marker appear\n";
			else
				std::cout << info->name << " made " << info->bufs.lightning_strike.amount 
					<< " lightning strike markers appear\n";
		}
		else if (info->bufs.lightning_strike.duration > 0 && number == 0)
			std::cout << info->name << " all lightning strike markers are gone\n";
		else if (info->bufs.lightning_strike.duration > 0 && number > 0)
		{
			std::cout << "old lightning strike markers have disappeared\n";
			if (info->bufs.lightning_strike.amount == 1)
				std::cout << info->name << " has made a lightning strike marker appear";
			else
				std::cout << info->name << " has made " << info->bufs.lightning_strike.amount 
					<< " lightning strike markers appear\n";
		}
		info->bufs.lightning_strike.duration = number;
	}
	else
		std::cerr << "2-Lightning strike expecting a number between 0 and 1";
	
	return ;
}
