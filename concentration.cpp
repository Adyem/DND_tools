#include "character.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

static void ft_concentration_remove_buf(t_char *info, t_target_data *targets)
{
    if (info->concentration.spell_id == HUNTERS_MARK_ID)
        ft_concentration_remove_hunters_mark(info, targets);
    return ;
}

int ft_remove_concentration(t_char *info)
{
	t_target_data	targets;
    int				i;
	int				error;
	int				fd;

    if (DEBUG == 1)
        pf_printf("Removing concentration\n");
    i = 0;
	targets.buff_info = ft_nullptr;
    while (info->concentration.targets && info->concentration.targets[i])
    {
		targets.target[i] = ft_validate_and_fetch_target(info->concentration.targets[i],
				info, &error);
		if (error || !targets.target[i])
			return (1);
		targets.target_copy[i] = ft_validate_and_fetch_target(info->concentration.targets[i],
				info, &error);
		if (error || !targets.target_copy[i])
			return (1);
        i++;
    }
	fd = ft_check_and_open(&targets, info);
	if (fd == -1)
		return (1);
	ft_concentration_remove_buf(info, &targets);
	ft_cast_concentration_save_files(info, &targets, fd);
    return (0);
}

void ft_check_concentration(t_char *info, int damage)
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
