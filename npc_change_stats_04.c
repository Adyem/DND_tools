#include "dnd_tools.h"

static void	ft_deal_damage(t_char *info, char **input, char *d_type, int resistance)
{
	int	temp;
	int	damage;
	int	extra;

	if (ft_check_value(input[1]))
	{
		ft_printf_fd(2, "1-Damage: expecting a number higher then or equal to 0\n");
		return ;
	}
	damage = ft_atoi(input[1]);
	if (damage < 0)
	{
		ft_printf_fd(2, "2-Damage: expecting a number higher then or equal to 0\n");
		return ;
	}
	if (d_type && resistance > 0)
	{
		extra = damage * (resistance / 100);
		ft_printf("%s is resistant to %s damage and takes %i%% less damage" \
			" for a total of less damage%i\n",
			info->name, d_type, resistance, extra);
		damage = damage - extra;
	}
	else if (d_type && resistance < 0)
	{
		extra = damage * ((resistance * -1) / 100);
		ft_printf("%s is vulnerable to %s damage and takes %i%% more damage" \
			" for a total of %i more damag e\n",
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
	ft_print_character_status(info, damage * -1, temp);
}

void	ft_change_stats_04(t_char *info, char **input)
{
	if (ft_strcmp_dnd(input[3], "damage") == 0)
	{
		if (info->version_number < 2)
			ft_deal_damage(info, input, NULL, 0);
		else if (ft_strcmp_dnd(input[2], "acid") == 0)
			ft_deal_damage(info, input, "acid", info->c_resistance.acid);
		else if (ft_strcmp_dnd(input[2], "bludgeoning") == 0)
			ft_deal_damage(info, input, "bludgeoning", info->c_resistance.bludgeoning);
		else if (ft_strcmp_dnd(input[2], "cold") == 0)
			ft_deal_damage(info, input, "cold", info->c_resistance.cold);
		else if (ft_strcmp_dnd(input[2], "fire") == 0)
			ft_deal_damage(info, input, "fire", info->c_resistance.fire);
		else if (ft_strcmp_dnd(input[2], "force") == 0)
			ft_deal_damage(info, input, "force", info->c_resistance.force);
		else if (ft_strcmp_dnd(input[2], "lightning") == 0)
			ft_deal_damage(info, input, "lightning", info->c_resistance.lightning);
		else if (ft_strcmp_dnd(input[2], "necrotic") == 0)
			ft_deal_damage(info, input, "necrotic", info->c_resistance.necrotic);
		else if (ft_strcmp_dnd(input[2], "piercing") == 0)
			ft_deal_damage(info, input, "piercing", info->c_resistance.piercing);
		else if (ft_strcmp_dnd(input[2], "poison") == 0)
			ft_deal_damage(info, input, "poison", info->c_resistance.poison);
		else if (ft_strcmp_dnd(input[2], "psychic") == 0)
			ft_deal_damage(info, input, "psychic", info->c_resistance.psychic);
		else if (ft_strcmp_dnd(input[2], "radiant") == 0)
			ft_deal_damage(info, input, "radiant", info->c_resistance.radiant);
		else if (ft_strcmp_dnd(input[2], "slashing") == 0)
			ft_deal_damage(info, input, "slashing", info->c_resistance.slashing);
		else if (ft_strcmp_dnd(input[2], "thunder") == 0)
			ft_deal_damage(info, input, "thunder", info->c_resistance.thunder);
    }
}
