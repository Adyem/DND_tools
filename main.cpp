#include "dnd_tools.hpp"
#include <iostream>
#include <ctime>

int main(int argc, char **argv)
{
    t_name *name;

    (void)argv;
    if (DEBUG == 1)
        std::cout << "Size of t_char struct is " << sizeof(t_char) << std::endl;
    
    if (argc > 1)
    {
        std::cerr << "005-Error: expecting no arguments" << std::endl;
        return (1);
    }
    srand((unsigned)time(nullptr));

    if (DEBUG == 1)
    {
        std::cout << "DEBUGGING" << std::endl;
        std::cout << "Rand Max = " << RAND_MAX << std::endl;
    }
    if (ft_create_data_dir())
        return (1);
    name = ft_allocate_memory_name();
    ft_request_input(name);
    ft_free_memory_name(name, 0);
    return (0);
}
