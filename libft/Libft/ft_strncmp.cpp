#include <unistd.h>

int ft_strncmp(const char *string_1, const char *string_2, size_t max_len)
{
    unsigned int current_index;

    current_index = 0;
    while (string_1[current_index] != '\0' && string_2[current_index] != '\0' && current_index < max_len)
    {
        if ((unsigned char)string_1[current_index] != (unsigned char)string_2[current_index])
            return ((unsigned char)string_1[current_index] - (unsigned char)string_2[current_index]);
        current_index++;
    }
    if (current_index == max_len)
        return (0);
    return ((unsigned char)string_1[current_index] - (unsigned char)string_2[current_index]);
}
