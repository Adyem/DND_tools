#include "dnd_tools.hpp"
#include "command_builtins.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"

static char    **ft_parse_input(char *input_string)
{
    char **input;

    input = cma_split(input_string, ' ');
    if (!input)
    {
        cma_free(input_string);
        pf_printf_fd(2, "006-Error splitting input\n");
    }
    return (input);
}

static int ft_handle_custom_commands(char **input, int argc, t_name *name)
{
    if (input[0] == ft_nullptr)
        return (0);

    t_name *temp;

    temp = name;
    while (temp != ft_nullptr)
    {
        if (argc > 0 && ft_strcmp(input[0], temp->name) == 0)
        {
            temp->function(argc, const_cast<const char **>(input), name, 0);
            return (1);
        }
        temp = temp->next;
    }
    return (0);
}

void ft_request_input(t_name *name)
{
    char *input_string;
    char **input;

    while ((input_string = rl_readline("dndtools: ")) != ft_nullptr)
    {
        input = ft_parse_input(input_string);
        if (!input)
            continue ;
        if (input[0] == ft_nullptr)
        {
            ft_free_input(input, input_string);
            continue ;
        }
        int index = 0;
        while (input[index])
            index++;
        int builtin_status;
        int found;

        builtin_status = ft_dispatch_builtin_command(input, index, name);
        if (builtin_status == FT_BUILTIN_EXIT)
        {
            rl_clear_history();
            ft_free_input(input, input_string);
            return ;
        }
        if (builtin_status == FT_BUILTIN_HANDLED)
        {
            ft_free_input(input, input_string);
            continue ;
        }
        if (builtin_status == FT_BUILTIN_ERROR)
        {
            pf_printf_fd(2, "008-Error failed to process builtin command: %s\n",
                ft_strerror(ft_errno));
            ft_free_input(input, input_string);
            continue ;
        }
        found = ft_handle_custom_commands(input, index, name);
        if (!found)
            pf_printf_fd(2, "007-Error unknown command: %s\n", input_string);
        ft_free_input(input, input_string);
    }
    return ;
}
