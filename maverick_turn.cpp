#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "maverick.hpp"
#include "libft/Printf/printf.hpp"
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

static void	ft_maverick_lightning_strike(SharedPtr<t_char> info)
{
	info->bufs.lightning_strike.amount = 3;
	info->bufs.lightning_strike.duration = 1;
	info->bufs.lightning_strike.dice_amount = 1;
	info->bufs.lightning_strike.dice_faces = 8;
	info->bufs.lightning_strike.distance = 5;
	print_lightning_strike(info);
	return ;
}

static void	ft_maverick_lightningV2_strike(SharedPtr<t_char> info)
{
	info->bufs.lightning_strikeV2.duration = 1;
	info->bufs.lightning_strikeV2.dice_amount = 2;
	info->bufs.lightning_strikeV2.dice_faces = 8;
	info->bufs.lightning_strikeV2.distance = 5;
	print_lightning_strike_v2(info);
	return ;
}

static void	ft_maverick_flame_geyser(SharedPtr<t_char> info)
{
	info->bufs.flame_geyser.amount = 2;
	info->bufs.flame_geyser.duration = 1;
	info->bufs.flame_geyser.tower_explode_d = 10;
	info->bufs.flame_geyser.close_to_tower_d = 3;
	print_flame_geyser(info);
	return ;
}

static void ft_maverick_meteor_strike(SharedPtr<t_char> info, char **player_list)
{
	cma_free(info->bufs.meteor_strike.target_id);
	info->bufs.meteor_strike.target_id = ft_nullptr;
	ft_get_random_target(player_list, &info->bufs.meteor_strike.target_id);
	info->bufs.meteor_strike.duration = 1;
	info->bufs.meteor_strike.one_target_d = 22;
	info->bufs.meteor_strike.two_targets_d = 10;
	info->bufs.meteor_strike.three_targets_d = 16;
	info->bufs.meteor_strike.four_targets_d = 4;
	info->bufs.meteor_strike.five_targets_d = 3;
	print_meteor_strike(info);
	return ;
}

static void	ft_maverick_earth_pounce(SharedPtr<t_char> info, char **player_list)
{
	cma_free(info->bufs.earth_pounce.target_id);
	info->bufs.earth_pounce.target_id = ft_nullptr;
	ft_get_random_target(player_list, &info->bufs.earth_pounce.target_id);
	info->bufs.earth_pounce.active = 1;
	info->bufs.earth_pounce.base_damage = 27;
	print_earth_pounce(info);
	return ;
}

static void	ft_maverick_arcane_pounce(SharedPtr<t_char> info, char **player_list)
{
	cma_free(info->bufs.frost_breath.target_id);
	info->bufs.frost_breath.target_id = ft_nullptr;
	ft_get_random_target(player_list, &info->bufs.arcane_pounce.target_id);
	info->bufs.arcane_pounce.active = 1;
	info->bufs.arcane_pounce.erea_damage = 8;
	info->bufs.arcane_pounce.magic_damage = 4;
	print_arcane_pounce(info);
	return ;
}

static void	ft_maverick_frost_breath(SharedPtr<t_char> info, char **player_list)
{
	cma_free(info->bufs.frost_breath.target_id);
	info->bufs.frost_breath.target_id = ft_nullptr;
	ft_get_random_target(player_list, &info->bufs.frost_breath.target_id);
	info->bufs.frost_breath.active = 1;
	info->bufs.frost_breath.damage = 25;
	print_frost_breath(info);
	return ;
}

static void print_mass_teleport(int tp_number)
{
    pf_printf("Mass Teleport: Teleport all players to random locations " \
			"across the arena depending on what ability it is paired with.\n");    
	if (tp_number == 2)
        pf_printf("Teleportation Type: Meteor Strike - Spreading " \
				"players 20ft-60ft. away from one another.\n");
	else if (tp_number == 3)
        pf_printf("Teleportation Type: Lightning Strike - Teleporting " \
				"the players close to the boss.\n");
	else if (tp_number == 4)
        pf_printf("Teleportation Type: Flame Geyser - Teleporting the " \
				"players to random locations 30-60ft. away from the flame geysers.\n");
	else if (tp_number == 5)
        pf_printf("Teleportation Type: Frost Breath - Teleporting all " \
				"players in front of the boss.\n");
	else if (tp_number == 6)
        pf_printf("Teleportation Type: Lightning Strike V2 - Teleporting " \
				"all players to the marker.\n");
	else if (tp_number == 7)
        pf_printf("Teleportation Type: Arcane Pounce - Teleporting all " \
				"players around the target.\n");
	else if (tp_number == 8)
        pf_printf("Teleportation Type: Earth Pounce - Teleporting all " \
				"players around the target.\n");
	return ;
}

void ft_maverick_print_f(int first, int second, SharedPtr<t_char> info, char **player_list)
{
    if (first == 1)
        print_mass_teleport(second);
    else if (first == 2)
		ft_maverick_meteor_strike(info, player_list);
    else if (first == 3)
        ft_maverick_lightning_strike(info);
    else if (first == 4)
		ft_maverick_flame_geyser(info);
    else if (first == 5)
        ft_maverick_frost_breath(info, player_list);
    else if (first == 6)
        ft_maverick_lightningV2_strike(info);
    else if (first == 7)
		ft_maverick_arcane_pounce(info, player_list);
    else if (first == 8)
		ft_maverick_earth_pounce(info, player_list);
	return ;
}

void ft_maverick_print_s(int first, int second, SharedPtr<t_char> info, char **player_list)
{
    if (second == 1)
        print_mass_teleport(first);
    else if (second == 2)
		ft_maverick_meteor_strike(info, player_list);
    else if (second == 3)
        ft_maverick_lightning_strike(info);
    else if (second == 4)
		ft_maverick_flame_geyser(info);
    else if (second == 5)
        ft_maverick_frost_breath(info, player_list);
    else if (second == 6)
        ft_maverick_lightningV2_strike(info);
    else if (second == 7)
		ft_maverick_arcane_pounce(info, player_list);
    else if (second == 8)
		ft_maverick_earth_pounce(info, player_list);
	return ;
}
