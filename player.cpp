#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

static void ft_add_player(t_pc *player)
{
	char *filename;

	filename = cma_strjoin("data/PC--", player->name, false);
	if (!filename)
	{
		pf_printf("240-Error: Allocating memory for player string join\n");
		return ;
	}
	ft_file pc_file(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	cma_free(filename);
	if (pc_file.get_error_code())
	{
		pf_printf("Error opening file: %s\n", pc_file.get_error_message());
		return ;
	}
	pf_printf("Adding player %s\n", player->name);
	ft_save_pc(player, pc_file);
	return ;
}

static void	ft_list_players(void)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir("data");
	if (dir == NULL)
	{
		pf_printf("Unable to open data folder: %s", strerror(errno));
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (strncmp(entry->d_name, "pc--", 4) == 0)
			pf_printf("%s\n", entry->d_name + 4);
	}
	closedir(dir);
	return ;
}


void	ft_player(const char **input)
{
	t_pc *player = ft_nullptr;

	if (input[1] && input[2])
	{
		if (ft_strcmp_dnd(input[0], "add") == 0)
		{
			player = (t_pc *)cma_malloc(sizeof(t_pc), false);
			if (!player)
			{
				pf_printf("248-Error: Allocating memory for player\n");
				return ;
			}
			player->name = cma_strdup(input[2], false);
			if (!player->name)
			{
				pf_printf("249-Error: Allocating memory for player name\n");
				cma_free(player);
				return ;
			}
			player->initiative = 0;
			ft_add_player(player);
		}
		else if (ft_strcmp_dnd(input[0], "list"))
			ft_list_players();
	}
	else
		pf_printf("243-Error: Invalid input for player\n");
	cma_free(player->name);
	cma_free(player);
	return ;
}
