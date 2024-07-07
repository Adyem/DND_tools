#include "dnd_tools.h"

static void	ft_add_player(t_pc *player)
{
	int		fd;
	char	*filename;

	filename = ft_strjoin("data/PC--", player->name);
	if (!filename)
	{
		ft_printf_fd(2, "240-Error allocating memory add player strjoin\n");
		return ;
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR);
	free(filename);
	if (fd == -1)
	{
		ft_printf_fd(2, "Error opening file: %s\n", strerror(errno));
		return ;
	}
	ft_save_pc(player, fd);
	close (fd);
	return ;
}

void ft_player(const char **input)
{
	t_pc *player;

	player = NULL;
	if (input[1] && input[2])
	{
		if (ft_strcmp_dnd(input[0], "add") == 0)
		{
			player = malloc(sizeof(t_pc));
			if (!player)
			{
				ft_printf_fd(2, "248-Error allocating memory for player");
				return ;
			}
			player->name = ft_strdup(input[2]);
			{
				ft_printf_fd(2, "249-Error allocating memory player name");
				free(player);
				return ;
			}
			player->initiative = 0;
			ft_add_player(player);
		}
	}
	else
		ft_printf_fd(2, "243-Error with input: player");
	free(player->name);
	free(player);
	return ;
}
