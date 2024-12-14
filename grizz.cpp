#include "character.hpp"
#include "dnd_tools.hpp"
#include "grizz.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"
#include "libft/CMA/CMA.hpp"

void ft_grizz_turn(SharedPtr<t_char> info)
{
	ft_update_buf(info);
	if (info->flags.prone)
	{
		pf_printf("%s will use his/her action to stand up\n", info->name);
		info->flags.prone = 0;
	}
	else
		pf_printf("The grizz will try to make either a ranged or melee attack during his turn\n");
	pf_printf("Grizz currently has %d/%d hp\n", info->stats.health, info->dstats.health);
	if (info->stats.health < info->dstats.health / 2)
	{
		pf_printf("%s uses Roar of the Grizz!\n", info->name);
    	pf_printf("All enemies within 15 feet must make a DC 14 Wisdom saving throw.\n");
    	pf_printf("On a failed save, enemies are frightened, imposing disadvantage on their " \
				"attack rolls against Grizz until the end of their next turn.\n");
	}
	info->flags.reaction_used = 0;
	return ;
}

static void ft_initialize_gear_and_feats(SharedPtr<t_char> info)
{
	info->feats.crackback.active = 1;
	return ;
}

SharedPtr<t_char> ft_grizz(const int index, const char **input, t_name *name, int exception)
{
	int error = 0;
    SharedPtr<t_char> info(1);

	if (!info)
    {
        pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
        return (SharedPtr<t_char> ());
    }
	*info = GRIZZ_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = cma_strjoin("data/", input[0], false);
	if (!info->save_file)
	{
		ft_free_info(info);
		return (SharedPtr<t_char> ());
	}
	if (index == 2)
	{
		if (ft_strcmp_dnd(input[1], "init") == 0)
		{
			ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
			pf_printf("Stats for %s written on a file\n", info->name);
			ft_free_info(info);
			return (SharedPtr<t_char> ());
		}
	}
	error = ft_npc_open_file(info);
	if (error)
	{
		ft_free_info(info);
		return (SharedPtr<t_char> ());
	}
	error = ft_npc_check_info(info);
	if (error)
	{
		ft_free_info(info);
		return (SharedPtr<t_char> ());
	}
	ft_initialize_gear_and_feats(info);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (SharedPtr<t_char> ());
}
