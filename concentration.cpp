#include "character.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

void ft_check_concentration(SharedPtr<t_char>info, int damage)
{
    int difficulty;
    int result;

    if (DEBUG == 1)
        pf_printf("Rolling con save for concentration %s\n", info->name);
    if (!info->concentration.concentration)
        return ;
    result = ft_saving_throw(info, "constitution", info->stats.con, info->save_mod.con);
    difficulty = 10;
    if (difficulty < damage / 2)
        difficulty = damage / 2;
    if (result < difficulty)
    {
        pf_printf("%s failed his/her concentration save\n", info->name);
        ft_remove_concentration(info);
    }
    else
        pf_printf("%s made his/her concentration save\n", info->name);
    return ;
}
