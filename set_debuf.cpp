#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void ft_set_debuf_blinded(t_char * info, const char **input)
{
    int result;

    result = ft_check_stat(info, input[2], 0);
    if (result < 0 || result > 50)
    {
        pf_printf_fd(2, "230-Error blinded value out of bounds or not found\n");
        return ;
    }
    info->debufs.blinded.duration = result;
    print_blinded(info);
    return ;
}

void ft_set_debuf_faerie_fire(t_char * info, const char **input)
{
    int result;

    result = ft_check_stat(info, input[2], 0);
    if (result < 0 || result > 50)
    {
        pf_printf_fd(2, "231-Error faerie fire value out of bounds or not found\n");
        return ;
    }
    info->debufs.faerie_fire.duration = result;
    print_faerie_fire(info);
    return ;
}

void ft_set_buff_sanctuary(t_char * info, const char **input)
{
    int duration;
    int save_dc;

    duration = ft_check_stat(info, input[2], 0);
    if (duration < 0 || duration > 50)
    {
        pf_printf_fd(2, "232-Error sanctuary duration out of bounds or not found\n");
        return ;
    }
    if (input[3])
    {
        save_dc = ft_check_stat(info, input[3], 0);
        if (save_dc < 0 || save_dc > 30)
        {
            pf_printf_fd(2, "233-Error sanctuary save dc out of bounds or not found\n");
            return ;
        }
        info->bufs.sanctuary.save_dc = save_dc;
    }
    info->bufs.sanctuary.duration = duration;
    print_sanctuary(info);
    return ;
}
