#include "dnd_tools.hpp"
#include "xavius.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/rng.hpp"
#include "libft/CMA/CMA.hpp"
#include <unistd.h>

static void    ft_xavius_lightningV2_strike(t_char *info)
{
    info->bufs.lightning_strikeV2.duration = 1;
    info->bufs.lightning_strikeV2.dice_amount = 2;
    info->bufs.lightning_strikeV2.dice_faces = 8;
    info->bufs.lightning_strikeV2.distance = 5;
    print_lightning_strike_v2(info);
    return ;
}
static char    *ft_shadow_clone_name(int index)
{
    char    *id = cma_itoa(index);
    char    *name;

    if (!id)
        return (ft_nullptr);
    if (index < 10)
    {
        char    *tmp = cma_strjoin("0", id);

        cma_free(id);
        if (!tmp)
            return (ft_nullptr);
        id = tmp;
    }
    name = cma_strjoin("shadow_illusion_", id);
    cma_free(id);
    if (!name)
        return (ft_nullptr);
    return (name);
}

static void     ft_spawn_shadow_clone(t_char *info)
{
    int     index = 1;

    while (index <= 9)
    {
        char    *name = ft_shadow_clone_name(index);
        char    *path = ft_nullptr;

        if (!name)
            return ;
        path = cma_strjoin("data/", name);
        if (!path)
        {
            cma_free(name);
            return ;
        }
        if (access(path, F_OK) != 0)
        {
            const char      *input[3];

            input[0] = name;
            input[1] = "init";
            input[2] = ft_nullptr;
            ft_shadow_illusion(2, input, info->struct_name, 0);
            cma_free(path);
            cma_free(const_cast<char *>(input[0]));
            info->bufs.shadow_illusion.active = 1;
            info->bufs.shadow_illusion.duration = 5;
            print_shadow_illusion(info);
            return ;
        }
        cma_free(path);
        cma_free(name);
        index++;
    }
    pf_printf("All shadow illusions already exist.\n");
    return ;
}

static void     ft_xavius_shadow_illusion(t_char *info)
{
    ft_spawn_shadow_clone(info);
}

void ft_xavius_turn(t_char * info)
{
    ft_update_buf(info);
    if (info->flags.prone)
    {
        pf_printf("%s will use his/her action to stand up\n", info->name);
        info->flags.prone = 0;
    }
    else
        pf_printf("The %s will try to make either a ranged or melee attack during " \
                "his turn\n", info->name);
    if (info->stats.turn == 2)
        ft_xavius_lightningV2_strike(info);
    if (info->stats.turn == 3)
        ft_xavius_shadow_illusion(info);
    if (info->stats.turn == 5)
        info->stats.turn = 0;
    else
        info->stats.turn++;
    pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health,
            info->dstats.health);
    return ;
}

static void ft_initialize_gear_and_feats(t_char * info)
{
    (void)info;
    return ;
}

void    ft_xavius_loot(t_char * info)
{
    (void)info;
    return ;
}

t_char *ft_xavius(const int index, const char **input, t_name *name, int exception)
{
    int error = 0;
    t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
    if (!info)
    {
        pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
        return (ft_nullptr);
    }
    *info = XAVIUS_INFO;
    info->name = input[0];
    info->struct_name = name;
    info->save_file = cma_strjoin("data/", input[0]);
    if (!info->save_file)
    {
        ft_free_info(info);
        return (ft_nullptr);
    }
    if (index == 2)
    {
        if (ft_strcmp(input[1], "init") == 0)
        {
            int result = ft_dice_roll(info->hit_dice.dice_amount,
                    info->hit_dice.dice_faces);
            if (result == -1)
            {
                pf_printf("147-Error Invalid hit dice %s", info->name);
                ft_free_info(info);
                return (ft_nullptr);
            }
            info->dstats.health = info->dstats.health + result;
            ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
                    S_IWUSR);
            if (file.get_error())
            {
                pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                    file.get_error_str());
                return (ft_nullptr);
            }
            ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
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
