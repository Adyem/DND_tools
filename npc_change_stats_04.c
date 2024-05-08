#include "dnd_tools.h"

void	ft_deal_damage(t_char *info, char *input, char *d_type, int resistance,
		int concentration)
{
	static int	total;
	int			temp;
	int			damage;
	int			extra;

	if (concentration == 1 || concentration == 0)
	{
		if (ft_check_value(input))
		{
			ft_printf_fd(2, "1-Damage: expecting a number higher then or equal to 0\n");
			return ;
		}
		damage = ft_atoi(input);
		if (damage < 0)
		{
			ft_printf_fd(2, "2-Damage: expecting a number higher then or equal to 0\n");
			return ;
		}
		if (d_type && resistance > 0)
		{
			extra = damage * (resistance / 100);
			ft_printf("%s is resistant to %s damage and takes %i%% less damage" \
				" for a total of %i less damage\n",
				info->name, d_type, resistance, extra);
			damage = damage - extra;
		}
		else if (d_type && resistance < 0)
		{
			extra = damage * ((resistance * -1) / 100);
			ft_printf("%s is vulnerable to %s damage and takes %i%% more damage" \
				" for a total of %i more damage\n",
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
		if (info->stats.health < 0)
			info->stats.health = 0;
		total += damage;
		ft_print_character_status(info, damage * -1, temp);
	}
	if (concentration == 1 || concentration == 2)
	{
		if (info->concentration.concentration)
			ft_check_concentration(info, total);
		total = 0;
	}
	return ;
}

void	ft_change_stats_04(t_char *info, char **input)
{
	if (ft_strcmp_dnd(input[3], "damage") == 0)
	{
		if (info->version_number < 2)
			ft_deal_damage(info, input[1], NULL, 0, 1);
		else if (ft_strcmp_dnd(input[2], "acid") == 0)
			ft_deal_damage(info, input[1], "acid", info->c_resistance.acid, 1);
		else if (ft_strcmp_dnd(input[2], "bludgeoning") == 0)
			ft_deal_damage(info, input[1], "bludgeoning", info->c_resistance.bludgeoning, 1);
		else if (ft_strcmp_dnd(input[2], "cold") == 0)
			ft_deal_damage(info, input[1], "cold", info->c_resistance.coldn, 1);
		else if (ft_strcmp_dnd(input[2], "fire") == 0)
			ft_deal_damage(info, input[1], "fire", info->c_resistance.fire, 1);
		else if (ft_strcmp_dnd(input[2], "force") == 0)
			ft_deal_damage(info, input[1], "force", info->c_resistance.force, 1);
		else if (ft_strcmp_dnd(input[2], "lightning") == 0)
			ft_deal_damage(info, input[1], "lightning", info->c_resistance.lightning, 1);
		else if (ft_strcmp_dnd(input[2], "necrotic") == 0)
			ft_deal_damage(info, input[1], "necrotic", info->c_resistance.necrotic, 1);
		else if (ft_strcmp_dnd(input[2], "piercing") == 0)
			ft_deal_damage(info, input[1], "piercing", info->c_resistance.piercing, 1);
		else if (ft_strcmp_dnd(input[2], "poison") == 0)
			ft_deal_damage(info, input[1], "poison", info->c_resistance.poison, 1);
		else if (ft_strcmp_dnd(input[2], "psychic") == 0)
			ft_deal_damage(info, input[1], "psychic", info->c_resistance.psychic, 1);
		else if (ft_strcmp_dnd(input[2], "radiant") == 0)
			ft_deal_damage(info, input[1], "radiant", info->c_resistance.radiant, 1);
		else if (ft_strcmp_dnd(input[2], "slashing") == 0)
			ft_deal_damage(info, input[1], "slashing", info->c_resistance.slashing, 1);
		else if (ft_strcmp_dnd(input[2], "thunder") == 0)
			ft_deal_damage(info, input[1], "thunder", info->c_resistance.thunder, 1);
    }
}
