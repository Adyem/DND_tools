#include "character.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

static void ft_free_memory_cmt(t_target_data *target_data, int amount)
{
    int j = 0;

    while (j < amount)
    {
        if (target_data->target[j])
        {
            ft_free_info(target_data->target[j]);
            target_data->target[j] = ft_nullptr;
        }
		if (target_data->target_copy[j])
		{
			ft_free_info(target_data->target_copy[j]);
			target_data->target[j] = ft_nullptr;
		}
        if (target_data->Pchar_name[j])
        {
            cma_free(target_data->Pchar_name[j]);
            target_data->Pchar_name[j] = ft_nullptr;
        }
        if (target_data->fd[j] != -1)
        {
            close(target_data->fd[j]);
            target_data->fd[j] = -1;
        }
        j++;
    }
	return ;
}

static int ft_check_target_amount(int target_amount)
{
    if (target_amount > 20)
    {
        pf_printf("110-Error: too many targets\n");
        return (0);
    }
    return (1);
}

static char *ft_read_target_name(int i)
{
    char	message[55];
    char	*target_name;

    sprintf(message, "Requesting the name of the %s target", ft_ordinal_suffix(i + 1));
    target_name = rl_readline(message);
    if (!target_name)
    {
        pf_printf("108-Error: Failed to allocate memory for readline target\n");
        return (ft_nullptr);
    }
    return (target_name);
}

static t_char *ft_validate_and_fetch_target(char *target_name, t_char *info,
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


static void ft_initialize_variables(t_target_data *target_data)
{
	int i = 0;

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

void ft_cast_concentration_multi_target_01(t_char *info, t_buff *buff, const char **input)
{
    t_target_data	target_data;
    int				error = 0;
    int				targets_collected = 0;
    int				error_code;

    if (ft_remove_concentration(info))
        return ;
    ft_initialize_variables(&target_data);
    if (!ft_check_target_amount(buff->target_amount))
        return ;
    while (targets_collected < buff->target_amount)
    {
        target_data.Pchar_name[targets_collected] = ft_read_target_name(targets_collected);
        if (!target_data.Pchar_name[targets_collected])
        {
            ft_free_memory_cmt(&target_data, targets_collected);
            return ;
        }
        target_data.target[targets_collected] = ft_validate_and_fetch_target
			(target_data.Pchar_name[targets_collected], info, &error_code);
		target_data.target_copy[targets_collected] = ft_validate_and_fetch_target
			(target_data.Pchar_name[targets_collected], info, &error_code);
        if (!target_data.target[targets_collected])
        {
            if (error_code == 0)
            {
                cma_free(target_data.Pchar_name[targets_collected]);
                target_data.Pchar_name[targets_collected] = ft_nullptr;
            }
            else
            {
                cma_free(target_data.Pchar_name[targets_collected]);
                target_data.Pchar_name[targets_collected] = ft_nullptr;
                error++;
                if (error >= MAX_ERROR_COUNT)
                {
                    ft_free_memory_cmt(&target_data, targets_collected);
                    return ;
                }
				continue ;
            }
        }
        targets_collected++;
    }
    buff->target_amount = targets_collected;
    target_data.buff_info = buff;
    ft_cast_concentration_multi_target_02(info, &target_data, input);
    ft_free_memory_cmt(&target_data, buff->target_amount);
    return ;
}
