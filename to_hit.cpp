#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"

void ft_pc_specific(t_char *info, int number)
{
	if (ft_strcmp_dnd(info->name, "grizz"))
		ft_grizz_crackback(info, number);
	return ;
}

void ft_npc_check_ac(t_char *info, const char **input)
{
	int number;
	int ac;

	ac = ft_calculate_ac(info);
	ft_to_hit_check_buff(info);
	if (ft_strcmp_dnd(input[2], "crit") == 0)
	{
		if (info->bufs.protective_winds.duration > 0)
			ft_printf("%s has protective winds running, any projectiles are thrown "
			          "back at the attacker\n", info->name);
		ft_printf("%s was hit by a critical strike\n", info->name);
		return ;
	}
	else if (ft_check_value(input[2]))
	{
		ft_printf_fd(2, "1-to hit expecting a number between 1 and 99 or the word 'crit'\n");
		return ;
	}
	number = ft_atoi(input[2]);
	if (number >= 0 && number <= 99)
	{
		if (info->bufs.protective_winds.duration > 0)
			ft_printf("%s has protective winds running, any projectiles are thrown "
			          "back at the attacker\n", info->name);
		if (ac <= number)
			ft_printf("%s was hit by the attack\n", info->name);
		else
			ft_printf("the attack missed %s\n", info->name);
	}
	else
		ft_printf_fd(2, "2-to hit expecting a number between 1 and 99 or the word 'crit'\n");
	ft_pc_specific(info, number);

	return ;
}
