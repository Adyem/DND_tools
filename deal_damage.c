#include "dnd_tools.h"

void	ft_deal_damage(t_char *info, const char *input, const char *d_type, int resistance,
			int override)
{
	static int	total;
	int			temp;
	int			damage;
	int			extra;

	if (override == 1 || override == 0)
	{
		if (ft_check_value(input))
		{
			ft_printf_fd(2, "1-Damage: expecting a number higher then or equal to 0\n");
			return ;
		}
		damage = ft_atoi(input);
		if (damage < 0)
		{
			ft_printf_fd(2, "2-Damage: expecting a number higher then or equal to 0\n");
			return ;
		}
		if (d_type && resistance > 0)
		{
			extra = damage * (resistance / 100);
			ft_printf("%s is resistant to %s damage and takes %i%% less damage" \
				" for a total of %i less damage\n",
				info->name, d_type, resistance, extra);
			damage = damage - extra;
		}
		else if (d_type && resistance < 0)
		{
			extra = damage * ((resistance * -1) / 100);
			ft_printf("%s is vulnerable to %s damage and takes %i%% more damage" \
				" for a total of %i more damage\n",
				info->name, d_type, resistance, extra);
			damage = damage + extra;
		}
		else if (d_type && resistance == 100)
		{
			ft_printf("%s is immune to %s damage\n", info->name, d_type);
			damage = 0;
		}
		temp = info->stats.health;
		info->stats.health = info->stats.health - damage;
		if (info->stats.health < 0)
			info->stats.health = 0;
		total += damage;
		ft_print_character_status(info, damage * -1, temp);
	}
	if (override == 1 || override == 2)
	{
		if (DEBUG == 1)
			ft_printf("%s takes %i damage\n", info->name, total);
		if (info->version_number >= 2 && info->concentration.concentration)
			ft_check_concentration(info, total);
		total = 0;
	}
	return ;
}
