#include "dnd_tools.hpp"
#include "ghost.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/CMA/CMA.hpp"

void ft_ghost_turn(t_char *info)
{
	ft_update_buf(info);
	if (info->flags.prone)
	{
		pf_printf("%s uses their action to stand up.\n", info->name);
		info->flags.prone = 0;
	}
	else
		pf_printf("%s attempts to make either a ranged or melee attack during their turn.\n", info->name);
	if (info->stats.health < info->dstats.health / 2)
	{
		pf_printf("%s lets out a terrifying screech!\n", info->name);
		pf_printf("All enemies within 15 feet must make a DC 14 Wisdom saving throw.\n");
		pf_printf("On a failed save, enemies are frightened and have disadvantage on their attack rolls " \
				  "against %s until the end of their next turn.\n", info->name);
	}
	pf_printf("%s currently has %d/%d HP.\n", info->name, info->stats.health, info->dstats.health);
	return ;
}

static void ft_initialize_gear_and_feats(t_char *info)
{
	(void)info;
	return ;
}

t_char *ft_ghost(const int index, const char **input, t_name *name, int exception)
{
	int error;
	t_char *info;

	info = (t_char *)cma_calloc(1, sizeof(t_char), false);
	if (!info)
		return (ft_nullptr);
	*info = GHOST_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = cma_strjoin("data/", input[0], false);
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
