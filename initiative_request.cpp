#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"
#include <cstdlib>
#include <readline/readline.h>
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
        ft_printf_fd(2, "250 Error allocating memory: %s\n", strerror(errno));
        return (1);
    }
    message = ft_strjoin(temp, ": ");
    free(temp);
    if (!message)
    {
        ft_printf_fd(2, "251 Error allocating memory: %s\n", strerror(errno));
        return (1);
    }
    while ((input = readline(message)))
    {
        if (!input)
            return (1);
        if (ft_check_value(input))
        {
            free(input);
            ft_printf("Requesting a number between 1 and 50\n");
            continue ;
        }
        initiative = ft_atoi(input);
        free(input);
        if (!(initiative >= 1 && initiative <= 50))
        {
            ft_printf("Requesting a number between 1 and 50\n");
            continue ;
        }
        player->initiative = initiative;
        break ;
    }
    free(message);
    return (0);
}
