#include "dnd_tools.h"

void	ft_change_stats_04(t_char *info, char **input)
{
	int	resistance;

	if (ft_strcmp_dnd(input[3], "damage") == 0)
	{
		if (info->version_number < 2)
			ft_deal_damage(info, input[1], NULL, 0, 1);
		else
		{
			resistance = ft_get_resistance(info, input[2]);
			ft_deal_damage(info, input[1], input[2], resistance, 1);
		}
    }
}
