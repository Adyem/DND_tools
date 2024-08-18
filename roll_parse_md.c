#include "dnd_tools.h"

int	ft_roll_excecute_md(char *string, int *i, int j)
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
        if (!string[*i] || string[*i] == ')')
            break ;
        if (string[*i] == '/' || string[*i] == '*')
        {
            sign = string[*i];
            x = *i;
            if (*i > 0)
                (*i)--;
            x++;
            if (DEBUG == 1)
                ft_printf("before calculation the value of x is %i\n", x);
            first_number = ft_roll_convert_previous(string, i, &error);
            second_number = ft_roll_convert_next(string, x, &error);
            if (error)
                return (1);
            if (sign == '*')
            {
                if (first_number != 0 && 
                    (second_number > INT_MAX / first_number || second_number < INT_MIN / first_number))
                {
					ft_printf_fd(2, "174-Error: Result is higher then %i or lower then %i\n",
							INT_MAX, INT_MIN);
                    return (1);
                }
                result = first_number * second_number;
            }
            else if (sign == '/')
            {
                if (second_number == 0)
                {
					ft_printf_fd(2, "176-Error: Cant divide by 0\n");
                    return (1); // Division by zero
                }
                if (first_number == INT_MIN && second_number == -1)
                {
					ft_printf_fd(2, "175-Error: Result is higher then %i or lower then %i\n",
							INT_MAX, INT_MIN);
                    return (1);
                }
                result = first_number / second_number;
            }
            else
            {
                return (1);
            }
            if (DEBUG == 1)
                ft_printf("result = %i and i=%i\n", result, *i);
            if (ft_roll_itoa(result, i, string))
                return (1);
            if (DEBUG == 1)
                ft_printf("the value of i = %i and x = %i\n", *i, x);
            if (string[x] == '-' || string[x] == '+')
                x++;
            while (string[x] >= '0' && string[x] <= '9')
                x++;
            if (DEBUG == 1)
                ft_printf("the value of i = %i and x = %i\n", *i, x);
            while (string[x])
            {
                if (DEBUG == 1)
                    ft_printf("copying over value %c\n" \
                        "check 2:the value of i = %i and x = %i\n", string[x], *i, x);
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
        ft_printf("after md the result is %s\n", string);
    return (0);
}
