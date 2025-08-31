#include "dnd_tools.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/Printf/printf.hpp"
#include "key_list.hpp"

void    ft_save_pc(t_pc *player, ft_file &file)
{
    pf_printf_fd(file, "NAME=%s\n", player->name);
    pf_printf_fd(file, "INITIATIVE=%d\n", player->initiative);
    pf_printf_fd(file, "%s%d\n", POSITION_X_KEY, player->position.x);
    pf_printf_fd(file, "%s%d\n", POSITION_Y_KEY, player->position.y);
    pf_printf_fd(file, "%s%d\n", POSITION_Z_KEY, player->position.z);
    return ;
}
