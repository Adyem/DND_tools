#include "dnd_tools.hpp"
#include <iostream>
#include "libft/Libft/libft.hpp"

void ft_update_buff_status(t_char *info, int current_dur, int duration, const char *buff_name)
{
	if (duration == 0 && current_dur == 0)
        std::cout << info->name << " never had " << buff_name
			<< " and still doesn't have it" << std::endl;
	else if (duration == 0)
        std::cout << info->name << " just lost his " << buff_name
			<< " buff" << std::endl;
	else if (duration == 1 && current_dur == 0)
        std::cout << info->name << " just received a " << buff_name
			<< " that lasts for a turn" << std::endl;
	else if (duration == 1 && current_dur == 1)
        std::cout << info->name << " already had a " << buff_name
			<< " that lasts for a turn" << std::endl;
	else if (duration > 1 && current_dur == 0)
        std::cout << info->name << " just received a " << buff_name
			<< " that lasts for " << duration << " turns" << std::endl;
	else if (duration > 1 && duration > current_dur)
        std::cout << info->name << " his " << buff_name
			<< " got refreshed to " << duration << " turns" << std::endl;
	else if (duration > 1 && current_dur > duration)
        std::cout << info->name << " already had a better " << buff_name
			<< " that lasts for " << current_dur << " turns" << std::endl;
	else if (duration == current_dur)
        std::cout << info->name << " already has a " << buff_name
			<< " that is just as good lasting " << current_dur << " turns" << std::endl;
	return ;
}

void ft_npc_update_buff(t_char *info, const char **input, int *buff, const char *name)
{
    int number;

    if (ft_check_value(input[2]))
    {
        std::cerr << "1-Buff Error: Expecting a number between 0 and 50" << std::endl;
        return;
    }
    number = ft_atoi(input[2]);
	if (number >= 0 && number <= 50)
	{
        ft_update_buff_status(info, *buff, number, name);
        if (number > *buff)
            *buff = number;
        else if (number == 0)
            *buff = number;
	}
	else
		std::cerr << "2-Buff Error: Expecting a number between 0 and 50" << std::endl;
	return ;
}
