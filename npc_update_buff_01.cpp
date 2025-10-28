#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"

void ft_update_buff_status(t_char * info, int current_dur, int duration,
                            const char *buff_name)
{
    if (duration == 0 && current_dur == 0)
        pf_printf("%s never had %s and still doesn't have it\n", info->name, buff_name);
    else if (duration == 0)
        pf_printf("%s just lost his %s buff\n", info->name, buff_name);
    else if (duration == 1 && current_dur == 0)
        pf_printf("%s just received a %s that lasts for a turn\n", info->name, buff_name);
    else if (duration == 1 && current_dur == 1)
        pf_printf("%s already had a %s that lasts for a turn\n", info->name, buff_name);
    else if (duration > 1 && current_dur == 0)
        pf_printf("%s just received a %s that lasts for %d turns\n", info->name, buff_name, duration);
    else if (duration > 1 && duration > current_dur)
        pf_printf("%s his %s got refreshed to %d turns\n", info->name, buff_name, duration);
    else if (duration > 1 && current_dur > duration)
        pf_printf("%s already had a better %s that lasts for %d turns\n", info->name, buff_name, current_dur);
    else if (duration == current_dur)
        pf_printf("%s already has a %s that is just as good lasting %d turns\n", info->name, buff_name, current_dur);
    return ;
}

void ft_npc_update_buff(t_char * info, const char **input, int *buff, const char *name)
{
    int number;

    if (ft_validate_int(input[2]))
    {
        pf_printf_fd(2, "1-Buff Error: Expecting a number between 0 and 50\n");
        return ;
    }
    number = ft_atoi(input[2]);
    if (number >= 0 && number <= 50)
    {
        ft_update_buff_status(info, *buff, number, name);
        if (number > *buff)
            *buff = number;
        else if (number == 0)
            *buff = number;
        if (buff == &info->bufs.protective_winds.duration && *buff > 0)
            print_protective_winds(info);
    }
    else
        pf_printf_fd(2, "2-Buff Error: Expecting a number between 0 and 50\n");
    return ;
}
