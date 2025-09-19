#include "dnd_tools.hpp"

static int    ft_calculate_total_dr(t_char * info, int t_resistance::*field)
{
    t_equipment_id    *equipment_slots[12];
    int                index;
    int                total;

    equipment_slots[0] = &info->equipment.weapon;
    equipment_slots[1] = &info->equipment.offhand_weapon;
    equipment_slots[2] = &info->equipment.ranged_weapon;
    equipment_slots[3] = &info->equipment.armor;
    equipment_slots[4] = &info->equipment.helmet;
    equipment_slots[5] = &info->equipment.shield;
    equipment_slots[6] = &info->equipment.boots;
    equipment_slots[7] = &info->equipment.gloves;
    equipment_slots[8] = &info->equipment.amulet;
    equipment_slots[9] = &info->equipment.ring_01;
    equipment_slots[10] = &info->equipment.ring_02;
    equipment_slots[11] = &info->equipment.belt;
    index = 0;
    total = 0;
    while (index < 12)
    {
        total += ((equipment_slots[index]->flat_dr).*field);
        index = index + 1;
    }
    return (total);
}

int    ft_calculate_acid_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::acid));
}

int    ft_calculate_bludgeoning_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::bludgeoning));
}

int    ft_calculate_cold_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::cold));
}

int    ft_calculate_fire_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::fire));
}

int    ft_calculate_force_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::force));
}

int    ft_calculate_lightning_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::lightning));
}

int    ft_calculate_necrotic_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::necrotic));
}

int    ft_calculate_piercing_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::piercing));
}

int    ft_calculate_poison_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::poison));
}

int    ft_calculate_psychic_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::psychic));
}

int    ft_calculate_radiant_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::radiant));
}

int    ft_calculate_slashing_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::slashing));
}

int    ft_calculate_thunder_dr(t_char * info)
{
    return (ft_calculate_total_dr(info, &t_resistance::thunder));
}
