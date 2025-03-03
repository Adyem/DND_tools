#include <climits>
#include "dice_roll.hpp"
#include "../Printf/printf.hpp"

bool g_srand_init = false;

int ft_dice_roll(int number, int faces)
{
	ft_init_srand();
	if (faces == 0 && number == 0)
		return (0);
	else if (faces < 1 || number < 1)
        return (-1);
	else if (faces == 1)
        return (number);
    int result = 0;
    int index = 0;
    int roll = 0;
    while (index < number)
    {
        roll = rand();
        if (result > INT_MAX - ((roll % faces) + 1))
            return (-1);
        result += (roll % faces) + 1;
        index++;
    }
    if (DEBUG == 1)
        pf_printf_fd(2, "The dice rolled %d on %d faces with %d amount of dice\n",
				result, faces, number);
    return (result);
}
