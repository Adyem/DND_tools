#include "dnd_tools.h"

static int	ft_check_int(char *content, int index, char *filename)
{
	int temp;
	int result;

	temp = index;
	if (DEBUG == 1)
		ft_printf("%s\n", content);
	while (index)
	{
		content++;
		index--;
	}
	if (ft_check_value(content))
	{
		while (temp)
		{
			content--;
			temp--;
		}
		ft_printf_fd(2, "2-Something is wrong with the save file from %s at the line: %s\n",
				filename ,content);
		return (-99999);
	}
	result = ft_atoi(content);
	return (result);
}

static char	*ft_check_string(char *content, int index)
{
	char	*result;

	content = content + index;
	result = ft_strdup(content);
	return (result);
}

int	ft_check_stat_pc(t_pc *player, char **content, char *filename)
{
	int	i;

	player->initiative = -1;
	player->name = NULL;
	i = 0;
	while (content[i])
	{
		if (ft_strncmp(content[i], "INITIATIVE=", 11) == 0 && (player->initiative == -2))
			player->initiative = ft_check_int(content[i], 11, filename);
		else if (ft_strncmp(content[i], "NAME=", 5) == 0 && (player->name == NULL))
		{
			player->name = ft_check_string(content[i], 5);
			if (!player->name)
				return (1);
		}
		else
			return (1);
	}
	if (!(player->initiative >= 0 && player->initiative <= 50))
		return (1);
	if (!player->name)
		return (1);
	return (0);
}
