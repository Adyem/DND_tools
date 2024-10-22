#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "dnd_tools.hpp"

void ft_update_lightning_strike(t_char *info)
{
    int result;

    if (info->bufs.lightning_strike.dice_amount <= 0 ||
        info->bufs.lightning_strike.dice_faces <= 0 ||
        info->bufs.lightning_strike.distance <= 0)
        return ;
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
        return ;
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
        ft_printf("%s is preparing a lightning strike that will unleash on the next turn.\n",
                  info->name);
    else
        ft_printf("%s's lightning strike will unleash in %d turns.\n",
                  info->name, info->bufs.lightning_strikeV2.duration);
    return ;
}

void ft_update_flame_geyser(t_char *info)
{
    if (info->bufs.flame_geyser.duration <= 0 ||
        info->bufs.flame_geyser.close_to_tower_d <= 0 ||
        info->bufs.flame_geyser.tower_explode_d <= 0)
        return;
    info->bufs.flame_geyser.duration--;
    if (info->bufs.flame_geyser.duration == 0)
    {
        ft_printf("Flame geyser explode this turn: \n");
		ft_printf("Everyone under a flame geyser takes %i damage\n",
				info->bufs.flame_geyser.close_to_tower_d);
		ft_printf("If a tower has no player under it it explodes dealing %i damage " \
				"to all players\n", info->bufs.flame_geyser.tower_explode_d);
    }
    else if (info->bufs.flame_geyser.duration == 1)
        ft_printf("Flame Geyser will explode on the boss's next turn.\n");
    else
       ft_printf("Flame Geyser will explode in %d turns.\n",
			   info->bufs.flame_geyser.duration);
}

void ft_update_meteor_strike(t_char *info)
{
	const char *target;

	if (info->bufs.meteor_strike.duration <= 0 ||
        info->bufs.meteor_strike.one_target_d < 0 ||
        info->bufs.meteor_strike.two_targets_d < 0 ||
        info->bufs.meteor_strike.three_targets_d < 0 ||
        info->bufs.meteor_strike.four_targets_d < 0 ||
        info->bufs.meteor_strike.five_targets_d < 0)
        return;
	info->bufs.meteor_strike.duration--;
	if (info->bufs.meteor_strike.target_id)
		target = info->bufs.meteor_strike.target_id;
	else
		target = "the target";
	if (info->bufs.meteor_strike.duration == 0)
	{
        ft_printf("The Meteor above %s lands, dealing damage depending on the total " \
				"amount of players in the area.\n", target);
        ft_printf("If 5 or more players were hit, they each take %i damage.\n",
				info->bufs.meteor_strike.five_targets_d);
        ft_printf("If 4 players were hit, they each take %i damage.\n",
				info->bufs.meteor_strike.four_targets_d);
        ft_printf("If 3 players were hit, they each take %i damage.\n",
				info->bufs.meteor_strike.three_targets_d);
        ft_printf("If 2 players were hit, they each take %i damage.\n",
				info->bufs.meteor_strike.two_targets_d);
        ft_printf("If 1 player was hit, he/she takes %i damage.\n",
				info->bufs.meteor_strike.one_target_d);
	}
	else if (info->bufs.meteor_strike.duration == 1)
        ft_printf("Meteor Strike will impact on the boss's next turn.\n");
	else
        ft_printf("Meteor Strike will impact in %d turns.\n",
				info->bufs.meteor_strike.duration);
	cma_free(info->bufs.meteor_strike.target_id);
	info->bufs.meteor_strike.target_id = nullptr;
}

void ft_update_earth_pounce(t_char *info)
{
	const char *target;

	if (info->bufs.earth_pounce.active != 1 ||
        info->bufs.earth_pounce.base_damage < 0)
        return;
	if (info->bufs.earth_pounce.target_id)
		target = info->bufs.earth_pounce.target_id;
	else
		target = "the target";
    info->bufs.earth_pounce.active = 0;
    ft_printf("%s will jump towards %s and pounce, dealing %i damage reduced by the " \
			"total AC of the target.\n", target, info->name, info->bufs.earth_pounce.base_damage);
	cma_free(info->bufs.earth_pounce.target_id);
	info->bufs.earth_pounce.target_id = nullptr;
	return ;
}

void ft_update_arcane_pounce(t_char *info)
{
	const char *target;

	if (info->bufs.arcane_pounce.active != 1 ||
        info->bufs.arcane_pounce.erea_damage < 0 ||
        info->bufs.arcane_pounce.magic_damage < 0)
        return ;
	info->bufs.arcane_pounce.active = 0;
	if (info->bufs.arcane_pounce.target_id)
		target = info->bufs.arcane_pounce.target_id;
	else
		target = "the target";
	ft_printf("%s will jump towards %s and pounce, dealing ", target, info->name);
    ft_printf("%i damage and %i damage to anyone within 10ft.\n",
              info->bufs.arcane_pounce.magic_damage, info->bufs.arcane_pounce.erea_damage);
	cma_free(info->bufs.arcane_pounce.target_id);
	info->bufs.arcane_pounce.target_id = nullptr;
    return ;
}

void ft_update_frost_breath(t_char *info)
{
	if (info->bufs.frost_breath.active != 1 ||
        info->bufs.frost_breath.damage < 0)
        return ;
    ft_printf("The boss breathes out dealing %s damage to annyone in a 90% degree " \
			"in front of him\n", info->bufs.frost_breath.damage);
	info->bufs.frost_breath.active = 0;
	info->bufs.frost_breath.damage = 0;
	cma_free(info->bufs.frost_breath.target_id);
	info->bufs.frost_breath.target_id = nullptr;
    return ;
}
