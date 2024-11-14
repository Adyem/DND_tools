#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>

int ft_double_char_length(const char **double_char)
{
    int i;

    if (!double_char)
        return (0);
    i = 0;
    while (double_char[i])
        i++;
    return (i);
}
