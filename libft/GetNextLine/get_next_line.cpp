#include "../Libft/libft.hpp"
#include "../CMA/CMA.hpp"
#include "../CPP_class/nullptr.hpp"
#include <cstdio>
#include "get_next_line.hpp"

static char* allocate_new_string(char* string_1, char* string_2)
{
    int total_len = 0;
    char* new_str;

    if (string_1)
        total_len += ft_strlen(string_1);
    if (string_2)
        total_len += ft_strlen(string_2);
    new_str = (char*)cma_malloc(total_len + 1);
    if (!new_str)
        return ft_nullptr;
    return new_str;
}

char* ft_strjoin_gnl(char* string_1, char* string_2)
{
    char* result;
    char* original_string = string_1;
    int index;

    if (!string_1 && !string_2)
        return ft_nullptr;
    result = allocate_new_string(string_1, string_2);
    if (!result)
        return ft_nullptr;
    index = 0;
    if (string_1)
        while (*string_1)
            result[index++] = *string_1++;
    if (string_2)
        while (*string_2)
            result[index++] = *string_2++;
    result[index] = '\0';
    cma_free(original_string);
    return result;
}

char* leftovers(char* readed_string)
{
    int read_index = 0;
    int write_index = 0;
    char* string;

    while (readed_string[read_index] && readed_string[read_index] != '\n')
        read_index++;
    if (!readed_string[read_index])
    {
        cma_free(readed_string);
        return ft_nullptr;
    }
    string = (char*)cma_malloc(ft_strlen(readed_string) - read_index + 1);
    if (!string)
        return ft_nullptr;
    read_index++;
    while (readed_string[read_index])
        string[write_index++] = readed_string[read_index++];
    string[write_index] = '\0';
    cma_free(readed_string);
    return string;
}

char* malloc_gnl(char* readed_string, size_t i)
{
    char* string;

    if (readed_string && readed_string[i] == '\n')
        string = (char*)cma_malloc(i + 2);
    else
        string = (char*)cma_malloc(i + 1);
    if (!string)
        return ft_nullptr;
    return string;
}

char* fetch_line(char* readed_string)
{
    size_t index = 0;
    char* string;

    if (!readed_string[index])
        return ft_nullptr;
    while (readed_string[index] && readed_string[index] != '\n')
        index++;
    string = malloc_gnl(readed_string, index);
    if (!string)
        return ft_nullptr;
    index = 0;
    while (readed_string[index] && readed_string[index] != '\n')
    {
        string[index] = readed_string[index];
        index++;
    }
    if (readed_string[index] == '\n')
    {
        string[index] = '\n';
        index++;
    }
    string[index] = '\0';
    return string;
}

char* read_fd(ft_file& file, char* readed_string)
{
    char* buffer;
    ssize_t readed_bytes;

    buffer = (char*)cma_malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return ft_nullptr;
    readed_bytes = 1;
    while (!ft_strchr(readed_string, '\n') && readed_bytes != 0)
    {
        readed_bytes = file.read(buffer, BUFFER_SIZE);
        if (readed_bytes == -1)
        {
            cma_free(buffer);
            cma_free(readed_string);
            return ft_nullptr;
        }
        buffer[readed_bytes] = '\0';
        readed_string = ft_strjoin_gnl(readed_string, buffer);
        if (!readed_string)
        {
            cma_free(buffer);
            return ft_nullptr;
        }
    }
    cma_free(buffer);
    return readed_string;
}

char	*get_next_line(ft_file &file)
{
	char		*string = ft_nullptr;
	static char	*readed_string[4096];
	int			index = 0;

	while (file == -1 && index < 4096)
	{
		free(readed_string[index]);
		readed_string[index] = nullptr;
		index++;
	}
	if (BUFFER_SIZE <= 0 || file < 0)
		return (nullptr);
	readed_string[file] = read_fd(file, readed_string[file]);
	if (!readed_string[file])
		return (nullptr);
	string = fetch_line(readed_string[file]);
	readed_string[file] = leftovers(readed_string[file]);
	return (string);
}
