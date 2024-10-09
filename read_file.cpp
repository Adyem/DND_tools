#include "dnd_tools.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

static void ft_malloc_fail_gnl_dnd(char **return_v)
{
    int	i;

    i = 0;
    if (return_v)
    {
        while (return_v[i])
        {
            cma_free(return_v[i]);
            i++;
        }
        cma_free(return_v);
    }
	return ;
}

static char **ft_realloc_dnd(char **return_v, int index)
{
    int		i;
    char	**temp;

    i = 0;
    temp = (char **)cma_calloc(index + 1, sizeof(char *), false);
    if (!temp)
    {
        ft_malloc_fail_gnl_dnd(return_v);
        return (nullptr);
    }
    if (return_v)
    {
        while (return_v[i])
        {
            temp[i] = return_v[i];
            i++;
        }
    }
    cma_free(return_v);
    return (temp);
}

char **ft_read_file_dnd(int fd)
{
    char	**return_v = nullptr;
    char	*line = nullptr;
    int		i = 0;

    while (1)
    {
        line = get_next_line(fd, false);
        if (!line)
            break;
        i++;
        return_v = ft_realloc_dnd(return_v, i);
        if (!return_v)
        {
            cma_free(line);
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
            ft_printf("%s", content[i]);
            i++;
        }
        ft_printf("\n");
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
        ft_printf_fd(2, "Error opening file: %s\n", strerror(errno));
        return (nullptr);
    }
    content = ft_read_file_dnd(fd);
    close(fd);
    ft_print_file(content);
    if (!content)
    {
        get_next_line(-1, false);
        ft_printf_fd(2, "Error allocating memory for content inside file\n");
    }
    return (content);
}
