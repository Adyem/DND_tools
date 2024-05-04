#include "dnd_tools.h"

static int	ft_initiative_copy_v(t_pc *players, char *content)
{
	char *temp;

	temp = ft_strchr(content, '=');
	if (!temp)
		return (ft_initiative_free_pc(players));
	temp = '\0';
	temp++;
	players->name = strdup(content);
	if (!players->name)
		return (ft_initiative_free_pc(players));
	if (ft_check_value(temp))
		return (ft_initiative_free_pc(players));
	players->initiative = ft_atoi(content);
	return (0);
}

static t_pc	ft_initiative_players_am(char ** content)
{
	t_pc	*players;
	t_pc	*temp;
	int		i;

	players = malloc(sizeof(players));
	if (!players)
		return (NULL);
	players->next = NULL;
	players->name = NULL;
	players->initiative = -2;
	if (ft_initiative_copy_v(players, content[0]))
		return (ft_initiative_free_pc(players));
	temp = players;
	i = 1;
	while (content[i])
	{
		temp->next = malloc(sizeof(players));
		if (!temp->next)
			return (NULL);
	}
}

void	ft_initiative_sort(int fd)
{
	t_pc	*players;
	char	**content;

	if (fd == -1)
	{
		ft_printf_fd(2, "Error opening file: %s\n", strerror(errno));
		return ;
	}
	content = ft_read_file_dnd(fd);
	if (!content)
		return (NULL);
	players = ft_initiative_players_am(content);
	if (!players)
		return ;
}
