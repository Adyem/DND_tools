#include "dnd_tools.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include "libft/Libft/libft.hpp"

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
			std::cout << "FT_CHECK_VALUE_ROLL the string is " << str << "\n";
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
		std::cerr << "171-Error: numbers cant be higher then " << INT_MAX 
                  << " or lower then " << INT_MIN << "\n";
		return (0);
	}
    result = ft_atoi(&string[*i]);
    if (DEBUG == 1)
        std::cout << "the first number is " << result << " and i=" << *i << "\n";
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
		std::cerr << "170-Error: numbers cant be higher then " << INT_MAX 
                  << " or lower then " << INT_MIN << "\n";
		return (0);
	}
	result = ft_atoi(&string[i]);
	if (DEBUG == 1)
		std::cout << "the second number is " << result << "\n";
	return (result);
}

int	ft_roll_itoa(int result, int *i, char *string)
{
	char	*temp;
	int		y;

	if (DEBUG == 1)
		std::cout << "roll itoa: the value of i=" << *i << "\n";
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
