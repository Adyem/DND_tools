#include "dnd_tools.hpp"
#include "thorbald_ironpocket.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"

void ft_thorbald_ironpocket_turn(SharedPtr<t_char>info)
{
    ft_update_buf(info);
    if (info->flags.prone)
    {
        pf_printf("%s will use his action to stand up\n", info->name);
        info->flags.prone = 0;
    }
    else
        pf_printf("Gundren Rockseeker will try to make either a ranged or melee " \
				"attack during his turn\n");
    pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
    return ;
}

static void ft_initialize_gear_and_feats(SharedPtr<t_char>info)
{
    (void)info;
    return ;
}

SharedPtr<t_char>ft_thorbald_ironpocket(const int index, const char **input, t_name *name, int exception)
{
    int error = 0;
    SharedPtr<t_char> info(1);

	if (!info)
    {
        pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
        return (SharedPtr<t_char>());
    }
    *info = THORBALD_IRONPOCKET_INFO;
    info->name = input[0];
    info->struct_name = name;
    info->save_file = cma_strjoin("data/", input[0], false);
    if (!info->save_file)
    {
        ft_free_info(info);
        return (SharedPtr<t_char>());
    }
    if (index == 2)
    {
        if (ft_strcmp_dnd(input[1], "init") == 0)
        {
            ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
            pf_printf("Stats for %s written to a file\n", info->name);
            ft_free_info(info);
            return (SharedPtr<t_char>());
        }
    }
    error = ft_npc_open_file(info);
    if (error)
    {
        ft_free_info(info);
        return (SharedPtr<t_char>());
    }
    error = ft_npc_check_info(info);
    if (error)
    {
        ft_free_info(info);
        return (SharedPtr<t_char>());
    }
    ft_initialize_gear_and_feats(info);
    if (exception)
        return (info);
    ft_npc_change_stats(info, index, input);
    ft_free_info(info);
    return (SharedPtr<t_char>());
}
