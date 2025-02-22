#include "dnd_tools.hpp"
#include "maverick.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/RNG/dice_roll.hpp"

void	ft_maverick_turn(t_char * info)
{
	int		first;
	int		second;
	char	**player_list;

	ft_update_buf(info);
	pf_printf("\n\n");
	player_list = ft_get_pc_list();
	if (ft_double_char_length((const char **)player_list) < 2)
	{
		if (ft_double_char_length((const char **)player_list) > 0)
			pf_printf_fd(2, "283-Error not enough targets for %s\n", info->name);
		cma_free_double(player_list);
		return ;
	}
	first = 0;
	second = 0;
	while (first == second && first != 8)
	{
		first = ft_dice_roll(1, 8);
		second = ft_dice_roll(1, 8);
	}
	ft_maverick_print_f(first, second, info, player_list);
	ft_maverick_print_s(first, second, info, player_list);
	pf_printf("\n\n");
	cma_free_double(player_list);
	return ;
}

static void ft_initialize_gear_and_feats(t_char * info)
{
	(void)info;
	return ;
}

t_char *ft_maverick(const int index, const char **input, t_name *name, int exception)
{
    int error = 0;
    t_char *info = (t_char *)cma_malloc(sizeof(t_char));
	if (!info)
    {
        pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
        return (ft_nullptr);
    }
    *info = MAVERICK_INFO;
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
			if (file.get_error_code())
			{
				pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
					file.get_error_message());
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
