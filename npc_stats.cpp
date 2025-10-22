#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_file.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/JSon/document.hpp"
#include "dnd_tools.hpp"
#include "read_file_lines.hpp"

static char **ft_npc_load_json_lines(const char *filepath)
{
    json_document       document;
    json_group          *lines_group;
    json_item           *item;
    size_t              count;
    char                **content;
    size_t              index;

    if (document.read_from_file(filepath) != 0)
        return (ft_nullptr);
    lines_group = document.find_group("lines");
    if (!lines_group)
        return (ft_nullptr);
    count = 0;
    item = lines_group->items;
    while (item)
    {
        count++;
        item = item->next;
    }
    content = static_cast<char **>(cma_malloc(sizeof(char *) * (count + 1)));
    if (!content)
        return (ft_nullptr);
    index = 0;
    item = lines_group->items;
    while (item)
    {
        content[index] = cma_strdup(item->value);
        if (!content[index])
        {
            content[index] = ft_nullptr;
            cma_free_double(content);
            return (ft_nullptr);
        }
        index++;
        item = item->next;
    }
    content[index] = ft_nullptr;
    return (content);
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
