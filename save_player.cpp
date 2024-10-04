#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"

void	ft_save_pc(t_pc *player, int fd)
{
	ft_printf_fd(fd, "NAME=%s\n", player->name);
	ft_printf_fd(fd, "INITIATIVE=%d\n", player->initiative);
	return ;
}
