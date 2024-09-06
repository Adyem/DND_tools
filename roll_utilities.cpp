#include "dnd_tools.hpp"
#include <climits>
#include <cstdlib>
#include "libft/printf/ft_printf.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"

int ft_check_value_roll(const char *str)
{
    int					sign;
    unsigned long long	result;
    unsigned long long	limit;

	sign = 1;
	result = 0;
	limit = (unsigned long long)INT_MAX + 1;
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
        result = result * 10 + (*str - '0');
        str++;
        if ((sign == 1 && result > INT_MAX) || (sign == -1 && result > limit))
            return (1);
		if (DEBUG == 1)
			ft_printf("FT_CHECK_VALUE_ROLL the string is %s\n", str);
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
	int	i;

	i = 0;
	if (to_parse)
	{
		while (to_parse[i])
		{
			free(to_parse[1]);
			i++;
		}
		free(to_parse);
	}
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
		ft_printf_fd(2, "171-Error: numbers cant be higher then %i or lower then %i\n",
				INT_MAX, INT_MIN);
		return (0);
	}
    result = ft_atoi(&string[*i]);
    if (DEBUG == 1)
        ft_printf("the first number is %i and i=%i\n", result, *i);
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
		ft_printf_fd(2, "170-Error: numbers cant be higher then %i or lower then %i\n",
				INT_MAX, INT_MIN);
		return (0);
	}
	result = ft_atoi(&string[i]);
	if (DEBUG == 1)
		ft_printf("the second number is %i\n", result);
	return (result);
}

int	ft_roll_itoa(int result, int *i, char *string)
{
	char	*temp;
	int		y;

	if (DEBUG == 1)
		ft_printf("roll itoa: the value of i=%i\n", *i);
	temp = ft_itoa(result);
	if (!temp)
		return (1);
	y = 0;
	while (temp[y])
	{
		string[*i] = temp[y];
		(*i)++;
		y++;
	}
	free(temp);
	return(0);
}
