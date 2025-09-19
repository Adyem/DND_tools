#include "dnd_tools.hpp"
#include <limits>

int    ft_check_value(const char *input)
{
    long    number = 0;
    int        index = 0;
    int        sign = 1;

    if (input[index] == '+' || input[index] == '-')
        index++;
    if (!input[index])
        return (1);
    if (input[0] == '-')
        sign = -1;
    while (input[index])
    {
        if (input[index] >= '0' && input[index] <= '9')
        {
            number = (number * 10) + input[index] - '0';
            long signed_number = sign * number;
            if (signed_number < std::numeric_limits<int>::min()
                    || signed_number > std::numeric_limits<int>::max())
                return (2);
            index++;
        }
        else
            return (3);
    }
    return (0);
}
