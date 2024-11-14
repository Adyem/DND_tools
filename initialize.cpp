#include "dnd_tools.hpp"
#include "libft/CPP_class/nullptr.hpp"

void ft_initialize_variables(t_target_data *target_data)
{
	int i = 0;

	target_data->buff_info = ft_nullptr;
	while (i < 20)
	{
		target_data->Pchar_name[i] = ft_nullptr;
		target_data->fd[i] = -1;
		target_data->target[i] = ft_nullptr;
		target_data->target_copy[i] = ft_nullptr;
		i++;
	}
	return ;
}
