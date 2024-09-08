#include "dnd_tools.hpp"
#include <fstream>
#include <iostream>

void	ft_save_pc(t_pc *player, int fd)
{
	std::ofstream ofs;

	if (fd == -1)
	{
		std::cerr << "Error: Invalid file descriptor" << std::endl;
		return ;
	}
	ofs.open("/proc/self/fd/" + std::to_string(fd));
	if (!ofs.is_open())
	{
		std::cerr << "Error: failed to open file stream for descriptor " << fd << std::endl;
		return ;
	}
	ofs << "NAME=" << player->name << std::endl;
	ofs << "INITIATIVE=" << player->initiative << std::endl;
	ofs.close();
	return ;
}
