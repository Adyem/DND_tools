#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"

static int ft_get_damage_reduction(t_char * info, const char *type)
{
    if (ft_strcmp(type, "acid") == 0)
        return (ft_calculate_acid_dr(info));
    else if (ft_strcmp(type, "bludgeoning") == 0)
        return (ft_calculate_bludgeoning_dr(info));
    else if (ft_strcmp(type, "cold") == 0)
        return (ft_calculate_cold_dr(info));
    else if (ft_strcmp(type, "fire") == 0)
        return (ft_calculate_fire_dr(info));
    else if (ft_strcmp(type, "force") == 0)
        return (ft_calculate_force_dr(info));
    else if (ft_strcmp(type, "lightning") == 0)
        return (ft_calculate_lightning_dr(info));
    else if (ft_strcmp(type, "necrotic") == 0)
        return (ft_calculate_necrotic_dr(info));
    else if (ft_strcmp(type, "piercing") == 0)
        return (ft_calculate_piercing_dr(info));
    else if (ft_strcmp(type, "poison") == 0)
        return (ft_calculate_poison_dr(info));
    else if (ft_strcmp(type, "psychic") == 0)
        return (ft_calculate_psychic_dr(info));
    else if (ft_strcmp(type, "radiant") == 0)
        return (ft_calculate_radiant_dr(info));
    else if (ft_strcmp(type, "slashing") == 0)
        return (ft_calculate_slashing_dr(info));
    else if (ft_strcmp(type, "thunder") == 0)
        return (ft_calculate_thunder_dr(info));
    return (ERROR_RESISTANCE);
}

void ft_deal_damage(t_char * info, const char *input, const char *d_type,
                        int resistance, int override)
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
            pf_printf_fd(2, "1-Damage: expecting a number higher than or equal to 0\n");
            return ;
        }
        damage = ft_atoi(input);
        if (damage < 0)
        {
            pf_printf_fd(2, "2-Damage: expecting a number higher than or equal to 0\n");
            return ;
        }
        damage_reduction = ft_get_damage_reduction(info, d_type);
        if (damage_reduction == ERROR_RESISTANCE)
            return (pf_printf_fd(2, "161-Error finding damage reduction\n"), (void)0);
        damage = damage - damage_reduction;
        if (damage_reduction > 0)
            pf_printf("The %s damage was reduced by %d.\n", d_type, damage_reduction);
        else if (damage_reduction < 0)
            pf_printf("The %s damage was increased by %d.\n", d_type, -damage_reduction);
        if (damage < 0)
            damage = 0;
        if (d_type && resistance > 0)
        {
            extra = (damage * resistance) / 100;
            pf_printf("%s is resistant to %s damage and takes %d%% less damage for a " \
                    "total of %d less damage.\n", info->name, d_type, resistance, extra);
            damage = damage - extra;
        }
        else if (d_type && resistance < 0)
        {
            extra = damage * ((resistance * -1) / 100);
            pf_printf("%s is vulnerable to %s damage and takes %d%% more damage for a " \
                    "total of %d more damage.\n", info->name, d_type, -resistance, extra);
            damage = damage + extra;
        }
        else if (d_type && resistance == 100)
        {
            pf_printf("%s is immune to %s damage.\n", info->name, d_type);
            damage = 0;
        }
        if (info->bufs.growth.stacks > 0) {
            damage -= info->bufs.growth.stacks;
            if (damage < 0)
                damage = 0;
            pf_printf("growth reduces damage by %d.\n", info->bufs.growth.stacks);
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
            pf_printf("%s takes %d damage.\n", info->name, total);
        if (info->version_number >= 2 && info->concentration.concentration)
            ft_check_concentration(info, total);
        total = 0;
    }
    return ;
}
