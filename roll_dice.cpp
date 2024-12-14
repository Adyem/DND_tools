#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <climits>
#include <cstdlib>

int ft_dice_roll(int number, int faces)
{

    if (faces < 1 || number < 1)
        return (-1);
    if (faces == 1)
        return (number);
    int result = 0;
    int index = 0;
    int roll = 0;
    while (index < number)
    {
        roll = rand();
        if (result > INT_MAX - ((roll % faces) + 1))
            return -1;
        result += (roll % faces) + 1;
        index++;
    }
    if (DEBUG == 1)
        pf_printf_fd(2, "The dice rolled %d on %d faces with %d amount of dice\n", result, faces, number);
    return (result);
}

void ft_reroll(SharedPtr<t_char> info, int *result)
{
    int second_roll;

    if (DEBUG == 1)
        pf_printf_fd(2, "%s %d\n", info->name, *result);
    if (!info->flags.advantage)
        return ;
    second_roll = ft_dice_roll(1, 20);
    if (info->flags.advantage > 0)
    {
        pf_printf("%s rolled %d on his/her advantage\n", info->name, second_roll);
        if (second_roll > *result)
            *result = second_roll;
    }
    else if (info->flags.advantage < 0)
    {
        pf_printf("%s rolled %d on his/her disadvantage\n", info->name, second_roll);
        if (second_roll < *result)
            *result = second_roll;
    }
    return ;
}
