#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Libft/libft.hpp"

void    ft_growth_stack(t_char *info, const char **input, int argc)
{
    int amount = 1;
    if (argc == 5)
    {
        if (ft_check_value(input[4]))
        {
            pf_printf_fd(2, "Growth stack expects a number between 1 and 10\n");
            return ;
        }
        amount = ft_atoi(input[4]);
    }
    if (amount < 1 || amount > 10)
    {
        pf_printf_fd(2, "Growth stack expects a number between 1 and 10\n");
        return ;
    }
    if (ft_strcmp_dnd(input[1], "add") == 0)
    {
        info->bufs.growth.stacks += amount;
        if (info->bufs.growth.stacks > 10)
            info->bufs.growth.stacks = 10;
        pf_printf("%s gains %d growth stack(s) (total %d)\n", info->name, amount,
                  info->bufs.growth.stacks);
    }
    else if (ft_strcmp_dnd(input[1], "remove") == 0)
    {
        info->bufs.growth.stacks -= amount;
        if (info->bufs.growth.stacks < 0)
            info->bufs.growth.stacks = 0;
        pf_printf("%s loses %d growth stack(s) (total %d)\n", info->name, amount,
                  info->bufs.growth.stacks);
    }
    else
        pf_printf_fd(2, "Growth stack invalid command\n");
}
