#include "dnd_tools.h"
#include "libft/libft/libft.h"
#include <fcntl.h>

static void	ft_chaos_crystal_damage(t_char *info)
{
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
	while (result == -1 || ft_strncmp(content[result], "pc--", 4))
		result = ft_dice_roll(1, length) - 1;
	ft_printf("%s shoots a magic missle at %s and he/she takes 2 force damage\n",
			info->name, &content[result][4]);
	return ;
}

void	ft_chaos_crystal_turn(t_char *info)
{
	ft_update_buf(info);
	ft_chaos_crystal_damage(info);
	ft_printf("Chaos_crystal currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

t_char	*ft_chaos_crystal(int index, const char **input, t_name *name, int exception)
{
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
		return (NULL);
	*info = CHAOS_CRYSTAL_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
		return (NULL);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
