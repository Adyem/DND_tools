#include "../Libft/libft.hpp"
#include "../CMA/CMA.hpp"
#include "../CPP_class/nullptr.hpp"
#include <cstdio>
#include "get_next_line.hpp"

static char	*allocate_new_string(char *string_1, char *string_2, bool critical)
{
	int		total_len;
	char	*new_str;

	total_len = 0;
	if (string_1)
		total_len += ft_strlen(string_1);
	if (string_2)
		total_len += ft_strlen(string_2);
	new_str = (char *)cma_malloc(total_len + 1, critical);
	if (!new_str)
		return (ft_nullptr);
	return (new_str);
}

char *ft_strjoin_gnl(char *string_1, char *string_2, bool critical)
{
    char *result;
    char *original_string;
    int i;
    char *temp1 = string_1;
    char *temp2 = string_2;

    if (!string_1 && !string_2)
        return (ft_nullptr);
    original_string = string_1;
    result = allocate_new_string(string_1, string_2, critical);
    if (!result)
        return (ft_nullptr);
    i = 0;
    if (temp1)
        while (*temp1)
            result[i++] = *temp1++;
    if (temp2)
        while (*temp2)
            result[i++] = *temp2++;
    result[i] = '\0';
    cma_free(original_string);
    return (result);
}

char *get_next_line(int fd, bool critical) {
    if (fd < 0)
        return (ft_nullptr);
    size_t buffer_size = 128;
    size_t position = 0;
    char *buffer = (char *)cma_malloc(buffer_size * sizeof(char), critical);
    if (!buffer)
        return (ft_nullptr);

    while (true)
	{
        char ch;
        ssize_t bytes_read = read(fd, &ch, 1);
		if (bytes_read == -1)
		{
            cma_free(buffer);
            return (ft_nullptr);
		}
		else if (bytes_read == 0)
            break ;
		else
		{
            buffer[position++] = ch;
            if (position >= buffer_size)
			{
                size_t new_buffer_size = buffer_size * 2;
                char *new_buffer = (char *)cma_realloc(buffer, new_buffer_size
						* sizeof(char), critical);
                if (!new_buffer)
				{
                    cma_free(buffer);
                    return (ft_nullptr);
                }
                buffer = new_buffer;
                buffer_size = new_buffer_size;
            }
			if (ch == '\n')
				break ;
        }
    }
    if (position == 0)
	{
        cma_free(buffer);
        return (ft_nullptr);
    }
    buffer[position] = '\0';
    char *result = (char *)cma_realloc(buffer, (position + 1) * sizeof(char), critical);
    if (!result)
		return (buffer);
    return (result);
}
