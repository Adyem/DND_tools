#include "dnd_tools.hpp"

static int ft_calculate_skill_total(t_char *info, int t_skills::*member)
{
    t_skills    *sources[13];
    int         index;
    int         total;

    sources[0] = &info->skill_mod;
    sources[1] = &info->equipment.weapon.skill_mod;
    sources[2] = &info->equipment.offhand_weapon.skill_mod;
    sources[3] = &info->equipment.ranged_weapon.skill_mod;
    sources[4] = &info->equipment.armor.skill_mod;
    sources[5] = &info->equipment.helmet.skill_mod;
    sources[6] = &info->equipment.shield.skill_mod;
    sources[7] = &info->equipment.boots.skill_mod;
    sources[8] = &info->equipment.gloves.skill_mod;
    sources[9] = &info->equipment.amulet.skill_mod;
    sources[10] = &info->equipment.ring_01.skill_mod;
    sources[11] = &info->equipment.ring_02.skill_mod;
    sources[12] = &info->equipment.belt.skill_mod;
    total = 0;
    index = 0;
    while (index < 13)
    {
        total += sources[index]->*member;
        index++;
    }
    return (total);
}

int ft_calculate_athletics(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::athletics));
}

int ft_calculate_acrobatics(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::acrobatics));
}

int ft_calculate_sleight_of_hand(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::sleight_of_hand));
}

int ft_calculate_stealth(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::stealth));
}

int ft_calculate_arcana(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::arcana));
}

int ft_calculate_history(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::history));
}

int ft_calculate_investigation(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::investigation));
}

int ft_calculate_nature(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::nature));
}

int ft_calculate_religion(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::religion));
}

int ft_calculate_animal_handling(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::animal_handling));
}

int ft_calculate_insight(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::insight));
}

int ft_calculate_medicine(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::medicine));
}

int ft_calculate_perception(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::perception));
}

int ft_calculate_survival(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::survival));
}

int ft_calculate_deception(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::deception));
}

int ft_calculate_intimidation(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::intimidation));
}

int ft_calculate_performance(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::performance));
}

int ft_calculate_persuasion(t_char * info)
{
    return (ft_calculate_skill_total(info, &t_skills::persuasion));
}
