#include <cerrno>
#include "dnd_tools.hpp"
#include "chaos_crystal.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void ft_chaos_crystal_damage(t_char *info)
{
	char	**player_list;
	int		i;

	player_list = ft_get_pc_list();
	if (!player_list)
		return ;
	i = ft_double_char_length((const char **)player_list);
	i = ft_dice_roll(1, i);
    pf_printf("%s shoots a magic missile at %s and he/she takes 1 force damage, " \
            " the target does not need to make a concentration save for this damage\n",
            info->name, player_list[i]);
    cma_free_double(player_list);
    return ;
}

void ft_chaos_crystal_turn(t_char *info)
{
    ft_update_buf(info);
    ft_chaos_crystal_damage(info);
    pf_printf("Chaos_crystal currently has %d/%d hp\n",
			info->stats.health, info->dstats.health);
	return ;
}

static void ft_initialize_gear_and_feats(t_char *info)
{
    (void)info;
    return ;
}

t_char *ft_chaos_crystal(const int index, const char **input, t_name *name, int exception)
{
    int error;
    t_char *info;

    info = (t_char *)cma_calloc(1, sizeof(t_char), false);
    if (!info)
    {
        pf_printf("103-Error: Failed to allocate memory info %s\n", input[0]);
        return (ft_nullptr);
    }
    *info = CHAOS_CRYSTAL_INFO;
    info->name = input[0];
    info->struct_name = name;
    info->save_file = cma_strjoin("data/", input[0], false);
    if (!info->save_file)
    {
        pf_printf("106-Error: Failed to allocate memory save_file name %s\n", info->name);
        ft_free_info(info);
        return (ft_nullptr);
    }
    if (index == 2)
    {
        if (ft_strcmp_dnd(input[1], "init") == 0)
        {
            ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
            pf_printf("Stats for %s written on a file\n", info->name);
            ft_free_info(info);
            return (ft_nullptr);
        }
    }
    error = ft_npc_open_file(info);
    if (error)
    {
        ft_free_info(info);
        return (ft_nullptr);
    }
    error = ft_npc_check_info(info);
    if (error)
    {
        ft_free_info(info);
        return (ft_nullptr);
    }
    ft_initialize_gear_and_feats(info);
    if (exception)
        return (info);
    ft_npc_change_stats(info, index, input);
    ft_free_info(info);
    return (ft_nullptr);
}
