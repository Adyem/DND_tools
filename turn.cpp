#include "dnd_tools.hpp"
#include "libft/libft/libft.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>

static int ft_turn_check_marker(t_pc *players)
{
	t_pc *temp;
	int marker;

	temp = players;
	marker = 0;
	while (temp)
	{
		if (ft_strncmp("--turn--", temp->name, 8) == 0)
			marker++;
		temp = temp->next;
	}
	if (marker == 0)
		std::cerr << "File is corrupted no turn marker found\n";
	else if (marker > 1)
		std::cerr << "File is corrupted multiple turn markers found\n";
	return (marker);
}

static int ft_turn_move_marker(t_pc *players)
{
	t_pc *temp;
	char *name;

	temp = players;
	while (temp)
	{
		if (ft_strncmp("--turn--", temp->name, 8) == 0)
		{
			name = ft_strtrim_prefix(temp->name, "--turn--");
			if (!name)
				std::cerr << "244-Error allocating memory turn\n";
			free(temp->name);
			temp->name = name;
			if (temp->next)
			{
				name = ft_strjoin("--turn--", temp->next->name);
				if (!name)
				{
					std::cerr << "245-Error allocating memory turn strjoin\n";
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
					std::cerr << "246-Error allocating memory turn strjoin\n";
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

static int ft_turn_write(t_pc *players)
{
	int fd;
	t_pc *temp;

	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		std::cerr << "263-Error opening file " << strerror(errno) << "\n";
		return (1);
	}
	temp = players;
	while (temp)
	{
		std::cout << temp->name << "=" << temp->initiative << "\n";
		temp = temp->next;
	}
	close(fd);
	return (0);
}

static int ft_turn_run(t_pc *players, t_name *name)
{
	t_pc *pc_temp;
	t_name *n_temp;
	char *c_name;
	const char *temp[2];
	int found;

	c_name = nullptr;
	pc_temp = players;
	found = 0;
	while (pc_temp && found == 0)
	{
		if (ft_strncmp("--turn--", pc_temp->name, 8) == 0)
		{
			found = 1;
			c_name = ft_strtrim_prefix(pc_temp->name, "--turn--");
			if (!c_name)
			{
				std::cerr << "247-Error allocating memory strtrim\n";
				return (1);
			}
			n_temp = name;
			while (n_temp != nullptr && found != 2)
			{
				if (ft_strcmp_dnd(n_temp->name, c_name) == 0)
				{
					temp[0] = c_name;
					temp[1] = nullptr;
					n_temp->function(1, temp, name, 0);
					found = 2;
				}
				n_temp = n_temp->next;
			}
		}
		if (ft_strncmp("--turn--PC--", pc_temp->name, 12) == 0)
			std::cout << "the current turn is for " << &pc_temp->name[12] << "\n";
		pc_temp = pc_temp->next;
	}
	free(c_name);
	return (0);
}

void ft_turn_next(t_name *name)
{
	t_pc *players;
	char **content;
	int fd;

	fd = open("data/data--initiative", O_RDONLY);
	if (fd == -1)
	{
		std::cerr << "Error opening data initiative file " << strerror(errno) << "\n";
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
