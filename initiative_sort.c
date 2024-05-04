#include "dnd_tools.h"

static int ft_initiative_free_pc(t_pc *players)
{
	t_pc	*temp;

	while (players)
	{
		temp = players->next;
		if (players->name)
			free(players->name);
		free(players);
		players = temp;
	}
	return (1);
}

static int ft_initiative_copy_v(t_pc *head, t_pc *players, char *content)
{
	char *temp;

	temp = ft_strchr(content, '=');
	if (!temp)
		return (ft_initiative_free_pc(head));
	temp = '\0';
	temp++;
	players->name = strdup(content);
	if (!players->name)
		return (ft_initiative_free_pc(head));
	if (ft_check_value(temp))
		return (ft_initiative_free_pc(head));
	players->initiative = ft_atoi(content);
	return (0);
}

static void	ft_initiative_players_init(t_pc *players)
{
	players->next = NULL;
	players->name = NULL;
	players->initiative = -2;
}

static t_pc	*ft_initiative_players_am(char **content)
{
	t_pc	*players;
	t_pc	*temp;
	int		i;

	players = malloc(sizeof(t_pc));
	if (!players)
	{
		ft_printf_fd(2, "Error allocating memory: players\n");
		return (NULL);
	}
	ft_initiative_players_init(players);
	players->initiative = -2;
	if (ft_initiative_copy_v(players, players, content[0]))
		return (NULL);
	temp = players;
	i = 1;
	while (content[i])
	{
		temp->next = malloc(sizeof(t_pc));
		if (!temp->next)
		{
			ft_printf_fd(2, "Error allocating memory: players->next\n");
			ft_initiative_free_pc(players);
			return (NULL);
		}
		ft_initiative_players_init(temp->next);
		if (ft_initiative_copy_v(players, temp->next, content[i]))
			return (NULL);
		temp = temp->next;
		i++;
	}
	return (players);
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
		return ;
	players = ft_initiative_players_am(content);
	if (!players)
	{
		ft_free_content(content);
		return ;
	}
	ft_free_content(content);
	return ;
}
