#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <climits>
#include <cassert>

static void ft_print_overflow_error(int error_code)
{
    pf_printf("%d-Error: Result is higher than %d or lower than %d\n", error_code, INT_MAX, INT_MIN);
    return ;
}

static int ft_check_add_sub_overflow(int first_number, int second_number,
                                     int error_code, int is_addition)
{
    if (is_addition) 
    {
        if ((second_number > 0 && first_number > INT_MAX - second_number) ||
            (second_number < 0 && first_number < INT_MIN - second_number))
        {
            ft_print_overflow_error(error_code);
            return (1);
        }
    }
    else
    {
        if ((second_number < 0 && first_number > INT_MAX + second_number) ||
            (second_number > 0 && first_number < INT_MIN + second_number))
        {
            ft_print_overflow_error(error_code);
            return (1);
        }
    }
    return (0);
}

static int ft_check_mul_overflow(int first_number, int second_number)
{
    if (first_number != 0 && second_number != 0)
    {
        if (first_number > INT_MAX / second_number || 
            first_number < INT_MIN / second_number)
        {
            ft_print_overflow_error(174);
            return (1);
        }
    }
    return (0);
}

static int ft_check_div_overflow(int first_number, int second_number)
{
    if (second_number == 0)
    {
        pf_printf("176-Error: Division by zero is undefined\n");
        return (1);
    }
    if (first_number == INT_MIN && second_number == -1)
    {
        ft_print_overflow_error(175);
        return (1);
    }
    return (0);
}

static int ft_check_overflow(int first_number, int second_number, char sign)
{
    assert(sign == '+' || sign == '-' || sign == '*' || sign == '/');

    if (sign == '+')
        return (ft_check_add_sub_overflow(first_number, second_number, 172, 1));
    else if (sign == '-')
        return (ft_check_add_sub_overflow(first_number, second_number, 173, 0));
    else if (sign == '*')
        return (ft_check_mul_overflow(first_number, second_number));
    else if (sign == '/')
        return (ft_check_div_overflow(first_number, second_number));
    return (0);
}

static int ft_calculate_result(int first_number, int second_number, char sign)
{
    assert(sign == '+' || sign == '-' || sign == '*' || sign == '/');

    if (sign == '+')
        return (first_number + second_number);
    else if (sign == '-')
        return (first_number - second_number);
    else if (sign == '*')
        return (first_number * second_number);
    else if (sign == '/')
        return (first_number / second_number);
    return (0);
}

static void ft_update_string(char *string, int *i, int x)
{
    if (string[x] == '-' || string[x] == '+')
        x++;
    while (string[x] >= '0' && string[x] <= '9')
        x++;
    if (DEBUG == 1)
        pf_printf("string = %s and x = %d\n", string, x);
    while (string[x])
    {
        string[*i] = string[x];
        (*i)++;
        x++;
    }
    while (string[*i])
    {
        string[*i] = '\0';
        (*i)++;
    }
    return ;
}

int ft_process_sign(char *string, int *i, int j, int *error)
{
    char sign;
    int result, first_number, second_number, x;

    sign = string[*i];
    x = *i;
    if (*i > 0)
        (*i)--;
    x++;
    first_number = ft_roll_convert_previous(string, i, error);
    second_number = ft_roll_convert_next(string, x, error);
    if (*error)
        return (1);
    if (ft_check_overflow(first_number, second_number, sign))
        return (1);
    result = ft_calculate_result(first_number, second_number, sign);
    if (DEBUG == 1)
        pf_printf("result = %d and i=%d\n", result, *i);
    if (ft_roll_itoa(result, i, string))
        return (1);
    ft_update_string(string, i, x);
    *i = 0;
    ft_calculate_j(string, &j);
    return (0);
}
