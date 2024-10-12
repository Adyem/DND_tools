#include "libft/Printf/ft_printf.hpp"
#include "dnd_tools.hpp"

void ft_update_lightning_strike(t_char *info)
{
    int result;

    if (info->bufs.lightning_strike.dice_amount <= 0 ||
        info->bufs.lightning_strike.dice_faces <= 0 ||
        info->bufs.lightning_strike.distance <= 0)
        return;
    info->bufs.lightning_strike.duration--;

    if (info->bufs.lightning_strike.duration == 0)
    {
        result = ft_dice_roll(1, 8) + info->bufs.lightning_strike.extra_damage;
        ft_printf("%s his lightning strike markers explode dealing %d " \
				"lightning damage to anyone standing within %d ft.\n",
                info->name, result, info->bufs.lightning_strike.distance);
    }
    else if (info->bufs.lightning_strike.duration == 1)
        ft_printf("%s his lightning strike markers will explode on his next turn\n",
				info->name);
    else
        ft_printf("%s his lightning strike markers will explode in %d turns\n",
                  info->name, info->bufs.lightning_strike.duration);

    return ;
}

void ft_update_lightningV2_strike(t_char *info)
{
    int result;

    if (info->bufs.lightning_strikeV2.dice_amount <= 0 ||
        info->bufs.lightning_strikeV2.dice_faces <= 0 ||
        info->bufs.lightning_strikeV2.distance <= 0)
        return;
    info->bufs.lightning_strikeV2.duration--;
    if (info->bufs.lightning_strikeV2.duration == 0)
    {
        result = ft_dice_roll(info->bufs.lightning_strikeV2.dice_amount, 
                              info->bufs.lightning_strikeV2.dice_faces) 
                 + info->bufs.lightning_strikeV2.extra_damage;
        ft_printf("%s unleashes a lightning strike, dealing %d lightning damage "
                  "to all foes within %d ft.\n",
                  info->name, result, info->bufs.lightning_strikeV2.distance);
    }
    else if (info->bufs.lightning_strikeV2.duration == 1)
    {
        ft_printf("%s is preparing a lightning strike that will unleash on the next turn.\n",
                  info->name);
    }
    else
    {
        ft_printf("%s's lightning strike will unleash in %d turns.\n",
                  info->name, info->bufs.lightning_strikeV2.duration);
    }
    return;
}
