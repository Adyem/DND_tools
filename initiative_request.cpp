#include "dnd_tools.hpp"
#include "libft/libft/libft.hpp"
#include <readline/readline.h>
#include <iostream>
#include <cstring>
#include <cerrno>

int ft_request_initiative(t_pc *player)
{
    char *temp;
    char *message;
    char *input;
    int initiative;

    temp = ft_strjoin("Requesting initiative for ", player->name);
    if (!temp)
    {
        std::cerr << "250 Error allocating memory: " << strerror(errno) << std::endl;
        return (1);
    }
    message = ft_strjoin(temp, ": ");
    free(temp);
    if (!message)
    {
        std::cerr << "251 Error allocating memory: " << strerror(errno) << std::endl;
        return (1);
    }
    while ((input = readline(message)))
    {
        if (!input)
            return (1);
        if (ft_check_value(input))
        {
            free(input);
            std::cerr << "Requesting a number between 1 and 50" << std::endl;
            continue ;
        }
        initiative = ft_atoi(input);
        free(input);
        if (!(initiative >= 1 && initiative <= 50))
        {
            std::cerr << "Requesting a number between 1 and 50" << std::endl;
            continue ;
        }
        player->initiative = initiative;
        break ;
    }
    free(message);
    return (0);
}
