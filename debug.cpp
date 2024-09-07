#include "dnd_tools.hpp"
#include <iostream>

void ft_print_content(char **content)
{
    int i;

    if (DEBUG != 1)
        return;
    
    i = 0;
    if (content)
    {
        while (content[i])
        {
            std::cout << content[i];
            i++;
        }
    }
    std::cout << std::endl;
    return;
}
