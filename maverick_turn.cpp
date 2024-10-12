#include "dnd_tools.hpp"
#include "maverick.hpp"
#include "libft/Printf/ft_printf.hpp"

static void	ft_maverick_lightning_strike(t_char *info)
{
	info->bufs.lightning_strike.duration = 1;
	info->bufs.lightning_strike.dice_amount = 1;
	info->bufs.lightning_strike.dice_faces = 8;
	info->bufs.lightning_strike.distance = 5;
}

static void	ft_maverick_lightningV2_strike(t_char *info)
{
	info->bufs.lightning_strikeV2.duration = 1;
	info->bufs.lightning_strikeV2.dice_amount = 2;
	info->bufs.lightning_strikeV2.dice_faces = 8;
	info->bufs.lightning_strikeV2.distance = 5;
}

static void	ft_maverick_print_tp(int number)
{
	if (number == 2)
		ft_printf("%s\n", MAVERICK_MTP_METEOR_STRIKE);
	else if (number == 3)
		ft_printf("%s\n", MAVERICK_MTP_LIGHTNING_STRIKE);
	else if (number == 4)
		ft_printf("%s\n", MAVERICK_MTP_FLAME_GEYSER);
	else if (number == 5)
		ft_printf("%s\n", MAVERICK_MTP_FROST_BREATH);
	else if (number == 6)
		ft_printf("%s\n", MAVERICK_MTP_LIGHTNING_STRIKE_V2);
	else if (number == 7)
		ft_printf("%s\n", MAVERICK_MTP_ARCANE_POUNCE);
	else if (number == 8)
		ft_printf("%s\n", MAVERICK_MTP_EARTH_POUNCE);
}

void ft_maverick_print_f(int first, int second, t_char *info)
{
	if (first == 1)
	{
		ft_printf("%s\n", MAVERICK_MASS_TELEPORT);
		ft_maverick_print_tp(second);
	}
	else if (first == 2)
		ft_printf("%s\n", MAVERICK_METEOR_STRIKE);
	else if (first == 3)
	{
		ft_maverick_lightning_strike(info);
		ft_printf("%s\n", MAVERICK_LIGHTNING_STRIKE);
	}
	else if (first == 4)
		ft_printf("%s\n", MAVERICK_FLAME_GEYSER);
	else if (first == 5)
		ft_printf("%s\n", MAVERICK_FORST_BREATH);
	else if (first == 6)
	{
		ft_maverick_lightningV2_strike(info);
		ft_printf("%s\n", MAVERICK_LIGHTNING_STRIKE_V2);
	}
	else if (first == 7)
		ft_printf("%s\n", MAVERICK_ARCANE_POUNCE);
	else if (first == 8)
		ft_printf("%s\n", MAVERICK_EARTH_POUNCE);
}

void	ft_maverick_print_s(int first, int second, t_char *info)
{
	if (second == 1)
	{
		ft_printf("%s\n", MAVERICK_MASS_TELEPORT);
		ft_maverick_print_tp(first);
	}
	else if (second == 2)
		ft_printf("%s\n", MAVERICK_METEOR_STRIKE);
	else if (second == 3)
	{
		ft_maverick_lightning_strike(info);
		ft_printf("%s\n", MAVERICK_LIGHTNING_STRIKE);
	}
	else if (second == 4)
		ft_printf("%s\n", MAVERICK_FLAME_GEYSER);
	else if (second == 5)
		ft_printf("%s\n", MAVERICK_FORST_BREATH);
	else if (second == 6)
	{
		ft_maverick_lightningV2_strike(info);
		ft_printf("%s\n", MAVERICK_LIGHTNING_STRIKE_V2);
	}
	else if (second == 7)
		ft_printf("%s\n", MAVERICK_ARCANE_POUNCE);
	else if (second == 8)
		ft_printf("%s\n", MAVERICK_EARTH_POUNCE);
}
