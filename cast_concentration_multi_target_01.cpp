#include "character.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

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
    char message[55];
    char *target_name;

    sprintf(message, "Requesting the name of the %s target", ft_ordinal_suffix(i + 1));
    target_name = rl_readline(message);
    if (!target_name)
    {
        pf_printf("108-Error: Failed to allocate memory for readline target\n");
        return (ft_nullptr);
    }
    return (target_name);
}

static t_char *ft_validate_and_fetch_target(char *target_name, t_char *info)
{
    if (ft_set_stats_check_name(target_name))
    {
        if (ft_check_player_character(target_name))
        {
            pf_printf("111-Error: target does not exist\n");
            return (ft_nullptr);
        }
        return (ft_nullptr);
    }
    else
    {
        t_char *target_info = ft_get_info(target_name, info->struct_name);
        if (!target_info)
        {
            pf_printf("109-Error: getting info for %s\n", target_name);
            return (ft_nullptr);
        }
        return (target_info);
    }
}

static void ft_initialize_variables(t_target_data *target_data)
{
	int i = 0;
	while (i < 20)
	{
		target_data->string[i] = ft_nullptr;
		target_data->fd[i] = -1;
		target_data->target[i] = ft_nullptr;
		i++;
	}
	return ;
}

static int ft_open_target_files(t_target_data *target_data, int amount)
{
    int i;

    for (i = 0; i < amount; i++)
    {
        if (!target_data->target[i] || !target_data->target[i]->save_file)
        {
            pf_printf("112-Error: invalid target or missing save file\n");
            break ;
        }
        target_data->fd[i] = open(target_data->target[i]->save_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (target_data->fd[i] == -1)
        {
            pf_printf("113-Error: opening file %s\n", target_data->target[i]->save_file);
            break ;
        }
    }
    if (i != amount)
    {
        for (int j = 0; j < i; j++)
        {
            close(target_data->fd[j]);
            target_data->fd[j] = -1;
        }
        return (0);
    }
    return (1);
}

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
        if (target_data->string[j])
        {
            cma_free(target_data->string[j]);
            target_data->string[j] = ft_nullptr;
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

void ft_cast_concentration_multi_target_01(t_char *info, const char **input, t_buff *buff)
{
    t_target_data target_data;
    int           i;

    (void)input;
    ft_initialize_variables(&target_data);
    if (!ft_check_target_amount(buff->target_amount))
        return ;
    i = 0;
    while (i < buff->target_amount)
    {
        target_data.string[i] = ft_read_target_name(i);
        if (!target_data.string[i])
        {
            ft_free_memory_cmt(&target_data, i);
            return ;
        }
        target_data.target[i] = ft_validate_and_fetch_target(target_data.string[i], info);
        if (!target_data.target[i])
        {
            cma_free(target_data.string[i]);
            target_data.string[i] = ft_nullptr;
            ft_free_memory_cmt(&target_data, i);
            return ;
        }
        i++;
    }
    if (!ft_open_target_files(&target_data, buff->target_amount))
    {
        ft_free_memory_cmt(&target_data, buff->target_amount);
        return ;
    }
    for (i = 0; i < buff->target_amount; i++)
    {
        ft_npc_write_file(info, &info->stats, &info->c_resistance, target_data.fd[i]);
        close(target_data.fd[i]);
        target_data.fd[i] = -1;
    }
    ft_free_memory_cmt(&target_data, buff->target_amount);
}
