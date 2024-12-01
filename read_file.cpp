#include "dnd_tools.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/nullptr.hpp"
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
        return (ft_nullptr);
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

char **ft_read_file_dnd(ft_file &file)
{
    char	**return_v = ft_nullptr;
    char	*line = ft_nullptr;
    int		i = 0;

    while (1)
    {
        line = get_next_line(file, false);
        if (!line)
            break ;
		if (DEBUG == 1)
			pf_printf("LINE = %s", line);
        i++;
        return_v = ft_realloc_dnd(return_v, i);
        if (!return_v)
        {
            cma_free(line);
			get_next_line(file, false);
			return (ft_nullptr);
        }
        return_v[i - 1] = line;
    }
    return (return_v);
}

char	**ft_open_and_read(const char *file_name)
{
	ft_file file(file_name, O_RDONLY);

	if (file.get_error_code())
	{
		pf_printf_fd(2, "error opening file %s: %s", file_name, file.get_error_message());
		return (ft_nullptr);
	}
	return (ft_read_file_dnd(file));
}
