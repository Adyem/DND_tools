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

static void ft_handle_allocation_failure(char **lines)
{
    int index = 0;

    if (lines)
    {
        while (lines[index])
        {
            cma_free(lines[index]);
            index++;
        }
        cma_free(lines);
    }
    return;
}

static char **ft_reallocate_lines(char **lines, int new_size)
{
    int index = 0;
    char **new_lines = (char **)cma_calloc(new_size + 1, sizeof(char *), false);

    if (!new_lines)
    {
        ft_handle_allocation_failure(lines);
        return (ft_nullptr);
    }

    if (lines)
    {
        while (lines[index])
        {
            new_lines[index] = lines[index];
            index++;
        }
    }
    cma_free(lines);
    return (new_lines);
}

char **ft_read_file_lines(ft_file &file)
{
    char **lines = ft_nullptr;
    char *current_line = ft_nullptr;
    int line_count = 0;

    while (true)
    {
        current_line = get_next_line(file, false);
        if (!current_line)
            break;

        if (DEBUG == 1)
            pf_printf("LINE = %s", current_line);

        line_count++;
        lines = ft_reallocate_lines(lines, line_count);
        if (!lines)
        {
            cma_free(current_line);
            get_next_line(file, false);
            return (ft_nullptr);
        }
        lines[line_count - 1] = current_line;
    }
    return (lines);
}

char **ft_open_and_read_file(const char *file_name)
{
    ft_file file(file_name, O_RDONLY);

    if (file.get_error_code())
    {
        pf_printf_fd(2, "120-Error opening file %s: %s", file_name, file.get_error_message());
        return (ft_nullptr);
    }
    return (ft_read_file_lines(file));
}
