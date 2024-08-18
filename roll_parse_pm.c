#include "dnd_tools.h"

int ft_roll_excecute_pm(char *string, int *i, int j)
{
    char    sign;
    int     result;
    int     first_number;
    int     second_number;
    int     x;
    int     error;

    error = 0;
    while(*i < j)
    {
        if (DEBUG == 1)
            ft_printf("PM i=%i and j=%i\n", *i, j);
        if (!string[*i] || string[*i] == ')')
            break ;
        if (string[*i] == '+' || string[*i] == '-')
        {
            sign = string[*i];
            x = *i;
            if (*i > 0)
                (*i)--;
            x++;
            first_number = ft_roll_convert_previous(string, i, &error);
            second_number = ft_roll_convert_next(string, x, &error);
            if (error)
                return (1);
            if (sign == '+')
            {
                if ((second_number > 0 && first_number > INT_MAX - second_number) ||
                    (second_number < 0 && first_number < INT_MIN - second_number))
                {
					ft_printf_fd(2, "172-Error: Result is higher then %i or lower then %i\n",
							INT_MAX, INT_MIN);
                    return (1);
                }
                result = first_number + second_number;
            }
            else if (sign == '-')
            {
                if ((second_number < 0 && first_number > INT_MAX + second_number) ||
                    (second_number > 0 && first_number < INT_MIN + second_number))
                {
					ft_printf_fd(2, "173-Error: Result is higher then %i or lower then %i\n",
							INT_MAX, INT_MIN);
                    return (1);
                }
                result = first_number - second_number;
            }
            else
            {
                return (1);
            }
            if (DEBUG == 1)
                ft_printf("result = %i and i=%i\n", result, *i);
            if (ft_roll_itoa(result, i, string))
                return (1);
            if (string[x] == '-' || string[x] == '+')
                x++;
            while (string[x] >= '0' && string[x] <= '9')
                x++;
            while (string[x])
            {
                string[*i] = string[x];
                (*i)++;
                x++;
            }
            string[*i] = '\0';
            *i = 0;
            ft_calculate_j(string, &j);
        }
        (*i)++;
    }
    if (DEBUG == 1)
        ft_printf("the result after pm is %s\n", string);
    return (0);
}
