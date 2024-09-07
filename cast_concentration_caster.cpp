#include "dnd_tools.hpp"
#include <iostream>
#include "libft/libft/libft.hpp"

int ft_update_caster_name(char ***caster_name, const char *input_name)
{
    char **temp;

    if (DEBUG == 1)
        std::cout << "adding the new caster name to the target struct" << std::endl;

    if (!(*caster_name))
    {
        *caster_name = (char **)ft_calloc(2, sizeof(char *));
        if (!(*caster_name))
        {
            std::cerr << "165-Error allocating memory for caster name" << std::endl;
            return (1) ;
        }
        **caster_name = ft_strdup(input_name);
        if (!(**caster_name))
        {
            std::cerr << "162-Error allocating memory for caster name" << std::endl;
            return (1) ;
        }
    }
    else
    {
        temp = ft_resize_double_char(*caster_name, input_name, 1);
        if (!temp)
        {
            std::cerr << "297-Error allocating memory for caster name" << std::endl;
            return (1) ;
        }
        ft_free_double_char(*caster_name) ;
        *caster_name = temp;
    }
    return (0) ;
}
