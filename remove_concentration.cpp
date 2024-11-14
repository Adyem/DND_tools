#include "character.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

static void ft_concentration_remove_buf(t_char *info, t_target_data *targets)
{
    if (info->concentration.spell_id == HUNTERS_MARK_ID)
        ft_concentration_remove_hunters_mark(info, targets);
    return ;
}

static int	ft_remove_concentration_fetch_targets(t_target_data *targets, t_char *info, int i)
{
	int	error = 0;

	targets->target[i] = ft_validate_and_fetch_target(info->concentration.targets[i],
			info, &error);
	if (error || !targets->target[i])
	{
		ft_free_memory_cmt(targets, i);
		return (FAILURE);
	}
	targets->target_copy[i] = ft_validate_and_fetch_target(info->concentration.targets[i],
			info, &error);
	if (error || !targets->target_copy[i])
	{
		ft_free_memory_cmt(targets, i);
		return (FAILURE);
	}
	return (SUCCES);
}

int ft_remove_concentration(t_char *info)
{
	t_target_data	targets;
    int				i;
	int				fd;

	ft_initialize_variables(&targets);
    if (DEBUG == 1)
        pf_printf("Removing concentration\n");
    i = 0;
	targets.buff_info = ft_nullptr;
    while (info->concentration.targets && info->concentration.targets[i])
    {
		ft_remove_concentration_fetch_targets(&targets, info, i);
        i++;
    }
	fd = ft_check_and_open(&targets, info);
	if (fd == -1)
		return (FAILURE);
	ft_concentration_remove_buf(info, &targets);
	ft_cast_concentration_save_files(info, &targets, fd);
    return (SUCCES);
}

