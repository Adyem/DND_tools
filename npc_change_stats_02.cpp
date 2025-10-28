#include "dnd_tools.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/map.hpp"

typedef int (*t_skill_calc)(t_char * info);
typedef t_npc_command_status    (*t_npc_command_handler)(t_char * info, const char **input);

typedef struct s_skill_table_entry
{
    const char  *name;
    t_skill_calc ability;
    t_skill_calc skill;
}   t_skill_table_entry;

typedef struct s_skill_handler_entry
{
    t_skill_calc ability;
    t_skill_calc skill;
}   t_skill_handler_entry;

typedef struct s_npc_command_entry
{
    const char              *name;
    t_npc_command_handler   handler;
}   t_npc_command_entry;

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

static int  ft_populate_skill_map(ft_map<ft_string, t_skill_handler_entry> &map)
{
    size_t  index;
    size_t  count;

    count = sizeof(g_skill_table) / sizeof(g_skill_table[0]);
    index = 0;
    while (index < count)
    {
        ft_string   key(g_skill_table[index].name);
        t_skill_handler_entry   entry;

        if (key.get_error() != ER_SUCCESS)
            return (-1);
        entry.ability = g_skill_table[index].ability;
        entry.skill = g_skill_table[index].skill;
        map.insert(key, entry);
        if (map.get_error() != ER_SUCCESS)
            return (-1);
        index = index + 1;
    }
    return (0);
}

static ft_map<ft_string, t_skill_handler_entry>  &ft_skill_handler_map(void)
{
    static ft_map<ft_string, t_skill_handler_entry> map(32);
    static bool                                     initialized = false;

    if (initialized == false)
    {
        if (ft_populate_skill_map(map) != 0)
        {
            map.clear();
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (map);
        }
        initialized = true;
    }
    return (map);
}

static t_npc_command_status    ft_execute_skill_roll(t_char * info, const char **input)
{
    Pair<ft_string, t_skill_handler_entry>  *entry;
    ft_string                               key;
    ft_map<ft_string, t_skill_handler_entry>    *map_pointer;
    t_skill_handler_entry                   handler;

    if (input == ft_nullptr || input[1] == ft_nullptr)
        return (FT_NPC_COMMAND_NOT_FOUND);
    map_pointer = &ft_skill_handler_map();
    if (map_pointer == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    ft_map<ft_string, t_skill_handler_entry>    &map = *map_pointer;
    if (map.get_error() != ER_SUCCESS)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    key = ft_string(input[1]);
    if (key.get_error() != ER_SUCCESS)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    entry = map.find(key);
    if (entry == ft_nullptr)
        return (FT_NPC_COMMAND_NOT_FOUND);
    handler = entry->value;
    if (handler.ability == ft_nullptr || handler.skill == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    ft_skill_throw(info, entry->key.c_str(), handler.ability(info), handler.skill(info));
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_attack(t_char * info, const char **input)
{
    (void)input;
    if (info->equipment.weapon.attack.function != ft_nullptr)
    {
        info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
        return (FT_NPC_COMMAND_HANDLED);
    }
    pf_printf_fd(2, "no weapon attack set for %s\n", info->name);
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_loot(t_char * info, const char **input)
{
    (void)input;
    if (info->drop_loot != ft_nullptr)
    {
        info->drop_loot(info);
        return (FT_NPC_COMMAND_HANDLED);
    }
    pf_printf("This mob doesnt drop anny loot");
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_ranged_attack(t_char * info, const char **input)
{
    (void)input;
    if (info->equipment.ranged_weapon.attack.function != ft_nullptr)
    {
        info->equipment.ranged_weapon.attack.function(info,
            &info->equipment.ranged_weapon, 0);
        return (FT_NPC_COMMAND_HANDLED);
    }
    pf_printf_fd(2, "no ranged weapon attack set for %s\n", info->name);
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_move(t_char * info, const char **input)
{
    (void)input;
    if (info->flags.prone != 0)
    {
        pf_printf("%s has %i movement", info->name, info->physical.speed / 2);
        return (FT_NPC_COMMAND_HANDLED);
    }
    pf_printf("%s has %i movement", info->name, info->physical.speed);
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_prone(t_char * info, const char **input)
{
    (void)input;
    info->flags.prone = 1;
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_kill(t_char * info, const char **input)
{
    (void)input;
    ft_kill(info);
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_damage(t_char * info, const char **input)
{
    (void)input;
    ft_request_damage(info);
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_turn(t_char * info, const char **input)
{
    (void)input;
    if (info->turn != ft_nullptr)
    {
        info->turn(info);
        return (FT_NPC_COMMAND_HANDLED);
    }
    pf_printf("%s doesn't take any actions on his/her turn\n", info->name);
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_hp(t_char * info, const char **input)
{
    (void)input;
    pf_printf("HP: %d\n", info->stats.health);
    return (FT_NPC_COMMAND_HANDLED);
}

static t_npc_command_status    ft_npc_command_initiative(t_char * info, const char **input)
{
    (void)input;
    ft_check_initiative(info);
    return (FT_NPC_COMMAND_HANDLED);
}

static int  ft_populate_npc_command_map(ft_map<ft_string, t_npc_command_handler> &map)
{
    t_npc_command_entry entries[] = {
        {"attack", &ft_npc_command_attack},
        {"loot", &ft_npc_command_loot},
        {"ranged_attack", &ft_npc_command_ranged_attack},
        {"move", &ft_npc_command_move},
        {"prone", &ft_npc_command_prone},
        {"kill", &ft_npc_command_kill},
        {"damage", &ft_npc_command_damage},
        {"turn", &ft_npc_command_turn},
        {"hp", &ft_npc_command_hp},
        {"initiative", &ft_npc_command_initiative}
    };
    size_t  index;
    size_t  count;

    count = sizeof(entries) / sizeof(entries[0]);
    index = 0;
    while (index < count)
    {
        ft_string   key(entries[index].name);

        if (key.get_error() != ER_SUCCESS)
            return (-1);
        map.insert(key, entries[index].handler);
        if (map.get_error() != ER_SUCCESS)
            return (-1);
        index = index + 1;
    }
    return (0);
}

static ft_map<ft_string, t_npc_command_handler>  &ft_npc_command_map(void)
{
    static ft_map<ft_string, t_npc_command_handler> map(16);
    static bool                                    initialized = false;

    if (initialized == false)
    {
        if (ft_populate_npc_command_map(map) != 0)
        {
            map.clear();
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (map);
        }
        initialized = true;
    }
    return (map);
}

t_npc_command_status    ft_npc_execute_command(t_char * info, const char **input)
{
    Pair<ft_string, t_npc_command_handler> *entry;
    t_npc_command_handler                   handler;
    ft_string                               key;
    ft_map<ft_string, t_npc_command_handler>    *map_pointer;
    int                                     previous_errno;

    previous_errno = ft_errno;
    if (info == ft_nullptr || input == ft_nullptr || input[1] == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    map_pointer = &ft_npc_command_map();
    if (map_pointer == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    ft_map<ft_string, t_npc_command_handler>    &map = *map_pointer;
    if (map.get_error() != ER_SUCCESS)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    key = ft_string(input[1]);
    if (key.get_error() != ER_SUCCESS)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_NPC_COMMAND_ERROR);
    }
    entry = map.find(key);
    if (entry != ft_nullptr)
    {
        handler = entry->value;
        if (handler == ft_nullptr)
        {
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (FT_NPC_COMMAND_ERROR);
        }
        ft_errno = previous_errno;
        return (handler(info, input));
    }
    ft_errno = previous_errno;
    return (ft_execute_skill_roll(info, input));
}

void    ft_npc_sstuff(t_char * info, const char **input)
{
    t_npc_command_status    status;

    status = ft_npc_execute_command(info, input);
    if (status == FT_NPC_COMMAND_NOT_FOUND || status == FT_NPC_COMMAND_ERROR)
        pf_printf_fd(2, "4-Invalid command given\n");
    return ;
}
