#include "dnd_tools.hpp"
#include "treeNode.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/RNG/rng.hpp"

bool g_dnd_test = 0;

int main(int argc, char **argv)
{
    t_name *name;

    (void)argv;
    if (argc > 1)
    {
        pf_printf_fd(2, "005-Error: expecting no arguments\n");
        return (1);
    }
    if (DEBUG == 1)
    {
        pf_printf("DEBUGGING\n");
        pf_printf("Random sample = %d\n", ft_random_int());
    }
    if (ft_create_data_dir())
        return (1);
    ft_initialize_suggestions_readline();
    name = ft_allocate_memory_name();
    ft_request_input(name);
    ft_free_memory_name(name, 0);
    rl_clear_suggestions();
    ft_cleanup_treeNode();
    return (0);
}
