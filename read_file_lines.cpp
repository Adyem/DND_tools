#include "read_file_lines.hpp"
#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/CPP_class/class_fd_istream.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/Template/vector.hpp"

static void ft_clear_partial_lines(char **lines, size_t count)
{
    size_t  index;

    if (!lines)
        return ;
    index = 0;
    while (index < count)
    {
        if (lines[index])
            cma_free(lines[index]);
        index++;
    }
    cma_free(lines);
    return ;
}

static char **ft_duplicate_lines(ft_vector<ft_string> &lines)
{
    size_t  line_count;
    char    **content;
    size_t  index;

    line_count = lines.size();
    if (lines.get_error() != ER_SUCCESS)
    {
        ft_errno = lines.get_error();
        return (ft_nullptr);
    }
    content = static_cast<char **>(cma_calloc(line_count + 1, sizeof(char *)));
    if (!content)
    {
        ft_errno = FT_ERR_NO_MEMORY;
        return (ft_nullptr);
    }
    index = 0;
    while (index < line_count)
    {
        const ft_string   &entry = lines[index];

        if (lines.get_error() != ER_SUCCESS)
        {
            ft_errno = lines.get_error();
            break ;
        }
        content[index] = cma_strdup(entry.c_str());
        if (!content[index])
        {
            ft_errno = FT_ERR_NO_MEMORY;
            break ;
        }
        index++;
    }
    if (index < line_count)
    {
        ft_clear_partial_lines(content, line_count);
        return (ft_nullptr);
    }
    content[line_count] = ft_nullptr;
    ft_errno = ER_SUCCESS;
    return (content);
}

char    **ft_read_file_lines_fd(int file_descriptor, size_t buffer_size)
{
    ft_vector<ft_string>    lines(8);
    ft_fd_istream           stream(file_descriptor);
    char                    *line;

    if (file_descriptor < 0)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (ft_nullptr);
    }
    if (buffer_size == 0)
        buffer_size = 1024;
    line = get_next_line(stream, buffer_size);
    while (line)
    {
        ft_string   entry(line);

        cma_free(line);
        if (entry.get_error() != ER_SUCCESS)
        {
            ft_errno = entry.get_error();
            lines.clear();
            return (ft_nullptr);
        }
        lines.push_back(entry);
        if (lines.get_error() != ER_SUCCESS)
        {
            ft_errno = lines.get_error();
            lines.clear();
            return (ft_nullptr);
        }
        line = get_next_line(stream, buffer_size);
    }
    return (ft_duplicate_lines(lines));
}

