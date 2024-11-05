#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"

void	ft_save_pc(t_pc *player, int fd)
{
	pf_printf_fd(fd, "NAME=%s\n", player->name);
	pf_printf_fd(fd, "INITIATIVE=%d\n", player->initiative);
	return ;
}
