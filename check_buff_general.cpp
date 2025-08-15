#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/RNG.hpp"

int ft_check_bless(t_char * info)
{
	int result = 0;
	if (info->bufs.bless.duration > 0)
        result = ft_dice_roll(info->bufs.bless.dice_amount_mod,
			info->bufs.bless.dice_faces_mod) + info->bufs.bless.base_mod;
	else
        return (0);
	if (result == -1)
	{
		pf_printf_fd(2, "144-Error: dice rolling bless\n");
		return (0);
	}
    pf_printf("%s rolled a %d as an additional modifier for his/her bless buff\n",
			info->name, result);
    return (result);
}
