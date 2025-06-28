#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"

void ft_print_help(t_name *name)
{
    pf_printf("Built-in commands:\n");
    pf_printf("  help                Show this help message\n");
    pf_printf("  roll <expr>         Roll dice expression\n");
    pf_printf("  exit                Exit the program\n");
    pf_printf("  fclean              Remove generated files\n");
    pf_printf("  clean               Clean object files\n");
    pf_printf("  initiative          Open all initiative files\n");
    pf_printf("  turn                Advance to next turn\n");
    pf_printf("  test                Run test sequence\n");
    pf_printf("  add player <name>   Add a new player\n");
    pf_printf("  encounter <name>    Start encounter from file\n");
    pf_printf("\nCustom commands:\n");
    t_name *tmp = name;
    while (tmp != ft_nullptr)
    {
        pf_printf("  %s\n", tmp->name);
        tmp = tmp->next;
    }
    return ;
}
