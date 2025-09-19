#include "dnd_tools.hpp"
#include "libft/CPP_class/class_nullptr.hpp"

void ft_initialize_variables(t_target_data *target_data)
{
    target_data->buff_info = ft_nullptr;
    ft_bzero(target_data->Pchar_name, sizeof(target_data->Pchar_name));
    return ;
}
