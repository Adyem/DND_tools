#include "character.hpp"
#include "dnd_tools.hpp"
#include "grizz.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/CMA/CMA.hpp"

void ft_grizz_crackback(t_char *info, int number)
{
	if (number < 10 && !info->flags.reaction_used)
	{
		ft_printf("because of the low attack roll %s has the oppertunity to react with an " \
				"oppertunity attack", info->name);
		if (info->equipment.weapon.attack.function)
			info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
		else
			ft_printf_fd(2, "No MH weapon set for %s", info->name);
		info->flags.reaction_used = 1;
	}
	return ;
}

void ft_grizz_turn(t_char *info)
{
	ft_update_buf(info);
	if (info->flags.prone)
	{
		ft_printf("%s will use his/her action to stand up\n", info->name);
		info->flags.prone = 0;
	}
	else
		ft_printf("The grizz will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Grizz currently has %d/%d hp\n", info->stats.health, info->dstats.health);
	if (info->stats.health < info->dstats.health / 2)
	{
		ft_printf("Grizz uses Roar of the Grizz!\n");
    	ft_printf("All enemies within 15 feet must make a DC 14 Wisdom saving throw.\n");
    	ft_printf("On a failed save, enemies are frightened, imposing disadvantage on their " \
				"attack rolls against Grizz until the end of their next turn.\n");
	}
	info->flags.reaction_used = 0;
	return ;
}

static void ft_initialize_gear_and_feats(t_char *info)
{
	(void)info;
	return ;
}

t_char *ft_grizz(const int index, const char **input, t_name *name, int exception)
{
	int		error;
	t_char	*info;

	info = (t_char *)cma_calloc(1, sizeof(t_char), false);
	if (!info)
		return (ft_nullptr);
	*info = GRIZZ_INFO;
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
			ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
			ft_printf("Stats for %s written on a file\n", info->name);
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
