#include "dnd_tools.hpp"
#include "command_builtins.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "character.hpp"

static int ft_handle_custom_commands(const char **input, int argc, t_name *name)
{
    t_name *temp;

    temp = name;
    while (temp != ft_nullptr)
    {
        if (argc > 0 && ft_strcmp(input[0], temp->name) == 0)
        {
            temp->function(argc, input, name, 0);
            return (1);
        }
        temp = temp->next;
    }
    return (0);
}

int ft_test_excecute(const char **input, int argc, t_name *name)
{
    char    **mutable_input;
    int     builtin_status;
    int     index;

    if (input == ft_nullptr)
        return (0);
    mutable_input = static_cast<char **>(cma_calloc(static_cast<size_t>(argc + 1),
                sizeof(char *)));
    if (mutable_input == ft_nullptr)
        return (0);
    index = 0;
    while (index < argc)
    {
        mutable_input[index] = const_cast<char *>(input[index]);
        index++;
    }
    mutable_input[index] = ft_nullptr;
    builtin_status = ft_dispatch_builtin_command(mutable_input, argc, name);
    cma_free(mutable_input);
    if (builtin_status == FT_BUILTIN_HANDLED || builtin_status == FT_BUILTIN_EXIT
        || builtin_status == FT_BUILTIN_ERROR)
        return (0);
    ft_handle_custom_commands(input, argc, name);
    return (0);
}
