#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"

int ft_roll_excecute_pm(char *string, int *i, int j)
{
    int error = 0;

    if (DEBUG == 1)
        ft_printf_fd(1, "CHECKING PM\n");
    while (*i < j)
    {
        if (DEBUG == 1)
            ft_printf("PM i=%d and j=%d\n", *i, j);
        if (!string[*i] || string[*i] == ')')
            break ;
        if (string[*i] == '+' || string[*i] == '-')
        {
            if (ft_process_sign(string, i, j, &error))
                return (1);
            ft_calculate_j(string, &j);
            *i = 0;
        }
        else
            (*i)++;
    }
    ft_calculate_j(string, &j);
    if (DEBUG == 1)
        ft_printf("The result after pm is %s\n", string);
    return (0);
}
