#include "dnd_tools.hpp"

int ft_ability_mod(int ability_score)
{
    int mod = ability_score - 10;
    if (mod < 0)
        return (mod - 1) / 2;
    return mod / 2;
}

static int ft_sum_equipment_member(t_equipment *equipment,
    int t_equipment_id::*member)
{
    int sum;

    sum = 0;
    sum += (equipment->weapon.*member);
    sum += (equipment->offhand_weapon.*member);
    sum += (equipment->ranged_weapon.*member);
    sum += (equipment->armor.*member);
    sum += (equipment->helmet.*member);
    sum += (equipment->shield.*member);
    sum += (equipment->boots.*member);
    sum += (equipment->gloves.*member);
    sum += (equipment->amulet.*member);
    sum += (equipment->ring_01.*member);
    sum += (equipment->ring_02.*member);
    sum += (equipment->belt.*member);
    return (sum);
}

static int ft_sum_stat_with_equipment(t_char * info, int t_stats::*stat_member,
    int t_equipment_id::*equipment_member)
{
    int total;

    total = (info->stats.*stat_member);
    total += ft_sum_equipment_member(&info->equipment, equipment_member);
    return (total);
}

int ft_calculate_ac(t_char * info)
{
    int ac;
    int dex_mod;

    ac = 10;
    dex_mod = ft_ability_mod(ft_calculate_dex(info));
    if (dex_mod > info->equipment.armor.dex_ac_max_bonus)
        ac += info->equipment.armor.dex_ac_max_bonus;
    else
        ac += dex_mod;
    ac += ft_sum_equipment_member(&info->equipment, &t_equipment_id::ac);
    return (ac);
}

int ft_calculate_str(t_char * info)
{
    return (ft_sum_stat_with_equipment(info, &t_stats::str, &t_equipment_id::str));
}

int ft_calculate_dex(t_char * info)
{
    return (ft_sum_stat_with_equipment(info, &t_stats::dex, &t_equipment_id::dex));
}

int ft_calculate_con(t_char * info)
{
    return (ft_sum_stat_with_equipment(info, &t_stats::con, &t_equipment_id::con));
}

int ft_calculate_inte(t_char * info)
{
    return (ft_sum_stat_with_equipment(info, &t_stats::inte,
        &t_equipment_id::inte));
}

int ft_calculate_wis(t_char * info)
{
    return (ft_sum_stat_with_equipment(info, &t_stats::wis, &t_equipment_id::wis));
}

int ft_calculate_cha(t_char * info)
{
    return (ft_sum_stat_with_equipment(info, &t_stats::cha, &t_equipment_id::cha));
}
