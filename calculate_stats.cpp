#include "dnd_tools.hpp"

int ft_calculate_ac(t_char * info)
{
    int ac;

    ac = 10;
    if (((ft_calculate_dex(info) - 10) / 2) > info->equipment.armor.dex_ac_max_bonus)
        ac += info->equipment.armor.dex_ac_max_bonus;
    else
        ac += (ft_calculate_dex(info) - 10) / 2;
    ac += info->equipment.weapon.ac;
    ac += info->equipment.offhand_weapon.ac;
    ac += info->equipment.ranged_weapon.ac;
    ac += info->equipment.armor.ac;
    ac += info->equipment.helmet.ac;
    ac += info->equipment.shield.ac;
    ac += info->equipment.boots.ac;
    ac += info->equipment.gloves.ac;
    ac += info->equipment.amulet.ac;
    ac += info->equipment.ring_01.ac;
    ac += info->equipment.ring_02.ac;
    ac += info->equipment.belt.ac;
    return (ac);
}

int ft_calculate_str(t_char * info)
{
    int str;

    str = info->stats.str;
    str += info->equipment.weapon.str;
    str += info->equipment.offhand_weapon.str;
    str += info->equipment.ranged_weapon.str;
    str += info->equipment.armor.str;
    str += info->equipment.helmet.str;
    str += info->equipment.shield.str;
    str += info->equipment.boots.str;
    str += info->equipment.gloves.str;
    str += info->equipment.amulet.str;
    str += info->equipment.ring_01.str;
    str += info->equipment.ring_02.str;
    str += info->equipment.belt.str;
    return (str);
}

int ft_calculate_dex(t_char * info)
{
    int dex;

    dex = info->stats.dex;
    dex += info->equipment.weapon.dex;
    dex += info->equipment.offhand_weapon.dex;
    dex += info->equipment.ranged_weapon.dex;
    dex += info->equipment.armor.dex;
    dex += info->equipment.helmet.dex;
    dex += info->equipment.shield.dex;
    dex += info->equipment.boots.dex;
    dex += info->equipment.gloves.dex;
    dex += info->equipment.amulet.dex;
    dex += info->equipment.ring_01.dex;
    dex += info->equipment.ring_02.dex;
    dex += info->equipment.belt.dex;
    return (dex);
}

int ft_calculate_con(t_char * info)
{
    int con;

    con = info->stats.con;
    con += info->equipment.weapon.con;
    con += info->equipment.offhand_weapon.con;
    con += info->equipment.ranged_weapon.con;
    con += info->equipment.armor.con;
    con += info->equipment.helmet.con;
    con += info->equipment.shield.con;
    con += info->equipment.boots.con;
    con += info->equipment.gloves.con;
    con += info->equipment.amulet.con;
    con += info->equipment.ring_01.con;
    con += info->equipment.ring_02.con;
    con += info->equipment.belt.con;
    return (con);
}

int ft_calculate_inte(t_char * info)
{
    int inte;

    inte = info->stats.inte;
    inte += info->equipment.weapon.inte;
    inte += info->equipment.offhand_weapon.inte;
    inte += info->equipment.ranged_weapon.inte;
    inte += info->equipment.armor.inte;
    inte += info->equipment.helmet.inte;
    inte += info->equipment.shield.inte;
    inte += info->equipment.boots.inte;
    inte += info->equipment.gloves.inte;
    inte += info->equipment.amulet.inte;
    inte += info->equipment.ring_01.inte;
    inte += info->equipment.ring_02.inte;
    inte += info->equipment.belt.inte;
    return (inte);
}

int ft_calculate_wis(t_char * info)
{
    int wis;

    wis = info->stats.wis;
    wis += info->equipment.weapon.wis;
    wis += info->equipment.offhand_weapon.wis;
    wis += info->equipment.ranged_weapon.wis;
    wis += info->equipment.armor.wis;
    wis += info->equipment.helmet.wis;
    wis += info->equipment.shield.wis;
    wis += info->equipment.boots.wis;
    wis += info->equipment.gloves.wis;
    wis += info->equipment.amulet.wis;
    wis += info->equipment.ring_01.wis;
    wis += info->equipment.ring_02.wis;
    wis += info->equipment.belt.wis;
    return (wis);
}

int ft_calculate_cha(t_char * info)
{
    int cha;

    cha = info->stats.cha;
    cha += info->equipment.weapon.cha;
    cha += info->equipment.offhand_weapon.cha;
    cha += info->equipment.ranged_weapon.cha;
    cha += info->equipment.armor.cha;
    cha += info->equipment.helmet.cha;
    cha += info->equipment.shield.cha;
    cha += info->equipment.boots.cha;
    cha += info->equipment.gloves.cha;
    cha += info->equipment.amulet.cha;
    cha += info->equipment.ring_01.cha;
    cha += info->equipment.ring_02.cha;
    cha += info->equipment.belt.cha;
    return (cha);
}
