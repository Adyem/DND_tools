#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"
#include <ctime>
#include <cstdlib>

int main(int argc, char **argv)
{
    t_name *name;

    (void)argv;
    if (DEBUG == 1)
        ft_printf("Size of t_char struct is %zu\n", sizeof(t_char));
    
    if (argc > 1)
    {
        ft_printf_fd(2, "005-Error: expecting no arguments\n");
        return (1);
    }
    srand((unsigned)time(nullptr));

    if (DEBUG == 1)
    {
        ft_printf("DEBUGGING\n");
        ft_printf("Rand Max = %d\n", RAND_MAX);
    }
    if (ft_create_data_dir())
        return (1);
    name = ft_allocate_memory_name();
    ft_request_input(name);
    ft_free_memory_name(name, 0);
    return (0);
}
