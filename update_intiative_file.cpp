#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/File/file_utils.hpp"
#include "dnd_tools.hpp"
#include "read_file_lines.hpp"

int ft_initiative_remove(t_char * info)
{
    char    *temp;
    char    **content;
    int     turn_marker;
    int     removed_turn;

    if (DEBUG == 1)
        pf_printf("removing initiative %s\n", info->name);
    if (file_exists("data/data--initiative") != 1)
    {
        if (DEBUG == 1)
            pf_printf("File does not exist: data/data--initiative\n");
        return (0);
    }
    ft_file read_file("data/data--initiative", O_RDONLY);
    if (read_file.get_error())
        return (0);
    content = ft_read_file_lines_fd(read_file.get_fd(), 1024);
    if (!content)
        return (0);
    ft_file initiative_file("data/data--initiative", O_WRONLY | O_TRUNC);
    if (initiative_file.get_error())
    {
        pf_printf("Error opening file: %s\n", initiative_file.get_error_str());
        cma_free_double(content);
        return (0);
    }
    int index = 0;
    size_t  name_len;
    turn_marker = 0;
    removed_turn = 0;
    name_len = ft_strlen(info->name);
    while (content[index])
    {
        if (ft_strncmp(content[index], "--turn--", 8) == 0)
        {
            turn_marker = 1;
            temp = &content[index][8];
        }
        else
            temp = content[index];
        size_t  temp_length;

        temp_length = static_cast<size_t>(ft_strlen(temp));
        if ((ft_strncmp(info->name, temp, name_len) == 0)
                && (temp_length > name_len)
                && (temp[name_len] == '='))
        {
            char    *value;
            char    *newline;
            char    saved_char;
            char    *carriage_return;
            char    saved_carriage;
            size_t  value_len;
            int     check_result;

            value = &temp[name_len + 1];
            newline = ft_strchr(value, '\n');
            saved_char = '\0';
            carriage_return = ft_nullptr;
            saved_carriage = '\0';
            if (newline)
            {
                saved_char = *newline;
                *newline = '\0';
            }
            value_len = ft_strlen(value);
            if (value_len > 0)
            {
                if (value[value_len - 1] == '\r')
                {
                    carriage_return = &value[value_len - 1];
                    saved_carriage = *carriage_return;
                    *carriage_return = '\0';
                }
            }
            check_result = ft_check_value(value);
            if (carriage_return)
                *carriage_return = saved_carriage;
            if (newline)
                *newline = saved_char;
            if (check_result == FT_SUCCESS)
            {
                if (DEBUG == 1)
                    pf_printf("found one %s and %c\n", content[index],
                            content[index][name_len]);
                index++;
                if (turn_marker)
                {
                    removed_turn = 1;
                    if (content[index])
                        pf_printf_fd(initiative_file, "--turn--");
                    turn_marker = 0;
                }
                continue ;
            }
        }
        pf_printf_fd(initiative_file, "%s", content[index]);
        turn_marker = 0;
        index++;
    }
    cma_free_double(content);
    return (removed_turn);
}

static int ft_initiative_check(t_char * info, char **content, int i)
{
    char    *mark;
    int     initiative;

    mark = ft_strchr(content[i], '=');
    if (!mark)
        return (2);
    mark++;
    if (ft_check_value(mark))
        return (2);
    initiative = ft_atoi(mark);
    if (info->initiative > initiative)
        return (0);
    return (1);
}

static int ft_initiative_check_content(t_char * info, char **content)
{
    int     index = 0;
    size_t  name_len = 0;

    while (info->name[name_len])
        name_len++;
    while (content[index])
    {
        char    *line;
        size_t  j;

        line = content[index];
        if (ft_strncmp(line, "--turn--", 8) == 0)
            line = line + 8;
        j = 0;
        while (j < name_len && line[j] && line[j] == info->name[j])
            j++;
        if (j == name_len)
        {
            if (line[j] == '=' || line[j] == '\0')
                return (1);
        }
        index++;
    }
    return (0);
}

void ft_initiative_add(t_char * info)
{
    char    **content;
    int     i;
    int     added;
    int     error;
    int     count;
    int     turn_marker_present;
    int     turn_marker_count;
    typedef struct s_validated_line
    {
        char    *line;
        char    *newline_mark;
        char    saved_newline;
        char    *carriage_mark;
        char    saved_carriage;
        int     check_result;
    }   t_validated_line;
    t_validated_line   *validated;

    if (DEBUG == 1)
        pf_printf("readding initiative %s %d\n", info->name, info->initiative);
    if (info->initiative <= 0)
        return ;
    if (file_exists("data/data--initiative") != 1)
    {
        content = static_cast<char **>(cma_calloc(1, sizeof(char *)));
        if (!content)
        {
            pf_printf("Error: failed to allocate initiative buffer\n");
            return ;
        }
        ft_errno = ER_SUCCESS;
    }
    else
    {
        ft_file read_file("data/data--initiative", O_RDONLY);

        if (read_file.get_error())
            return ;
        content = ft_read_file_lines_fd(read_file.get_fd(), 1024);
        if (!content)
        {
            if (ft_errno != ER_SUCCESS)
                return ;
            content = static_cast<char **>(cma_calloc(1, sizeof(char *)));
            if (!content)
            {
                pf_printf("Error: failed to allocate initiative buffer\n");
                return ;
            }
            ft_errno = ER_SUCCESS;
        }
    }
    if (ft_initiative_check_content(info, content))
    {
        cma_free_double(content);
        pf_printf("%s is already in initiative\n", info->name);
        return ;
    }
    count = 0;
    while (content[count])
        count++;
    validated = ft_nullptr;
    if (count > 0)
    {
        validated = static_cast<t_validated_line *>(cma_malloc(sizeof(t_validated_line) * count));
        if (!validated)
        {
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
    }
    i = 0;
    turn_marker_present = 0;
    turn_marker_count = 0;
    size_t  line_len;

    while (i < count)
    {
        validated[i].line = content[i];
        validated[i].newline_mark = ft_strchr(content[i], '\n');
        if (!validated[i].newline_mark)
        {
            if (validated)
                cma_free(validated);
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
        validated[i].saved_newline = *validated[i].newline_mark;
        *validated[i].newline_mark = '\0';
        validated[i].carriage_mark = ft_nullptr;
        validated[i].saved_carriage = '\0';
        line_len = ft_strlen(validated[i].line);
        if (line_len > 0)
        {
            if (validated[i].line[line_len - 1] == '\r')
            {
                validated[i].carriage_mark = &validated[i].line[line_len - 1];
                validated[i].saved_carriage = *validated[i].carriage_mark;
                *validated[i].carriage_mark = '\0';
            }
        }
        if (ft_strncmp(validated[i].line, "--turn--", 8) == 0)
        {
            turn_marker_count++;
            if (turn_marker_count > 1)
            {
                if (validated)
                    cma_free(validated);
                cma_free_double(content);
                pf_printf("Error: data--initiative file is corrupted\n");
                return ;
            }
            turn_marker_present = 1;
        }
        error = ft_initiative_check(info, content, i);
        if (DEBUG == 1)
            pf_printf("%s\n", content[i]);
        if (DEBUG == 1)
            pf_printf("Error = %d\n", error);
        if (error != 0 && error != 1)
        {
            if (validated)
                cma_free(validated);
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
        validated[i].check_result = error;
        i++;
    }
    ft_file initiative_file("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR);
    if (initiative_file == -1)
    {
        if (validated)
            cma_free(validated);
        cma_free_double(content);
        pf_printf("Error opening file: %s\n", initiative_file.get_error_str());
        return ;
    }
    added = 0;
    i = 0;
    while (i < count)
    {
        if (!added && validated[i].check_result == 0)
        {
            if (turn_marker_present == 0)
            {
                pf_printf_fd(initiative_file, "--turn--");
                turn_marker_present = 1;
            }
            pf_printf_fd(initiative_file, "%s=%d\n", info->name, info->initiative);
            added = 1;
        }
        pf_printf_fd(initiative_file, "%s\n", validated[i].line);
        i++;
    }
    if (added == 0)
    {
        if (turn_marker_present == 0)
        {
            pf_printf_fd(initiative_file, "--turn--");
            turn_marker_present = 1;
        }
        pf_printf_fd(initiative_file, "%s=%d\n", info->name, info->initiative);
        added = 1;
    }
    i = 0;
    while (i < count)
    {
        if (validated[i].carriage_mark)
            *validated[i].carriage_mark = validated[i].saved_carriage;
        *validated[i].newline_mark = validated[i].saved_newline;
        i++;
    }
    if (validated)
        cma_free(validated);
    cma_free_double(content);
    if (DEBUG == 1)
        pf_printf("added = %d\n", added);
    return ;
}
