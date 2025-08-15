#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void ft_print_help(void)
{
    pf_printf("Built-in commands:\n");
    pf_printf("  help                Show this help message\n");
    pf_printf("  roll <expr>         Roll dice expression\n");
    pf_printf("  exit                Exit the program\n");
    pf_printf("  fclean              Remove all saved date\n");
    pf_printf("  clean               Clean Monster data\n");
    pf_printf("  initiative          Open all initiative files\n");
    pf_printf("  turn                Advance to next turn\n");
    pf_printf("  test                Run test sequence\n");
    pf_printf("  add player <name>   Add a new player\n");
    pf_printf("  encounter <name>    Start encounter from file\n");
    pf_printf("  encounter xavius damage <portal|shield spell>   Deal 1 damage\n");
    return ;
}
