#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include <iostream>

static int ft_get_damage_reduction(t_char *info, const char *type)
{
    if (ft_strcmp_dnd(type, "acid") == 0)
        return (ft_calculate_acid_dr(info));
    else if (ft_strcmp_dnd(type, "bludgeoning") == 0)
        return (ft_calculate_bludgeoning_dr(info));
    else if (ft_strcmp_dnd(type, "cold") == 0)
        return (ft_calculate_cold_dr(info));
    else if (ft_strcmp_dnd(type, "fire") == 0)
        return (ft_calculate_fire_dr(info));
    else if (ft_strcmp_dnd(type, "force") == 0)
        return (ft_calculate_force_dr(info));
    else if (ft_strcmp_dnd(type, "lightning") == 0)
        return (ft_calculate_lightning_dr(info));
    else if (ft_strcmp_dnd(type, "necrotic") == 0)
        return (ft_calculate_necrotic_dr(info));
    else if (ft_strcmp_dnd(type, "piercing") == 0)
        return (ft_calculate_piercing_dr(info));
    else if (ft_strcmp_dnd(type, "poison") == 0)
        return (ft_calculate_poison_dr(info));
    else if (ft_strcmp_dnd(type, "psychic") == 0)
        return (ft_calculate_psychic_dr(info));
    else if (ft_strcmp_dnd(type, "radiant") == 0)
        return (ft_calculate_radiant_dr(info));
    else if (ft_strcmp_dnd(type, "slashing") == 0)
        return (ft_calculate_slashing_dr(info));
    else if (ft_strcmp_dnd(type, "thunder") == 0)
        return (ft_calculate_thunder_dr(info));
    return (ERROR_RESISTANCE);
}

void ft_deal_damage(t_char *info, const char *input, const char *d_type, int resistance, int override)
{
    static int total;
    int temp;
    int damage;
    int extra;
    int damage_reduction;

    if (override == 1 || override == 0)
    {
        if (ft_check_value(input))
        {
            std::cerr << "1-Damage: expecting a number higher than or equal to 0" << std::endl;
            return;
        }
        std::cout << "The " << d_type << " damage was not changed." << std::endl;
        damage = ft_atoi(input);
        if (damage < 0)
        {
            std::cerr << "2-Damage: expecting a number higher than or equal to 0" << std::endl;
            return;
        }
        damage_reduction = ft_get_damage_reduction(info, d_type);
        if (damage_reduction == ERROR_RESISTANCE)
            return (std::cerr << "161-Error finding damage reduction" << std::endl, (void)0);
        damage = damage - damage_reduction;
        if (damage_reduction > 0)
            std::cout << "The " << d_type << " damage was reduced by " << damage_reduction << "." << std::endl;
        else if (damage_reduction < 0)
            std::cout << "The " << d_type << " damage was increased by " << -damage_reduction << "." << std::endl;
        if (damage > 0)
            damage = 0;
        if (d_type && resistance > 0)
        {
            extra = damage * (resistance / 100);
            std::cout << info->name << " is resistant to " << d_type << " damage and takes " << resistance
                      << "% less damage for a total of " << extra << " less damage" << std::endl;
            damage = damage - extra;
        }
        else if (d_type && resistance < 0)
        {
            extra = damage * ((resistance * -1) / 100);
            std::cout << info->name << " is vulnerable to " << d_type << " damage and takes " << -resistance
                      << "% more damage for a total of " << extra << " more damage" << std::endl;
            damage = damage + extra;
        }
        else if (d_type && resistance == 100)
        {
            std::cout << info->name << " is immune to " << d_type << " damage" << std::endl;
            damage = 0;
        }
        temp = info->stats.health;
        info->stats.health = info->stats.health - damage;
        if (info->stats.health < 0)
            info->stats.health = 0;
        total += damage;
        ft_print_character_status(info, damage * -1, temp);
    }
    if (override == 1 || override == 2)
    {
        if (DEBUG == 1)
            std::cout << info->name << " takes " << total << " damage" << std::endl;
        if (info->version_number >= 2 && info->concentration.concentration)
            ft_check_concentration(info, total);
        total = 0;
    }
    return ;
}
