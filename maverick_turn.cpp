#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "maverick.hpp"
#include "libft/Printf/ft_printf.hpp"
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

static char **ft_maverick_choose_target()
{
    char **temp;
    char **content;
    int fd;
    int length;
    int result;

    fd = open("data/data--initiative", O_RDONLY);
    if (fd == -1)
    {
        ft_printf("280-Error opening file: %s\n", strerror(errno));
        return (NULL);
    }
    content = ft_read_file_dnd(fd);
    close(fd);
    if (!content)
    {
        ft_printf("281-Error opening file: %s\n", strerror(errno));
        return (NULL);
    }
    length = ft_double_char_length(content);
    result = -1;
    while (result == -1 || (ft_strncmp(content[result], "PC--", 4) != 0
                && ft_strncmp(content[result], "--turn--PC--", 12) != 0))
    {
        result = ft_dice_roll(1, length) - 1;
        if (DEBUG == 1)
            ft_printf("result = %d\n", result);
    }
	temp = (char **)cma_malloc(sizeof(char *), false);
	if (!temp)
		return (NULL);
    *temp = ft_strchr(content[result], '=');
    if (*temp)
        *temp = cma_strdup(*temp, false);
    return (temp);
}

static void	ft_maverick_lightning_strike(t_char *info)
{
	info->bufs.lightning_strike.amount = 3;
	info->bufs.lightning_strike.duration = 1;
	info->bufs.lightning_strike.dice_amount = 1;
	info->bufs.lightning_strike.dice_faces = 8;
	info->bufs.lightning_strike.distance = 5;
	return ;
}

static void	ft_maverick_lightningV2_strike(t_char *info)
{
	info->bufs.lightning_strikeV2.duration = 1;
	info->bufs.lightning_strikeV2.dice_amount = 2;
	info->bufs.lightning_strikeV2.dice_faces = 8;
	info->bufs.lightning_strikeV2.distance = 5;
	return ;
}

static void	ft_maverick_flame_geyser(t_char *info)
{
	info->bufs.flame_geyser.amount = 2;
	info->bufs.flame_geyser.duration = 1;
	info->bufs.flame_geyser.tower_explode_d = 10;
	info->bufs.flame_geyser.close_to_tower_d = 3;
	return ;
}

static void ft_maverick_meteor_strike(t_char *info)
{
	info->bufs.meteor_strike.target_id = ft_maverick_choose_target();
	info->bufs.meteor_strike.duration = 1;
	info->bufs.meteor_strike.one_target_d = 22;
	info->bufs.meteor_strike.two_targets_d = 10;
	info->bufs.meteor_strike.three_targets_d = 16;
	info->bufs.meteor_strike.four_targets_d = 4;
	info->bufs.meteor_strike.five_targets_d = 3;
	return ;
}

static void	ft_maverick_earth_pounce(t_char *info)
{
	info->bufs.earth_pounce.target_id = ft_maverick_choose_target();
	info->bufs.earth_pounce.active = 1;
	info->bufs.earth_pounce.base_damage = 27;
	return ;
}

static void	ft_maverick_arcane_pounce(t_char *info)
{
	info->bufs.arcane_pounce.target_id = ft_maverick_choose_target();
	info->bufs.arcane_pounce.active = 1;
	info->bufs.arcane_pounce.erea_damage = 8;
	info->bufs.arcane_pounce.magic_damage = 4;
	return ;
}

static void print_meteor_strike(const t_char *info)
{
    ft_printf("Meteor Strike: Create a circle around the target with arrows pointing towards the center (10ft radius), ");
    ft_printf("at the start of the next turn a meteor hits the target dealing damage dependent on the number of targets hit.\n");
    ft_printf("(Cannot be the same target as Arcane Pounce or Earth Pounce)\n");
    ft_printf("1 target\t\t%d fire damage\n", info->bufs.meteor_strike.one_target_d);
    ft_printf("2 targets\t\t%d fire damage each\n", info->bufs.meteor_strike.two_targets_d);
    ft_printf("3 targets\t\t%d fire damage each\n", info->bufs.meteor_strike.three_targets_d);
    ft_printf("4 or more targets\t%d fire damage each\n", info->bufs.meteor_strike.four_targets_d);
	return ;
}

static void print_lightning_strike(const t_char *info)
{
    ft_printf("Lightning Strike: The boss's skin will flare with electricity at the start of the boss's next turn ");
    ft_printf("and will deal %d lightning damage to anyone within %d ft.\n", 
              info->bufs.lightning_strike.amount * 4,
              info->bufs.lightning_strike.distance);
	return ;
}

static void print_flame_geyser(const t_char *info)
{
    ft_printf("Flame Geyser: %d red towers spawn at random locations. If no one stands underneath a tower at the start of the boss's next turn, ");
    ft_printf("it will explode, dealing %d fire damage to every member in the party. If one or more players stand ");
    ft_printf("underneath a tower, it deals %d fire damage to each of those players.\n", 
              info->bufs.flame_geyser.amount * 3,
              info->bufs.flame_geyser.close_to_tower_d);
    ft_printf("(Be careful with placement on the flame geyser’s so they don’t appear in areas where other abilities are going to hit)\n");
	return ;
}

static void print_frost_breath(const t_char *info)
{
    ft_printf("Frost Breath: The boss takes a deep breath and breathes out, dealing %d cold damage to anyone in a 90-degree cone in front of him.\n", 
              info->bufs.flame_geyser.amount * 6);
    ft_printf("(Be clear about what way the boss is facing when he starts casting the ability)\n");
	return ;
}

static void print_lightning_strike_v2(const t_char *info)
{
    ft_printf("Lightning Strike V2: A marker appears at a random location, indicating where lightning will strike.\n");
    ft_printf("At the start of the boss's next turn, it deals %d lightning damage to everyone, reduced by 2 for each 5ft of distance from the marker up to a minimum of %d.\n",
              info->bufs.lightning_strikeV2.dice_amount * 6,
              info->bufs.lightning_strikeV2.distance);
    ft_printf("(Be careful with placement on Lightning Strike V2 so it isn’t on top of flame geysers)\n");
	return ;
}

static void print_arcane_pounce(const t_char *info)
{
    ft_printf("Arcane Pounce: Targets a random player. At the start of the boss's next turn, ");
    ft_printf("leaps to that player, landing in front of them and pounces, dealing %d magic damage and %d magic damage to anyone within 5ft.\n",
              info->bufs.arcane_pounce.magic_damage, 
              info->bufs.arcane_pounce.erea_damage);
    ft_printf("(Cannot be the same target as Meteor Strike or Earth Pounce)\n");
	return ;
}

static void print_earth_pounce(const t_char *info)
{
    ft_printf("Earth Pounce: Targets the player with the highest Armor Class (AC). ");
    ft_printf("At the start of the boss's next turn, jumps towards the target and deals %d bludgeoning damage reduced by 1 for each AC the target has.\n",
              info->bufs.earth_pounce.base_damage);
    ft_printf("(Cannot be the same target as Meteor Strike or Arcane Pounce)\n");
	return ;
}

static void print_mass_teleport(int tp_number)
{
    ft_printf("Mass Teleport: Teleport all players to random locations across the arena depending on what ability it is paired with.\n");    
	if (tp_number == 2)
        ft_printf("Teleportation Type: Meteor Strike - Spreading players 20ft-60ft. away from one another.\n");
	else if (tp_number == 3)
        ft_printf("Teleportation Type: Lightning Strike - Teleporting the players close to the boss.\n");
	else if (tp_number == 4)
        ft_printf("Teleportation Type: Flame Geyser - Teleporting the players to random locations 30-60ft. away from the flame geysers.\n");
	else if (tp_number == 5)
        ft_printf("Teleportation Type: Frost Breath - Teleporting all players in front of the boss.\n");
	else if (tp_number == 6)
        ft_printf("Teleportation Type: Lightning Strike V2 - Teleporting all players to the marker.\n");
	else if (tp_number == 7)
        ft_printf("Teleportation Type: Arcane Pounce - Teleporting all players around the target.\n");
	else if (tp_number == 8)
        ft_printf("Teleportation Type: Earth Pounce - Teleporting all players around the target.\n");
	else
        ft_printf("Unknown Teleportation Type.\n");
	return ;
}

void ft_maverick_print_f(int first, int second, t_char *info)
{
    if (first == 1)
        print_mass_teleport(second);
    else if (first == 2)
	{
		ft_maverick_meteor_strike(info);
        print_meteor_strike(info);
	}
    else if (first == 3)
	{
        ft_maverick_lightning_strike(info);
        print_lightning_strike(info);
    }
    else if (first == 4)
	{
		ft_maverick_flame_geyser(info);
        print_flame_geyser(info);
	}
    else if (first == 5)
        print_frost_breath(info);
    else if (first == 6)
	{
        ft_maverick_lightningV2_strike(info);
        print_lightning_strike_v2(info);
    }
    else if (first == 7)
	{
		ft_maverick_arcane_pounce(info);
		print_arcane_pounce(info);
	}
    else if (first == 8)
	{
		ft_maverick_earth_pounce(info);
        print_earth_pounce(info);
	}
	return ;
}

void ft_maverick_print_s(int first, int second, t_char *info)
{
    if (second == 1)
        print_mass_teleport(first);
    else if (second == 2)
	{
		ft_maverick_meteor_strike(info);
        print_meteor_strike(info);
	}
    else if (second == 3)
	{
        ft_maverick_lightning_strike(info);
        print_lightning_strike(info);
    }
    else if (second == 4)
	{
		ft_maverick_flame_geyser(info);
        print_flame_geyser(info);
	}
    else if (second == 5)
        print_frost_breath(info);
    else if (second == 6)
	{
        ft_maverick_lightningV2_strike(info);
        print_lightning_strike_v2(info);
    }
    else if (second == 7)
	{
		ft_maverick_arcane_pounce(info);
        print_arcane_pounce(info);
	}
    else if (second == 8)
	{
		ft_maverick_earth_pounce(info);
        print_earth_pounce(info);
	}
	return ;
}
