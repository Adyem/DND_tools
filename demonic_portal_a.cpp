#include "dnd_tools.hpp"
#include "demonic_portal_a.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/dice_roll.hpp"
#include "libft/CMA/CMA.hpp"

static void ft_portal_surge(t_char *info)
{
    (void)info;
    int roll = ft_dice_roll(1, 5);
    if (roll == -1)
        return ;
    if (roll == 1)
    {
        pf_printf("Portal Surge: Psychic shriek - DC15 Con save for all nearby or be stunned\n");
    }
    else if (roll == 2)
    {
        pf_printf("Portal Surge: Demonic tentacles - DC15 Dex save or be grappled\n");
    }
    else if (roll == 3)
    {
        pf_printf("Portal Surge: Vision flash - DC15 Wis save or suffer disadvantage on attacks\n");
    }
    else if (roll == 4)
    {
        char    **player_list;
        int             i;
        int             damage;

        player_list = ft_get_pc_list();
        if (!player_list)
            return ;
        i = ft_double_char_length(const_cast<const char **>(player_list));
        i = ft_dice_roll(1, i) - 1;
        damage = ft_dice_roll(2, 6);
        pf_printf("Portal Surge: Arcane backlash hits %s for %d force damage\n", player_list[i], damage);
        cma_free_double(player_list);
    }
    else
    {
        pf_printf("Portal Surge: Calm moment - no effect\n");
    }
    return ;
}

void ft_demonic_portal_a_turn(t_char * info)
{
        ft_update_buf(info);
        ft_portal_surge(info);
        if (info->flags.prone)
        {
                pf_printf("%s will use his/her action to stand up\n", info->name);
                info->flags.prone = 0;
        }
	else
		pf_printf("The %s will try to make either a ranged or melee attack during his turn\n",
				info->name);
	pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
	return ;
}

static void ft_initialize_gear_and_feats(t_char * info)
{
	(void)info;
	return ;
}

void	ft_demonic_portal_a_loot(t_char * info)
{
	(void)info;
	return ;
}

t_char *ft_demonic_portal_a(const int index, const char **input, t_name *name, int exception)
{
	int error = 0;
	t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
	if (!info)
    {
        pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
        return (ft_nullptr);
    }
	*info = DEMONIC_PORTAL_A_INFO;
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
			int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
			if (result == -1)
			{
				pf_printf("147-Error Invalid hit dice %s", info->name);
				ft_free_info(info);
				return (ft_nullptr);
			}
			info->dstats.health = info->dstats.health + result;
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
