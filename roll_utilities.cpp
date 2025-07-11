#include "dnd_tools.hpp"
#include <climits>
#include <cstdlib>
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"

static int ft_check_value_roll(const char *str)
{
    int					sign;
    unsigned long long	result;
    unsigned long long	limit;

	sign = 1;
	result = 0;
	limit = static_cast<unsigned long long>(INT_MAX) + 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str && ft_isdigit(*str))
    {
        result = result * 10 + (static_cast<unsigned long long>(*str) - '0');
        str++;
        if ((sign == 1 && result > INT_MAX) || (sign == -1 && result > limit))
            return (1);
		if (DEBUG == 1)
			pf_printf("FT_CHECK_VALUE_ROLL the string is %s\n", str);
    }
    if (sign == -1 && result > limit)
        return (1);
    return (0);
}

int	ft_check_string_number(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] >= '0' && string[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_free_parse(char **to_parse)
{
	int	index = 0;

	if (to_parse)
	{
		while (to_parse[index])
		{
			cma_free(to_parse[index]);
			index++;
		}
		cma_free(to_parse);
	}
	return ;
}

int ft_roll_convert_previous(char *string, int *i, int *error)
{
	int result;
	int	check;

	while (*i > 0 && (string[*i] >= '0' && string[*i] <= '9'))
		(*i)--;
	if (*i > 0 && (string[*i - 1] == '+' || string[*i - 1] == '-'))
        (*i)--;
	if (string[*i] < '0' || string[*i] > '9')
		(*i)++;
	check = ft_check_value_roll(&string[*i]);
    if (check != 0)
    {
		*error = 1;
		pf_printf("171-Error: numbers cant be higher then %d or lower than %d\n", INT_MAX, INT_MIN);
		return (0);
	}
    result = ft_atoi(&string[*i]);
    if (DEBUG == 1)
        pf_printf("the first number is %d and i=%d\n", result, *i);
    return (result);
}

int	ft_roll_convert_next(char *string, int i, int *error)
{
	int	result;
	int	check;

	check = ft_check_value_roll(&string[i]);
	if (check != 0)
	{
		*error = 1;
		pf_printf("170-Error: numbers cant be higher then %d or lower than %d\n", INT_MAX, INT_MIN);
		return (0);
	}
	result = ft_atoi(&string[i]);
	if (DEBUG == 1)
		pf_printf("the second number is %d\n", result);
	return (result);
}

int	ft_roll_itoa(int result, int *i, char *string)
{
	char	*temp;
	int		y;

	if (DEBUG == 1)
		pf_printf("roll itoa: the value of i=%d\n", *i);
	temp = cma_itoa(result);
	if (!temp)
		return (1);
	y = 0;
	while (temp[y])
	{
		string[*i] = temp[y];
		(*i)++;
		y++;
	}
	cma_free(temp);
	return (0);
}
