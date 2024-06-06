#include "dnd_tools.h"

static int ft_initiative_copy_v(t_pc *head, t_pc *players, char *content)
{
	char *temp;

	temp = ft_strchr(content, '\n');
	if (temp)
		*temp = '\0';
	temp = ft_strchr(content, '=');
	if (!temp)
	{
		ft_printf_fd(2, "Error did not find = sign\n");
		return (ft_free_players(head));
	}
	*temp = '\0';
	temp++;
	players->name = strdup(content);
	if (!players->name)
	{
		ft_printf_fd(2, "257 Error allocating memory\n");
		return (ft_free_players(head));
	}
	if (ft_check_value(temp))
	{
		ft_printf_fd(2, "There is an error on the line: %s\n", temp);
		return (ft_free_players(head));
	}
	players->initiative = ft_atoi(temp);
	if (DEBUG == 1)
		ft_printf("the initiative from %s = %i\n",
				players->name, players->initiative);
	return (0);
}

static void	ft_initiative_players_init(t_pc *players)
{
	players->next = NULL;
	players->name = NULL;
	players->initiative = -2;
}

t_pc	*ft_initiative_players_am(char **content)
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
			ft_free_players(players);
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
	close(fd);
	if (!content)
		return ;
	players = ft_initiative_players_am(content);
	ft_free_double_char(content);
	if (!players)
		return ;
	ft_initiative_sort_2(players);
	ft_free_players(players);
	ft_initiative_print();
	return ;
}
