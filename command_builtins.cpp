#include "command_builtins.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/map.hpp"

typedef int (*t_builtin_handler)(char **input, int argc, t_name *name);

typedef struct s_builtin_entry
{
    const char          *key;
    t_builtin_handler   handler;
}   t_builtin_entry;

static int ft_builtin_roll(char **input, int argc, t_name *name)
{
    int *roll_value;

    (void)argc;
    (void)name;
    roll_value = ft_command_roll(input);
    if (roll_value == ft_nullptr)
    {
        if (ft_errno != ER_SUCCESS)
            pf_printf_fd(2, "Roll failed: %s\n", ft_strerror(ft_errno));
        return (FT_BUILTIN_HANDLED);
    }
    pf_printf("%d\n", *roll_value);
    cma_free(roll_value);
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_exit(char **input, int argc, t_name *name)
{
    (void)input;
    (void)name;
    if (argc != 1)
        return (FT_BUILTIN_NOT_FOUND);
    ft_errno = ER_SUCCESS;
    return (FT_BUILTIN_EXIT);
}

static int ft_builtin_fclean(char **input, int argc, t_name *name)
{
    (void)input;
    (void)name;
    if (argc != 1)
        return (FT_BUILTIN_NOT_FOUND);
    ft_fclean();
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_clean(char **input, int argc, t_name *name)
{
    (void)input;
    (void)name;
    if (argc != 1)
        return (FT_BUILTIN_NOT_FOUND);
    ft_clean();
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_initiative(char **input, int argc, t_name *name)
{
    (void)input;
    if (argc != 1)
        return (FT_BUILTIN_NOT_FOUND);
    ft_open_all_files(name);
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_turn(char **input, int argc, t_name *name)
{
    (void)input;
    if (argc != 1)
        return (FT_BUILTIN_NOT_FOUND);
    ft_turn_next(name);
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_test(char **input, int argc, t_name *name)
{
    (void)input;
    if (argc != 1)
        return (FT_BUILTIN_NOT_FOUND);
    ft_test(name);
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_help(char **input, int argc, t_name *name)
{
    (void)input;
    (void)name;
    if (argc != 1)
        return (FT_BUILTIN_NOT_FOUND);
    ft_print_help();
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_encounter(char **input, int argc, t_name *name)
{
    if (argc < 2)
        return (FT_BUILTIN_NOT_FOUND);
    ft_encounter(argc - 1, const_cast<const char **>(input + 1), name);
    return (FT_BUILTIN_HANDLED);
}

static int ft_builtin_player(char **input, int argc, t_name *name)
{
    (void)name;
    if (argc < 2)
        return (FT_BUILTIN_NOT_FOUND);
    if (ft_strcmp(input[0], "add") == 0 && argc < 3)
        return (FT_BUILTIN_NOT_FOUND);
    ft_player(const_cast<const char **>(input));
    return (FT_BUILTIN_HANDLED);
}

static int  ft_populate_builtin_map(ft_map<ft_string, t_builtin_handler> &map)
{
    t_builtin_entry entries[] = {
        {"roll", &ft_builtin_roll},
        {"exit", &ft_builtin_exit},
        {"fclean", &ft_builtin_fclean},
        {"clean", &ft_builtin_clean},
        {"initiative", &ft_builtin_initiative},
        {"turn", &ft_builtin_turn},
        {"test", &ft_builtin_test},
        {"help", &ft_builtin_help},
        {"encounter", &ft_builtin_encounter},
        {"add player", &ft_builtin_player},
        {"list player", &ft_builtin_player}
    };
    size_t          index;
    size_t          count;

    count = sizeof(entries) / sizeof(entries[0]);
    index = 0;
    while (index < count)
    {
        ft_string key(entries[index].key);
        if (key.get_error() != ER_SUCCESS)
            return (-1);
        map.insert(key, entries[index].handler);
        if (map.get_error() != ER_SUCCESS)
            return (-1);
        index = index + 1;
    }
    return (0);
}

static ft_map<ft_string, t_builtin_handler>    &ft_builtin_command_map(void)
{
    static ft_map<ft_string, t_builtin_handler> map(16);
    static bool                                initialized = false;

    if (initialized == false)
    {
        if (ft_populate_builtin_map(map) != 0)
        {
            map.clear();
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (map);
        }
        initialized = true;
    }
    return (map);
}

static Pair<ft_string, t_builtin_handler>  *ft_find_builtin_entry(
        ft_map<ft_string, t_builtin_handler> &map, char **input, int argc)
{
    Pair<ft_string, t_builtin_handler> *entry;
    ft_string                           key;

    if (argc <= 0 || input[0] == ft_nullptr)
        return (ft_nullptr);
    key = ft_string(input[0]);
    if (key.get_error() != ER_SUCCESS)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (ft_nullptr);
    }
    entry = map.find(key);
    if (entry == ft_nullptr && argc > 1 && input[1] != ft_nullptr)
    {
        ft_string combined(input[0]);

        if (combined.get_error() != ER_SUCCESS)
        {
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (ft_nullptr);
        }
        combined.append(" ");
        if (combined.get_error() != ER_SUCCESS)
        {
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (ft_nullptr);
        }
        combined.append(input[1]);
        if (combined.get_error() != ER_SUCCESS)
        {
            ft_errno = FT_ERR_INVALID_ARGUMENT;
            return (ft_nullptr);
        }
        entry = map.find(combined);
    }
    return (entry);
}

int ft_dispatch_builtin_command(char **input, int argc, t_name *name)
{
    Pair<ft_string, t_builtin_handler> *entry;
    t_builtin_handler                  handler;
    int                                previous_errno;
    ft_map<ft_string, t_builtin_handler>   *map_pointer;

    previous_errno = ft_errno;
    if (input == ft_nullptr || argc <= 0)
    {
        ft_errno = previous_errno;
        return (FT_BUILTIN_NOT_FOUND);
    }
    map_pointer = &ft_builtin_command_map();
    if (map_pointer == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_BUILTIN_ERROR);
    }
    ft_map<ft_string, t_builtin_handler>   &map = *map_pointer;
    if (map.get_error() != ER_SUCCESS)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_BUILTIN_ERROR);
    }
    entry = ft_find_builtin_entry(map, input, argc);
    if (entry == ft_nullptr)
    {
        if (ft_errno == FT_ERR_INVALID_ARGUMENT)
            return (FT_BUILTIN_ERROR);
        ft_errno = previous_errno;
        return (FT_BUILTIN_NOT_FOUND);
    }
    handler = entry->value;
    if (handler == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_BUILTIN_ERROR);
    }
    return (handler(input, argc, name));
}
