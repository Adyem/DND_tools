#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/map.hpp"

typedef int (*t_damage_reduction_calculator)(t_char *);

typedef struct s_damage_reduction_entry
{
    const char                      *type;
    t_damage_reduction_calculator    calculator;
}   t_damage_reduction_entry;

static int    ft_populate_damage_reduction_map(
                ft_map<ft_string, t_damage_reduction_calculator> &map)
{
    t_damage_reduction_entry    entries[] = {
        {DAMAGE_TYPE_ACID, &ft_calculate_acid_dr},
        {DAMAGE_TYPE_BLUDGEONING, &ft_calculate_bludgeoning_dr},
        {DAMAGE_TYPE_COLD, &ft_calculate_cold_dr},
        {DAMAGE_TYPE_FIRE, &ft_calculate_fire_dr},
        {DAMAGE_TYPE_FORCE, &ft_calculate_force_dr},
        {DAMAGE_TYPE_LIGHTNING, &ft_calculate_lightning_dr},
        {DAMAGE_TYPE_NECROTIC, &ft_calculate_necrotic_dr},
        {DAMAGE_TYPE_PIERCING, &ft_calculate_piercing_dr},
        {DAMAGE_TYPE_POISON, &ft_calculate_poison_dr},
        {DAMAGE_TYPE_PSYCHIC, &ft_calculate_psychic_dr},
        {DAMAGE_TYPE_RADIANT, &ft_calculate_radiant_dr},
        {DAMAGE_TYPE_SLASHING, &ft_calculate_slashing_dr},
        {DAMAGE_TYPE_THUNDER, &ft_calculate_thunder_dr}
    };
    size_t                      index;

    index = 0;
    while (index < sizeof(entries) / sizeof(entries[0]))
    {
        ft_string key(entries[index].type);
        if (key.get_error() != ER_SUCCESS)
            return (-1);
        map.insert(key, entries[index].calculator);
        if (map.get_error() != ER_SUCCESS)
            return (-1);
        index = index + 1;
    }
    return (0);
}

static ft_map<ft_string, t_damage_reduction_calculator>    &ft_damage_reduction_map(void)
{
    static ft_map<ft_string, t_damage_reduction_calculator> map(16);
    static bool                                            initialized = false;

    if (initialized == false)
    {
        if (ft_populate_damage_reduction_map(map) != 0)
        {
            map.clear();
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (map);
        }
        initialized = true;
    }
    return (map);
}

static int    ft_get_damage_reduction(t_char * info, const char *type)
{
    ft_map<ft_string, t_damage_reduction_calculator>   &map = ft_damage_reduction_map();
    Pair<ft_string, t_damage_reduction_calculator>     *entry;
    t_damage_reduction_calculator                       calculator;
    ft_string                                           key(type);

    if (!type)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (ERROR_RESISTANCE);
    }
    if (key.get_error() != ER_SUCCESS)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (ERROR_RESISTANCE);
    }
    entry = map.find(key);
    if (!entry)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (ERROR_RESISTANCE);
    }
    calculator = entry->value;
    if (!calculator)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (ERROR_RESISTANCE);
    }
    ft_errno = ER_SUCCESS;
    return (calculator(info));
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
        if (ft_validate_int(input))
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
        if (d_type && resistance == 100)
        {
            pf_printf("%s is immune to %s damage.\n", info->name, d_type);
            damage = 0;
        }
        else if (d_type && resistance > 0)
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
