#include "dnd_tools.h"

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

int	ft_roll_convert_previous(char *string, int *i)
{
	int	result;

	while (*i > 0 && (string[*i] >= '0' && string[*i] <= '9'))
		(*i)--;
	if (*i > 0 && (string[*i] == '+' || string[*i] == '-'))
		(*i)--;
	if (*i > 0 && (string[*i] == '+' || string[*i] == '-'
			|| string[*i] == '*' || string[*i] == '/'))
		(*i)++;
	result = ft_atoi(&string[*i]);
	if (DEBUG == 1)
		ft_printf("the first number is %i and i=%i\n", result);
	return (result);
}

int	ft_roll_convert_next(char *string, int i)
{
	int	result;

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
	if (DEBUG == 1)
		ft_printf("the string after roll itoa is %s\n", string);
	return(0);
}
