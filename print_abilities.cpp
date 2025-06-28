#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void print_meteor_strike(const t_char * info)
{
	const char *target;

	if (info->bufs.meteor_strike.target_id)
		target = info->bufs.meteor_strike.target_id;
	else
		target = "the target";
    pf_printf("Meteor Strike: Create a circle around %s with arrows " \
			"pointing towards the center (10ft radius)", target);
    pf_printf("at the start of the next turn a meteor hits the target dealing " \
			"damage dependent on the number of targets hit.\n");
    pf_printf("(Cannot be the same target as Arcane Pounce or Earth Pounce)\n");
    pf_printf("1 target\t\t%d fire damage\n", info->bufs.meteor_strike.one_target_d);
    pf_printf("2 targets\t\t%d fire damage each\n", info->bufs.meteor_strike.two_targets_d);
    pf_printf("3 targets\t\t%d fire damage each\n", info->bufs.meteor_strike.three_targets_d);
    pf_printf("4 or more targets\t%d fire damage each\n", info->bufs.meteor_strike.four_targets_d);
	return ;
}

void print_lightning_strike(const t_char * info)
{
    pf_printf("Lightning Strike: The boss's skin will flare with electricity at " \
			"the start of the boss's next turn ");
    pf_printf("and will deal %d lightning damage to anyone within %d ft.\n", 
              info->bufs.lightning_strike.amount * 4,
              info->bufs.lightning_strike.distance);
	return ;
}

void print_flame_geyser(const t_char * info)
{
    pf_printf("Flame Geyser: %d red towers spawn at random locations. If no one " \
			"stands underneath a tower at the start of the boss's next turn, it " \
			"will explode, dealing %d fire damage to every member in the " \
			"party. If one or more players stand underneath a tower, it deals %d " \
			"fire damage to each of those players.\n", 
              info->bufs.flame_geyser.amount, info->bufs.flame_geyser.tower_explode_d,
			  info->bufs.flame_geyser.close_to_tower_d);
    pf_printf("(Be careful with placement on the flame geyser’s so they don’t " \
			"appear in areas where other abilities are going to hit)\n");
	return ;
}

void print_frost_breath(const t_char * info)
{
	const char *target;

	if (info->bufs.frost_breath.target_id)
		target = info->bufs.frost_breath.target_id;
	else
		target = "a random target";
    pf_printf("Frost Breath: The boss looks at %s and takes a deep breath and breathes " \
			"out on its next turn, dealing %i cold damage to anyone in a 90-degree "
			"cone in front of him.\n", target, info->bufs.frost_breath.damage);
    pf_printf("(Be clear about what way the boss is facing when " \
			"he starts casting the ability)\n");
	return ;
}

void print_lightning_strike_v2(const t_char * info)
{
    pf_printf("Lightning Strike V2: A marker appears at a random location, " \
			"indicating where lightning will strike.\n");
    pf_printf("At the start of the boss's next turn, it deals %d lightning " \
			"damage to everyone, reduced by 2 for each 5ft of distance " \
			"from the marker up to a minimum of %d.\n",
              info->bufs.lightning_strikeV2.dice_amount * 6,
              info->bufs.lightning_strikeV2.distance);
    pf_printf("(Be careful with placement on Lightning Strike V2 so it isn’t " \
			"on top of flame geysers)\n");
	return ;
}

void print_arcane_pounce(const t_char * info)
{
	const char *target;

	if (info->bufs.arcane_pounce.target_id)
		target = info->bufs.arcane_pounce.target_id;
	else
		target = "the target";
    pf_printf("Arcane Pounce: Targets a random player. At the start of the boss's next turn, ");
    pf_printf("leaps to %s, landing in front of him/her and pounces, " \
			"dealing %d magic damage and %d magic damage to anyone within 5ft.\n",
            target, info->bufs.arcane_pounce.magic_damage, info->bufs.arcane_pounce.erea_damage);
	return ;
}

void print_earth_pounce(const t_char * info)
{
	const char *target;

	if (info->bufs.earth_pounce.target_id)
		target = info->bufs.earth_pounce.target_id;
	else
		target = "the target";
        pf_printf("Earth Pounce: Targets the player with the highest Armor Class (AC). ");
    pf_printf("At the start of the boss's next turn, jumps towards the %s " \
                        "and deals %d bludgeoning damage reduced by 1 for each AC the %s has.\n",
            target, info->bufs.earth_pounce.base_damage, target);
        return ;
}

void print_shadow_illusion(const t_char * info)
{
    pf_printf("Shadow Illusion: Xavius creates an illusory copy of himself for %d turn(s).\n",
              info->bufs.shadow_illusion.duration);
    pf_printf("The next attack against him has a 50%% chance to strike the illusion instead.\n");
    return ;
}
