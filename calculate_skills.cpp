#include "dnd_tools.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Template/vector.hpp"

static int ft_add_skill_source(ft_vector<t_skills*> &sources, t_skills *source)
{
    sources.push_back(source);
    if (sources.get_error() != ER_SUCCESS)
    {
        ft_errno = sources.get_error();
        return (-1);
    }
    return (0);
}

static int ft_populate_skill_sources(t_char *info, ft_vector<t_skills*> &sources)
{
    if (ft_add_skill_source(sources, &info->skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.weapon.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.offhand_weapon.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.ranged_weapon.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.armor.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.helmet.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.shield.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.boots.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.gloves.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.amulet.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.ring_01.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.ring_02.skill_mod) != 0)
        return (-1);
    if (ft_add_skill_source(sources, &info->equipment.belt.skill_mod) != 0)
        return (-1);
    return (0);
}

static int ft_calculate_skill_total(t_char *info, int t_skills::*member)
{
    size_t  count;
    size_t  index;
    int     total;

    if (!info)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (0);
    }
    ft_vector<t_skills*>    sources(13);
    if (sources.get_error() != ER_SUCCESS)
    {
        ft_errno = sources.get_error();
        return (0);
    }
    if (ft_populate_skill_sources(info, sources) != 0)
        return (0);
    count = sources.size();
    if (sources.get_error() != ER_SUCCESS)
    {
        ft_errno = sources.get_error();
        return (0);
    }
    index = 0;
    total = 0;
    while (index < count)
    {
        t_skills    *skill_source;

        skill_source = sources[index];
        if (sources.get_error() != ER_SUCCESS)
        {
            ft_errno = sources.get_error();
            return (0);
        }
        total += skill_source->*member;
        index = index + 1;
    }
    ft_errno = ER_SUCCESS;
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
