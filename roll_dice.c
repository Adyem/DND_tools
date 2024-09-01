#include "dnd_tools.h"

int	ft_dice_roll(int number, int faces)
{
	int	roll;
	int	result;
	int	i;

	if (faces == 1)
		return (number);
	if (faces < 1 || number < 1)
		return (-1);
	result = 0;
	i = 0;
	roll = 0;
	while (i < number)
	{
		roll = rand();
		if (result > INT_MAX - ((roll % faces) + 1))
			return (-1);
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

	if (DEBUG == 1)
		ft_printf("%p %p\n", info, result);
	if (!info->flags.advantage)
		return ;
	second_roll = ft_dice_roll(1, 20);
	if (info->flags.advantage > 0)
	{
		ft_printf("%s rolled %i on his/her advantage\n", info->name, second_roll);
		if (second_roll > *result)
			*result = second_roll;
	}
	else if (info->flags.advantage < 0)
	{
		ft_printf("%s rolled %i on his/her disadvantage\n", info->name, second_roll);
		if (second_roll < *result)
			*result = second_roll;
	}
	return ;
}
