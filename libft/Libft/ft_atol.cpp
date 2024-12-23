#include "libft.hpp"

long ft_atol(const char *string)
{
    long index = 0;
    long sign = 1;
    unsigned long result = 0;

    while (string[index] == ' ' || (string[index] >= '\t' && string[index] <= '\r'))
        index++;
    if (string[index] == '+' || string[index] == '-')
    {
        if (string[index] == '-')
            sign = -1;
        index++;
    }
    while (string[index] >= '0' && string[index] <= '9')
    {
        result = (result * 10) + (string[index] - '0');
        index++;
    }
    return (result * sign);
}
