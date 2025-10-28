#include "dnd_tools.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Template/vector.hpp"

typedef t_equipment_id t_equipment::*t_equipment_slot;

static int    ft_add_equipment_slot(ft_vector<t_equipment_slot> &slots,
                t_equipment_slot slot)
{
    slots.push_back(slot);
    if (slots.get_error() != ER_SUCCESS)
    {
        ft_errno = slots.get_error();
        return (-1);
    }
    return (0);
}

static int    ft_populate_equipment_slots(ft_vector<t_equipment_slot> &slots)
{
    if (ft_add_equipment_slot(slots, &t_equipment::weapon) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::offhand_weapon) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::ranged_weapon) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::armor) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::helmet) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::shield) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::boots) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::gloves) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::amulet) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::ring_01) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::ring_02) != 0)
        return (-1);
    if (ft_add_equipment_slot(slots, &t_equipment::belt) != 0)
        return (-1);
    return (0);
}

static int    ft_calculate_total_dr(t_char * info, int t_resistance::*field)
{
    ft_vector<t_equipment_slot>    slots(12);
    size_t                          slot_count;
    size_t                          index;
    int                             total;

    if (slots.get_error() != ER_SUCCESS)
    {
        ft_errno = slots.get_error();
        return (0);
    }
    if (ft_populate_equipment_slots(slots) != 0)
        return (0);
    slot_count = slots.size();
    if (slots.get_error() != ER_SUCCESS)
    {
        ft_errno = slots.get_error();
        return (0);
    }
    index = 0;
    total = 0;
    while (index < slot_count)
    {
        t_equipment_slot slot = slots[index];
        if (slots.get_error() != ER_SUCCESS)
        {
            ft_errno = slots.get_error();
            return (0);
        }
        total += ((info->equipment.*slot).flat_dr.*field);
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
