#include "dnd_tools.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"

void	ft_save_pc(t_pc *player, int fd)
{
	ft_printf_fd(fd, "NAME=%s\n", player->name);
	ft_printf_fd(fd, "INITIATIVE=%i\n", player->initiative);
	return ;
}
