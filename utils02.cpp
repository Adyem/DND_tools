#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>

int ft_double_char_length(const char **double_char)
{
    if (!double_char)
        return (0);
    int index = 0;
    while (double_char[index])
        index++;
    return (index);
}
