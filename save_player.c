#include "dnd_tools.h"

void	ft_save_pc(t_pc *player)
{
	ft_printf_fd(2, "NAME=%s\n", player->name);
	ft_printf_fd(2, "INITIATIVE=%i\n", player->initiative);
	return ;
}
