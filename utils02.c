#include "dnd_tools.h"

int	ft_dice_roll(int number, int faces)
{
	int	roll;
	int	result;
	int	i;

	if (faces == 1)
		return (number);
	if (faces < 1 || number < 1)
		return (0);
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

void	ft_reroll(t_char *info, int *result)
{
	int second_roll;
	if (info->advantage > 0)
	{
		second_roll = ft_dice_roll(1, 20);
		if (second_roll > *result)
			*result = second_roll;
	}
	else if (info->advantage < 0)
	{
		second_roll = ft_dice_roll(1, 20);
		if (second_roll < *result)
			*result = second_roll;
	}
	return ;
}

int	ft_double_char_length(char **double_char)
{
	int	i;

	if (!double_char)
		return(0);
	i = 0;
	while (double_char[i])
		i++;
	return (i);
}
