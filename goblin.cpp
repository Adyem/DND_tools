#include "character.hpp"
#include "dnd_tools.hpp"
#include "goblin.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"

void ft_goblin_turn(t_char *info)
{
    ft_update_buf(info);
	if (info->flags.prone)
	{
        pf_printf("%s will use his/her action to stand up\n", info->name);
        info->flags.prone = 0;
	}
	else
		pf_printf("The goblin will try to make either a ranged or melee attack during his turn\n");
	pf_printf("Goblin currently has %d/%d hp\n", info->stats.health, info->dstats.health);
	if (info->stats.health < info->dstats.health / 2)
		pf_printf("The goblin is on low health and can disengage as a bonus action\n");
	return ;
}

static void ft_initialize_gear_and_feats(t_char *info)
{
    (void)info;
    return ;
}

t_char *ft_goblin(const int index, const char **input, t_name *name, int exception)
{
    int error = 0;
    t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
	if (!info)
    {
        pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
        return (ft_nullptr);
    }
    *info = GOBLIN_INFO;
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
        if (ft_strcmp_dnd(input[1], "init") == 0)
        {
			ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
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
