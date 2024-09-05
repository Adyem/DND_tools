#include "dnd_tools.h"

static void	ft_chaos_crystal_damage(t_char *info)
{
	char	*temp;
	char	**content;
	int		fd;
	int		length;
	int		result;

	fd = open("data/data--initiative", O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "280-Error opening file: %s\n", strerror(errno));
		return ;
	}
	content = ft_read_file_dnd(fd);
	close(fd);
	if (!content)
	{
		ft_printf_fd(2, "281-Error opening file: %s\n", strerror(errno));
		return ;
	}
	length = ft_double_char_length(content);
	result = -1;
	while (result == -1 || (ft_strncmp(content[result], "PC--", 4) != 0
				&& ft_strncmp(content[result], "--turn--PC--", 12) != 0))
	{
		result = ft_dice_roll(1, length) - 1;
		if (DEBUG == 1)
			ft_printf("result = %i\n", result);
	}
	temp = ft_strchr(content[result], '=');
	if (temp)
		*temp = '\0';
	ft_printf("%s shoots a magic missle at %s and he/she takes 1 force damage, " \
			"the target does not need to make a concentration save for this damage\n",
			info->name, &content[result][4]);
	ft_free_double_char(content);
	return ;
}

void	ft_chaos_crystal_turn(t_char *info)
{
	ft_update_buf(info);
	ft_chaos_crystal_damage(info);
	ft_printf("Chaos_crystal currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

static void	ft_initialize_gear_and_feats(t_char *info)
{
	(void)info;
	return ;
}

t_char	*ft_chaos_crystal(const int index, const char **input, t_name *name, int exception)
{
	int		error;
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
	{
		ft_printf_fd(2, "103-Error: Failed to allocate memory info %s\n", input[0]);
		return (NULL);
	}
	*info = CHAOS_CRYSTAL_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
	{
		ft_printf_fd(2, "106-Error: Failed to allocate memory save_file name %s\n", info->name);
		ft_free_info(info);
		return (NULL);
	}
	if (index == 2)
	{
		if (ft_strcmp_dnd(input[1], "init") == 0)
		{
			ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
			ft_printf("Stats for %s written on a file\n", info->name);
			ft_free_info(info);
			return (NULL);
		}
	}
	error = ft_npc_open_file(info);
	if (error)
	{
		ft_free_info(info);
		return (NULL);
	}
	error = ft_npc_check_info(info);
	if (error)
	{
		ft_free_info(info);
		return (NULL);
	}
	ft_initialize_gear_and_feats(info);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
