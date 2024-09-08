#include "dnd_tools.hpp"
#include <climits>
#include <iostream>

int ft_dice_roll(int number, int faces)
{
    int roll;
    int result;
    int i;

	if (faces < 1 || number < 1)
		return (-1);
	if (faces == 1)
		return (number);
    result = 0;
    i = 0;
    roll = 0;
    while (i < number)
    {
        roll = rand();
        if (result > INT_MAX - ((roll % faces) + 1))
            return -1;
        result += (roll % faces) + 1;
        i++;
    }
    if (DEBUG == 1)
        std::cerr << "The dice rolled " << result << " on " << faces 
                  << " faces with " << number << " amount of dice" << std::endl;
    return (result);
}

void ft_reroll(t_char *info, int *result)
{
    int second_roll;

    if (DEBUG == 1)
        std::cerr << info << " " << result << std::endl;
    if (!info->flags.advantage)
        return ;
    second_roll = ft_dice_roll(1, 20);
    if (info->flags.advantage > 0)
    {
        std::cout << info->name << " rolled " << second_roll << " on his/her advantage" 
                  << std::endl;
        if (second_roll > *result)
            *result = second_roll;
    }
    else if (info->flags.advantage < 0)
    {
        std::cout << info->name << " rolled " << second_roll 
                  << " on his/her disadvantage" << std::endl;
        if (second_roll < *result)
            *result = second_roll;
    }
    return ;
}
