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
	{
        ft_concentration_remove_hunters_mark(info, target);
	}
    return ;
}

int ft_remove_concentration(t_char *info)
{
	t_target_data	targets;
    int				i;
	int				error;

    if (DEBUG == 1)
        pf_printf("Removing concentration\n");
    i = 0;
	targets.buff_info = ft_nullptr;
    while (info->concentration.targets && info->concentration.targets[i])
    {
		targets.target[i] = ft_validate_and_fetch_target(info->concentration.targets[i], info, &error);
		if (error || !targets.target[i])
			return (1);
		targets.target_copy[i] = ft_validate_and_fetch_target(info->concentration.targets[i], info, &error);
		if (error || !targets.target_copy[i])
			return (1);
        i++;
    }
    info->concentration.concentration = 0;
    info->concentration.spell_id = 0;
    info->concentration.dice_amount_mod = 0;
    info->concentration.dice_faces_mod = 0;
    info->concentration.base_mod = 0;
	cma_free_double(info->concentration.targets);
    info->concentration.targets = ft_nullptr;
    info->bufs.chaos_armor.duration = 0;
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
