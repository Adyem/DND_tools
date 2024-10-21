#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "dnd_tools.hpp"
#include <cstdlib>

void	ft_free_info(t_char *info)
{
	if (info && DEBUG == 1)
		ft_printf("freeing info %s\n", info->name);
	cma_free_double(info->debufs.hunters_mark.caster_name);
	cma_free_double(info->concentration.targets);
	cma_free(info->bufs.meteor_strike.target_id);
	cma_free(info->bufs.frost_breath.target_id);
	cma_free(info->bufs.arcane_pounce.target_id);
	cma_free(info->bufs.earth_pounce.target_id);
	cma_free(info->save_file);
	cma_free(info);
	return ;
}
