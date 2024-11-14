#include "dnd_tools.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Printf/ft_printf.hpp"

int	ft_check_value(const char *input)
{
	long	check;
	int		i;
	int		sign;

	check = 0;
	i = 0;
	sign = 1;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (!input[i])
		return (1);
	if (input[0] == '-')
		sign = -1;
	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			check = (check * 10) + input[i] - '0';
			if (sign * check < -2147483648 || sign * check > 2147483647)
				return (2);
			i++;
		}
		else
			return (3);
	}
	return (0);
}

int	ft_strcmp_dnd(const char *string1, const char *string2)
{
	if (!string1 || !string2)
		return (-1);
	while (*string1 && (*string1) == (*string2))
	{
		string1++;
		string2++;
	}
	return ((int)(*string1) - (int)(*string2));
}

t_char *ft_validate_and_fetch_target(char *target_name, t_char *info,
		int *error_code)
{
    if (!ft_set_stats_check_name(target_name))
    {
        pf_printf("111-Error: target does not exist\n");
        *error_code = 1;
        return (ft_nullptr);
    }

    if (ft_check_player_character(target_name))
    {
        *error_code = 0;
        return (ft_nullptr);
    }
    t_char *target_info = ft_get_info(target_name, info->struct_name);
    if (!target_info)
    {
        pf_printf("109-Error: getting info for %s\n", target_name);
        *error_code = 2;
        return (ft_nullptr);
    }
    *error_code = 0;
    return (target_info);
}

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
