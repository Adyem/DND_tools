#include "dnd_tools.h"

static int ft_handle_dice_roll(char *string, int *i, int *x, int *error)
{
    int first_number;
    int second_number;

    if (DEBUG == 1)
        ft_printf("the value of x = %i\n", *x);

    if (string[*i] >= '0' && string[*i] <= '9')
        first_number = ft_roll_convert_previous(string, i, error);
    else
        first_number = 1;
    second_number = ft_roll_convert_next(string, *x, error);
    if (*error)
        return (1);
    if (first_number <= 0)
	{
        ft_printf("178-Error: The number of dice must be greater than 0. Current value: %i\n", first_number);
        return (1);
    }
    if (second_number <= 0)
	{
        ft_printf("179-Error: The number of faces on a die must be greater than 0. " \
                  "Current value: %i, the result can't be higher than %i as well\n", second_number, INT_MAX);
        return (1);
    }

    return ft_dice_roll(first_number, second_number);
}

static int ft_handle_result_replacement(char *string, int *i, int x, int result)
{
    if (ft_roll_itoa(result, i, string))
        return (1);
    if (DEBUG == 1)
        ft_printf("1 the value of i = %i and x = %i\n", *i, x);
    if (string[x] == '-' || string[x] == '+')
        x++;
    while (string[x] >= '0' && string[x] <= '9')
        x++;
    if (DEBUG == 1)
        ft_printf("2 the value of i = %i and x = %i\n", *i, x);
    while (string[x])
	{
        string[*i] = string[x];
        (*i)++;
        x++;
    }
    string[*i] = '\0';
    *i = 0;
    return (0);
}

int ft_roll_excecute_droll(char *string, int *i, int j)
{
    int result;
    int x;
    int error;

    error = 0;
    while (*i < j)
	{
        if (!string[*i] || string[*i] == ')')
            break;
        if (string[*i] == 'd') {
            x = *i;
            if (*i > 0)
                (*i)--;
            x++;
            result = ft_handle_dice_roll(string, i, &x, &error);
            if (result == -1 || error)
                return (1);
            if (ft_handle_result_replacement(string, i, x, result))
                return (1);
            ft_calculate_j(string, &j);
        }
        (*i)++;
    }
    if (DEBUG == 1)
        ft_printf("after dicerolling result is %s\n", string);

    return (0);
}

