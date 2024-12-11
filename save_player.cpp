#include "dnd_tools.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/Printf/printf.hpp"

void	ft_save_pc(t_pc *player, ft_file &file)
{
	pf_printf_fd(file, "NAME=%s\n", player->name);
	pf_printf_fd(file, "INITIATIVE=%d\n", player->initiative);
	return ;
}
