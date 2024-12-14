#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void ft_set_debuf_blinded(SharedPtr<t_char> info, const char **input)
{
	int result;

	result = ft_check_stat(info, input[2], 0);
	if (result < 0 || result > 50)
	{
		pf_printf_fd(2, "230-Error blinded value out of bounds or not found\n");
		return ;
	}
	info->debufs.blinded.duration = result;
	return ;
}
