#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/string.hpp"
#include "libft/Errno/errno.hpp"

static ft_string ft_felbeast_attack_effect_construct_message(t_char *info)
{
	char *string_constitution = cma_itoa(ft_calculate_dex(info));
	if (!string_constitution)
	{
		pf_printf_fd(2, "148-Error: Allocation failure %s poison effect\n", info->name);
		return (ft_string(STRING_MEM_ALLOC_FAIL));
	}
	ft_string temp("the target needs to succeed on a ");
	if (temp.getError())
	{
		pf_printf_fd(2, "149-Error: Allocation failure %s poisen effect\n", info->name);
		cma_free(string_constitution);
		return (ft_string(STRING_MEM_ALLOC_FAIL));
	}
	ft_string message = temp + string_constitution + " constitution save or become poisoned";
	cma_free(string_constitution);
	if (message.getError())
	{
		pf_printf_fd(2, "150-Error: Allocation failure %s poisen effect\n", info->name);
		return (ft_string(STRING_MEM_ALLOC_FAIL));
	}
	return (message);
}

void	ft_felbeast_attack_effects(t_char *info, t_equipment_id *weapon, int is_crit)
{
	ft_string message = ft_felbeast_attack_effect_construct_message(info);
	if (message.getError())
		return ;
	ft_readline_confirm(message);
	(void)weapon;
	(void)is_crit;
}
