#include "dnd_tools.h"

int	ft_check_value(char *input)
{
	long	check;
	int		i;
	int		sign;

	check = 0;
	i = 0;
	sign = 1;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (!input[i])
		return (1);
	if (input[0] == '-')
		sign = -1;
	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			check = (check * 10) + input[i] - '0';
			if (sign * check < -2147483648 || sign * check > 2147483647)
				return (1);
			i++;
		}
		else
			return (1);
	}
	return (0);
}

int	ft_dice_roll(int number, int faces)
{
	int	roll;
	int	result;
	int	i;

	result = 0;
	i = 0;
	roll = 0;
	while (i < number)
	{
		do
			roll = rand();
		while
			(roll > (RAND_MAX - (RAND_MAX % faces)) + 1);
		result += (roll % faces) + 1;
		i++;
	}
	if (DEBUG == 1)
		ft_printf("The dice rolled %i on %i faces with %i amount of dice\n",
				result, faces, number);
	return (result);
}

int	ft_strcmp_dnd(char *string1, char *string2)
{
	if (!string1 || !string2)
		return (-1);
	while (*string1 && (*string1) == (*string2))
	{
		string1++;
		string2++;
	}
	return ((int)(*string1) - (int)(*string2));
}