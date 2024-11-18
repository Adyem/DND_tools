#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include <ctime>
#include <cstdlib>

bool dnd_test = 0;

int main(int argc, char **argv)
{
    t_name *name;

    (void)argv;
	ft_errno = 0;
    if (DEBUG == 1)
        pf_printf("Size of t_char struct is %zu\n", sizeof(t_char));
    
    if (argc > 1)
    {
        pf_printf_fd(2, "005-Error: expecting no arguments\n");
        return (1);
    }
    srand((unsigned)time(ft_nullptr));
    if (DEBUG == 1)
    {
        pf_printf("DEBUGGING\n");
        pf_printf("Rand Max = %d\n", RAND_MAX);
    }
	if (ft_create_data_dir())
		return (1);
	ft_initialize_suggestions_readline();
    name = ft_allocate_memory_name();
    ft_request_input(name);
    ft_free_memory_name(name, 0);
	rl_clear_suggestions();
    return (0);
}
