#include "dnd_tools.h"

static int	ft_turn_check_marker(t_pc *players)
{
	t_pc	*temp;
	int		marker;

	temp = players;
	marker = 0;
	while (temp)
	{
		if (ft_strncmp("--turn--", temp->name, 8) == 0)
			marker++;
		temp = temp->next;
	}
	if (marker == 0)
		ft_printf_fd(2, "File is corrupted no turn marker found\n");
	else if (marker > 1)
		ft_printf_fd(2, "File is corrupted multiple turn markers found\n");
	return (marker);
}

static int	ft_turn_move_marker(t_pc *players)
{
	t_pc	*temp;
	char	*name;

	temp = players;
	while (temp)
	{
		if (ft_strncmp("--turn--", temp->name, 8) == 0)
		{
			name = ft_strtrim(temp->name, "--turn--");
			if (!name)
				ft_printf_fd(2, "244-Error allocating memory turn\n");
			free(temp->name);
			temp->name = name;
			if (temp->next)
			{
				name = ft_strjoin("--turn--", temp->next->name);
				if (!name)
				{
					ft_printf_fd(2, "245-Error allocating memory turn strjoin\n");
					return (1);
				}
				free(temp->next->name);
				temp->next->name = name;
			}
			else
			{
				name = ft_strjoin("--turn--", players->name);
				if (!name)
				{
					ft_printf_fd(2, "246-Error allocating memory turn strjoin\n");
					return (1);
				}
				free(players->name);
				players->name = name;
			}
			break ;
		}
		temp = temp->next;
	}
	return (0);
}

static int	ft_turn_write(t_pc *players)
{
	int		fd;
	t_pc	*temp;

	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf_fd(2, "263-Error opening file %s\n", strerror(errno));
		return (1);
	}
	temp = players;
	while (temp)
	{
		ft_printf_fd(fd, "%s=%i\n", temp->name, temp->initiative);
		temp = temp->next;
	}
	close(fd);
	return (0);
}

static int	ft_turn_run(t_pc *players, t_name *name)
{
	t_pc	*pc_temp;
	t_name	*n_temp;
	char	*c_name;
	int		found;

	pc_temp = players;
	found = 0;
	while(pc_temp && found == 0)
	{
		if (ft_strncmp("--turn--", pc_temp->name, 8) == 0)
		{
			found = 1;
			c_name = ft_strtrim(pc_temp->name, "--turn--");
			if (!name)
			{
				ft_printf_fd(2, "247-Error allocating memory strtrim\n");
				return (1);
			}
			n_temp = name;
			while (n_temp != NULL && found != 2)
			{
				if (ft_strcmp_dnd(n_temp->name, c_name) == 0)
				{
					n_temp->function(1, &c_name, 0);
					found = 2;
				}
				n_temp = n_temp->next;
			}
		}
		if (ft_strncmp("--turn--PC--", pc_temp->name, 12) == 0)
			ft_printf("the current turn is for %s\n", &pc_temp->name[12]);
		pc_temp = pc_temp->next;
	}
	free(c_name);
	return (0);
}

void	ft_turn_next(t_name *name)
{
	t_pc	*players;
	char	**content;
	int		fd;

	fd = open("data/data--initiative", O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "Error opening data initiative file %s\n", strerror(errno));
		return ;
	}
	content = ft_read_file_dnd(fd);
	close(fd);
	if (!content)
		return ;
	players = ft_initiative_players_am(content);
	ft_free_content(content);
	if (!players)
		return ;
	if (ft_turn_check_marker(players) != 1)
	{
		ft_free_players(players);
		return ;
	}
	if (ft_turn_run(players, name))
	{
		ft_free_players(players);
		return ;
	}
	if (ft_turn_move_marker(players))
	{
		ft_free_players(players);
		return ;
	}
	ft_turn_write(players);
	ft_free_players(players);
	return ;
}
