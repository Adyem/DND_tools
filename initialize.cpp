#include "dnd_tools.hpp"
#include "libft/CPP_class/nullptr.hpp"

void ft_initialize_variables(t_target_data *target_data)
{
	int index = 0;

	target_data->buff_info = ft_nullptr;
	while (index < 20)
	{
		target_data->Pchar_name[index] = ft_nullptr;
		index++;
	}
	return ;
}
