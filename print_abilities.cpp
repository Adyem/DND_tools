#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"

void print_meteor_strike(const t_char *info)
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

void print_lightning_strike(const t_char *info)
{
    ft_printf("Lightning Strike: The boss's skin will flare with electricity at the start of the boss's next turn ");
    ft_printf("and will deal %d lightning damage to anyone within %d ft.\n", 
              info->bufs.lightning_strike.amount * 4,
              info->bufs.lightning_strike.distance);
	return ;
}

void print_flame_geyser(const t_char *info)
{
    ft_printf("Flame Geyser: %d red towers spawn at random locations. If no one stands underneath a tower at the start of the boss's next turn, ");
    ft_printf("it will explode, dealing %d fire damage to every member in the party. If one or more players stand ");
    ft_printf("underneath a tower, it deals %d fire damage to each of those players.\n", 
              info->bufs.flame_geyser.amount * 3,
              info->bufs.flame_geyser.close_to_tower_d);
    ft_printf("(Be careful with placement on the flame geyser’s so they don’t appear in areas where other abilities are going to hit)\n");
	return ;
}

void print_frost_breath(const t_char *info)
{
	(void)info;
    ft_printf("Frost Breath: The boss takes a deep breath and breathes out, dealing 20 cold damage to anyone in a 90-degree cone in front of him.\n");
    ft_printf("(Be clear about what way the boss is facing when he starts casting the ability)\n");
	return ;
}

void print_lightning_strike_v2(const t_char *info)
{
    ft_printf("Lightning Strike V2: A marker appears at a random location, indicating where lightning will strike.\n");
    ft_printf("At the start of the boss's next turn, it deals %d lightning damage to everyone, reduced by 2 for each 5ft of distance from the marker up to a minimum of %d.\n",
              info->bufs.lightning_strikeV2.dice_amount * 6,
              info->bufs.lightning_strikeV2.distance);
    ft_printf("(Be careful with placement on Lightning Strike V2 so it isn’t on top of flame geysers)\n");
	return ;
}

void print_arcane_pounce(const t_char *info)
{
    ft_printf("Arcane Pounce: Targets a random player. At the start of the boss's next turn, ");
    ft_printf("leaps to that player, landing in front of them and pounces, dealing %d magic damage and %d magic damage to anyone within 5ft.\n",
              info->bufs.arcane_pounce.magic_damage, 
              info->bufs.arcane_pounce.erea_damage);
    ft_printf("(Cannot be the same target as Meteor Strike or Earth Pounce)\n");
	return ;
}

void print_earth_pounce(const t_char *info)
{
    ft_printf("Earth Pounce: Targets the player with the highest Armor Class (AC). ");
    ft_printf("At the start of the boss's next turn, jumps towards the target and deals %d bludgeoning damage reduced by 1 for each AC the target has.\n",
              info->bufs.earth_pounce.base_damage);
    ft_printf("(Cannot be the same target as Meteor Strike or Arcane Pounce)\n");
	return ;
}
