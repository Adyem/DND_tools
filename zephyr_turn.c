#include "dnd_tools.h"

void	ft_zephyr_spells(t_char *info)
{
	t_char	*air_totem;

	ft_printf("zephyr will try to use a melee attack and use a ranged attack if no one" \
			" is within range\n\n");
	if (info->stats.turn == 1)
	{
		ft_printf("%s\n", ZEPHYR_AIR_TOTEM);
		air_totem = (t_char *)malloc(sizeof(t_char));
		if (!air_totem)
			return ;
		*air_totem = AIR_TOTEM_INFO;
		ft_npc_write_file(air_totem, &air_totem->dstats, &air_totem->c_resistance, -1);
		ft_printf("Zephyr summoned an air totem, if a old totem was up it disappears\n");
		free(air_totem);
	}
	else if (info->stats.turn == 2)
	{
		ft_printf("%s\n", ZEPHYR_GUST_OF_WIND);
		ft_printf("%s\n", ZEPHYR_LIGHTNING_STRIKE);
		info->bufs.lightning_strike.duration = 1;
	}
	else if (info->stats.turn == 3)
		ft_printf("%s\n", ZEPHYR_GUST_OF_WIND);
	else if (info->stats.turn == 4)
		ft_printf("%s\n", ZEPHYR_CHAIN_LIGHTNING);
	else if (info->stats.turn == 5)
	{
		ft_printf("%s\n", ZEPHYR_PROTECTIVE_WINDS);
		ft_printf("%s\n", ZEPHYR_LIGHTNING_STRIKE);
		info->bufs.lightning_strike.duration = 1;
		info->bufs.protective_winds.duration = 1;
	}
	else if (info->stats.turn == 6)
	{
		ft_printf("%s\n", ZEPHYR_GUST_OF_WIND);
		ft_printf("%s\n", ZEPHYR_PROTECTIVE_WINDS);
		info->bufs.protective_winds.duration = 1;
	}
	info->stats.turn++;
	if (info->stats.turn == 7)
		info->stats.turn = 1;
	return ;
}
