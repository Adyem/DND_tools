#include "dnd_tools.hpp"
#include <iostream>

int ft_roll_excecute_md(char *string, int *i, int j)
{
    int error = 0;

    while (*i < j)
    {
        if (DEBUG == 1)
            std::cout << "MD i=" << *i << " and j=" << j << std::endl;
        if (!string[*i] || string[*i] == ')')
            break;
        if (string[*i] == '*' || string[*i] == '/')
        {
            if (ft_process_sign(string, i, j, &error))
                return 1;
            ft_calculate_j(string, &j);
            *i = 0;
        }
        else
            (*i)++;
    }
    ft_calculate_j(string, &j);
    if (DEBUG == 1)
        std::cout << "The result after md is " << string << std::endl;
    return (0);
}
