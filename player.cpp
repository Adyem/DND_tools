#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>

static void ft_add_player(t_pc *player)
{
    int fd;
    char *filename;

    filename = ft_strjoin("data/PC--", player->name);
    if (!filename)
    {
        std::cerr << "240-Error: Allocating memory for player string join" << std::endl;
        return ;
    }
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    free(filename);
    if (fd == -1)
    {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        return ;
    }
    std::cout << "Adding player " << player->name << std::endl;
    ft_save_pc(player, fd);
    close(fd);
	return ;
}

void ft_player(const char **input)
{
    t_pc *player = nullptr;

	if (input[1] && input[2])
	{
        if (ft_strcmp_dnd(input[0], "add") == 0)
        {
            player = (t_pc *)malloc(sizeof(t_pc));
            if (!player)
            {
                std::cerr << "248-Error: Allocating memory for player" << std::endl;
                return ;
            }
            player->name = ft_strdup(input[2]);
            if (!player->name)
            {
                std::cerr << "249-Error: Allocating memory for player name" << std::endl;
                free(player);
                return ;
            }
            player->initiative = 0;
            ft_add_player(player);
        }
	}
	else
		std::cerr << "243-Error: Invalid input for player" << std::endl;
    free(player->name);
    free(player);
	return ;
}
