#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_file.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/JSon/document.hpp"
#include "libft/Template/vector.hpp"
#include "dnd_tools.hpp"
#include "read_file_lines.hpp"

static int ft_append_json_line(ft_vector<ft_string> &lines, const char *value)
{
    ft_string   line(value);

    if (line.get_error() != ER_SUCCESS)
    {
        ft_errno = line.get_error();
        return (-1);
    }
    lines.push_back(line);
    if (lines.get_error() != ER_SUCCESS)
    {
        ft_errno = lines.get_error();
        return (-1);
    }
    return (0);
}

static char **ft_duplicate_json_lines(ft_vector<ft_string> &lines)
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
        size_t  cleanup_index;

        cleanup_index = 0;
        while (cleanup_index < line_count)
        {
            if (content[cleanup_index])
                cma_free(content[cleanup_index]);
            cleanup_index++;
        }
        cma_free(content);
        return (ft_nullptr);
    }
    content[index] = ft_nullptr;
    return (content);
}

static char **ft_npc_load_json_lines(const char *filepath)
{
    json_document       document;
    json_group          *lines_group;
    json_item           *item;
    ft_vector<ft_string>    lines(8);

    if (document.read_from_file(filepath) != 0)
        return (ft_nullptr);
    lines_group = document.find_group("lines");
    if (!lines_group)
        return (ft_nullptr);
    item = lines_group->items;
    while (item)
    {
        if (ft_append_json_line(lines, item->value) != 0)
        {
            lines.clear();
            return (ft_nullptr);
        }
        item = item->next;
    }
    return (ft_duplicate_json_lines(lines));
}

static char **ft_npc_load_legacy_lines(const char *filepath)
{
    ft_file info_file(filepath, O_RDONLY);
    char    **content;

    if (info_file.get_error())
    {
        pf_printf_fd(2, "1-Error opening file %s: %s\n", filepath, info_file.get_error_str());
        return (ft_nullptr);
    }
    if (DEBUG == 1)
        pf_printf("Opening file %s on fd %d\n", filepath, info_file.get_fd());
    content = ft_read_file_lines_fd(info_file.get_fd(), 1024);
    if (!content)
        pf_printf_fd(2, "1-Error reading legacy save %s\n", filepath);
    return (content);
}

int ft_npc_open_file(t_char * info)
{
    char    **content;
    int     error;

    content = ft_npc_load_json_lines(info->save_file);
    if (!content)
    {
        content = ft_npc_load_legacy_lines(info->save_file);
        if (!content)
            return (1);
    }
    error = ft_initialize_info(info, content);
    cma_free_double(content);
    if (info->flags.error || error)
        return (1);
    if (ft_npc_check_info(info))
        return (1);
    return (0);
}

void ft_npc_change_stats(t_char * info, const int argument_count, const char **argument_vector)
{
    int input_index = 0;

    while (DEBUG == 1 && argument_vector[input_index])
    {
        pf_printf("%s\n", argument_vector[input_index]);
        input_index++;
    }
    input_index = 0;
    if (argument_count == 1)
    {
        if (info->turn)
            info->turn(info);
        else
            pf_printf("%s doesn't take any actions on his/her turn\n", info->name);
    }
    else if (argument_count == 2)
        ft_npc_sstuff(info, argument_vector);
    else if (argument_count == 3)
        ft_npc_set_stat(info, argument_vector);
    else if ((argument_count == 4 || argument_count == 5) &&
        ((ft_strcmp(argument_vector[1], "add") == 0) ||
        (ft_strcmp(argument_vector[1], "remove") == 0)) &&
        ft_strcmp(argument_vector[2], "stack") == 0 &&
        ft_strcmp(argument_vector[3], "growth") == 0)
            ft_growth_stack(info, argument_vector, argument_count);
    else if (argument_count == 4)
        ft_change_stats_04(info, argument_vector);
    else
        pf_printf_fd(2, "146-Error Too many arguments given\n");
    if (info->flags.alreaddy_saved == 1)
        return ;
    ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file.get_error())
    {
        pf_printf_fd(2, "145-Error opening file %s: %s\n", info->save_file,
        file.get_error_str());
    }
    ft_npc_write_file(info, &info->stats, &info->d_resistance, file);
    return ;
}
