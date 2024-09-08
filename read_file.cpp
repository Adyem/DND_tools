#include "dnd_tools.hpp"
#include "libft/get_next_line/get_next_line.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>

static void ft_malloc_fail_gnl_dnd(char **return_v, int fd)
{
    int	i;

    close(fd);
    i = 0;
    if (return_v)
    {
        while (return_v[i])
        {
            free(return_v[i]);
            i++;
        }
        free(return_v);
    }
	return ;
}

static char **ft_realloc_dnd(char **return_v, int index, int fd)
{
    int		i;
    char	**temp;

    i = 0;
    temp = (char **)calloc(index + 1, sizeof(char *));
    if (!temp)
    {
        ft_malloc_fail_gnl_dnd(return_v, fd);
        return nullptr;
    }
    if (return_v)
    {
        while (return_v[i])
        {
            temp[i] = return_v[i];
            i++;
        }
    }
    free(return_v);
    return (temp);
}

char **ft_read_file_dnd(int fd)
{
    char	**return_v = nullptr;
    char	*line = nullptr;
    int		i = 0;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        i++;
        return_v = ft_realloc_dnd(return_v, i, fd);
        if (!return_v)
        {
            free(line);
            return (nullptr);
        }
        return_v[i - 1] = line;
    }
    return (return_v);
}

static void ft_print_file(char **content)
{
    int i;

    if (content && DEBUG == 1)
    {
        i = 0;
        while (content[i])
        {
            std::cout << content[i];
            i++;
        }
        std::cout << std::endl;
    }
	return ;
}

char **ft_open_and_read(const char *file)
{
    int		fd;
    char	**content;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        return (nullptr);
    }
    content = ft_read_file_dnd(fd);
    close(fd);
    ft_print_file(content);
    if (!content)
    {
        get_next_line(-1);
        std::cerr << "Error allocating memory for content inside file" << std::endl;
    }
    return (content);
}
