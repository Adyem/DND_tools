#include "read_file_lines.hpp"
#include "libft/CPP_class/class_fd_istream.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/GetNextLine/get_next_line.hpp"

char    **ft_read_file_lines_fd(int file_descriptor, size_t buffer_size)
{
    ft_fd_istream   input(file_descriptor);
    char            **lines;

    if (buffer_size == 0)
        buffer_size = 1024;
    lines = ft_read_file_lines(input, buffer_size);
    if (!lines)
        return (ft_nullptr);
    return (lines);
}

