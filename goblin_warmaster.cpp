#include "dnd_tools.hpp"
#include "goblin_warmaster.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"

void ft_goblin_warmaster_turn(t_char *info)
{
    ft_update_buf(info);
    if (info->flags.prone)
    {
        ft_printf("%s will use his/her action to stand up\n", info->name);
        info->flags.prone = 0;
    }
    else
        ft_printf("The warmaster will attempt a strategic melee or ranged attack during his turn\n");
    ft_printf("Warmaster currently has %d/%d hp\n", info->stats.health, info->dstats.health);
    if (info->stats.health < info->dstats.health / 2)
        ft_printf("The warmaster is on low health and may use the command ability as a bonus action\n");
}

static void ft_initialize_gear_and_feats(t_char *info)
{
    (void)info;
    return ;
}

t_char *ft_goblin_warmaster(const int index, const char **input, t_name *name, int exception)
{
    int error;
    t_char *info;

    info = (t_char *)cma_calloc(1, sizeof(t_char), false);
    if (!info)
        return (nullptr);
    *info = WARM_INFO;
    info->name = input[0];
    info->struct_name = name;
    info->save_file = cma_strjoin("data/", input[0], false);
    if (!info->save_file)
    {
        ft_free_info(info);
        return (nullptr);
    }
    if (index == 2)
    {
        if (ft_strcmp_dnd(input[1], "init") == 0)
        {
            ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
            ft_printf("Stats for %s written on a file\n", info->name);
            ft_free_info(info);
            return (nullptr);
        }
    }
    error = ft_npc_open_file(info);
    if (error)
    {
        ft_free_info(info);
        return (nullptr);
    }
    error = ft_npc_check_info(info);
    if (error)
    {
        ft_free_info(info);
        return (nullptr);
    }
    ft_initialize_gear_and_feats(info);
    if (exception)
        return (info);
    ft_npc_change_stats(info, index, input);
    ft_free_info(info);
    return (nullptr);
}
