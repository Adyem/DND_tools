#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

typedef int (*t_skill_calc)(t_char * info);

typedef struct s_skill_table_entry
{
    const char  *name;
    t_skill_calc ability;
    t_skill_calc skill;
}   t_skill_table_entry;

static const t_skill_table_entry g_skill_table[] = {
    {"athletics", &ft_calculate_str, &ft_calculate_athletics},
    {"acrobatics", &ft_calculate_dex, &ft_calculate_acrobatics},
    {"sleight_of_hand", &ft_calculate_dex, &ft_calculate_sleight_of_hand},
    {"stealth", &ft_calculate_dex, &ft_calculate_stealth},
    {"arcana", &ft_calculate_inte, &ft_calculate_arcana},
    {"history", &ft_calculate_inte, &ft_calculate_history},
    {"investigation", &ft_calculate_inte, &ft_calculate_investigation},
    {"nature", &ft_calculate_inte, &ft_calculate_nature},
    {"religion", &ft_calculate_inte, &ft_calculate_religion},
    {"animal_handling", &ft_calculate_wis, &ft_calculate_animal_handling},
    {"insight", &ft_calculate_wis, &ft_calculate_insight},
    {"medicine", &ft_calculate_wis, &ft_calculate_medicine},
    {"perception", &ft_calculate_wis, &ft_calculate_perception},
    {"survival", &ft_calculate_wis, &ft_calculate_survival},
    {"deception", &ft_calculate_cha, &ft_calculate_deception},
    {"intimidation", &ft_calculate_cha, &ft_calculate_intimidation},
    {"performance", &ft_calculate_cha, &ft_calculate_performance},
    {"persuasion", &ft_calculate_cha, &ft_calculate_persuasion}
};

static const int g_skill_table_size = 18;

static int    ft_skill_roll(t_char * info, const char **input)
{
    int index;

    index = 0;
    while (index < g_skill_table_size)
    {
        if (ft_strcmp(input[1], g_skill_table[index].name) == 0)
        {
            ft_skill_throw(info, g_skill_table[index].name,
                g_skill_table[index].ability(info),
                g_skill_table[index].skill(info));
            return (0);
        }
        index++;
    }
    return (1);
}

void    ft_npc_sstuff(t_char * info, const char **input)
{
    if (ft_strcmp(input[1], "attack") == 0)
    {
        if (info->equipment.weapon.attack.function)
            info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
        else
            pf_printf_fd(2, "no weapon attack set for %s\n", info->name);
    }
        else if (ft_strcmp(input[1], "loot") == 0)
        {
                if (info->drop_loot)
                        info->drop_loot(info);
                else
                        pf_printf("This mob doesnt drop anny loot");
        }
    else if (ft_strcmp(input[1], "ranged_attack") == 0)
    {
        if (info->equipment.ranged_weapon.attack.function)
            info->equipment.ranged_weapon.attack.function(info, &info->equipment.ranged_weapon, 0);
        else
            pf_printf_fd(2, "no ranged weapon attack set for %s\n", info->name);
    }
    else if (ft_strcmp(input[1], "move") == 0)
    {
        if (info->flags.prone)
            pf_printf("%s has %i movement", info->name, info->physical.speed / 2);
        else
            pf_printf("%s has %i movement", info->name, info->physical.speed);
    }
    else if (ft_strcmp(input[1], "prone") == 0)
        info->flags.prone = 1;
    else if (ft_strcmp(input[1], "kill") == 0)
        ft_kill(info);
    else if (ft_strcmp(input[1], "damage") == 0)
        ft_request_damage(info);
    else if (ft_strcmp(input[1], "turn") == 0)
    {
        if (info->turn)
            info->turn(info);
        else
            pf_printf("%s doesn't take any actions on his/her turn\n", info->name);
    }
    else if (ft_strcmp(input[1], "hp") == 0)
        pf_printf("HP: %d\n", info->stats.health);
    else if (ft_strcmp(input[1], "initiative") == 0)
        ft_check_initiative(info);
    else if (ft_skill_roll(info, input) == 0)
        return ;
    else
        pf_printf_fd(2, "4-Invalid command given\n");
    return ;
}
