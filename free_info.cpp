#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "dnd_tools.hpp"
#include <cstdlib>

void	ft_free_info(t_char *info)
{
	if (info && DEBUG == 1)
		ft_printf("freeing info %s\n", info->name);
	if (info && info->version_number >= 2)
	{
		cma_free_double(info->debufs.hunters_mark.caster_name);
		cma_free_double(info->concentration.targets);
		cma_free(info->save_file);
	}
	cma_free(info);
	return ;
}
