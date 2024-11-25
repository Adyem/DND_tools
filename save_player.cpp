#include "dnd_tools.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/Printf/ft_printf.hpp"

void	ft_save_pc(t_pc *player, ft_file &file)
{
	pf_printf_fd(file.get_fd(), "NAME=%s\n", player->name);
	pf_printf_fd(file.get_fd(), "INITIATIVE=%d\n", player->initiative);
	return ;
}
