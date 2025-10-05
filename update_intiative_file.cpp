#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

int ft_initiative_remove(t_char * info)
{
    char    *temp;
    char    **content;
    int     turn_marker;
    int     removed_turn;

    if (DEBUG == 1)
        pf_printf("removing initiative %s\n", info->name);
    if (access("data/data--initiative", F_OK) == -1)
    {
        if (DEBUG == 1)
            pf_printf("File does not exist: data/data--initiative\n");
        return (0);
    }
    content = ft_open_and_read_file("data/data--initiative", 1024);
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
        if ((ft_strncmp(info->name, temp, name_len) == 0)
                && (ft_strlen(temp) > name_len)
                && (temp[name_len] == '='))
        {
            char    *value;
            char    *newline;
            char    saved_char;
            int     check_result;

            value = &temp[name_len + 1];
            newline = ft_strchr(value, '\n');
            saved_char = '\0';
            if (newline)
            {
                saved_char = *newline;
                *newline = '\0';
            }
            check_result = ft_check_value(value);
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
    typedef struct s_validated_line
    {
        char    *line;
        char    *newline_mark;
        int     check_result;
    }   t_validated_line;
    t_validated_line   *validated;

    if (DEBUG == 1)
        pf_printf("readding initiative %s %d\n", info->name, info->initiative);
    if (info->initiative <= 0)
        return ;
    content = ft_open_and_read_file("data/data--initiative", 1024);
    if (content == ft_nullptr)
    {
        if (ft_errno == ER_SUCCESS || ft_errno == FILE_END_OF_FILE
                || ft_errno == FILE_INVALID_FD
                || ft_errno == ERRNO_OFFSET + ENOENT)
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
            return ;
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
    validated = NULL;
    if (count > 0)
    {
        validated = (t_validated_line *)malloc(sizeof(t_validated_line) * count);
        if (!validated)
        {
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
    }
    i = 0;
    turn_marker_present = 0;
    while (i < count)
    {
        validated[i].line = content[i];
        validated[i].newline_mark = ft_strchr(content[i], '\n');
        if (!validated[i].newline_mark)
        {
            if (validated)
                free(validated);
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
        *validated[i].newline_mark = '\0';
        if (ft_strncmp(validated[i].line, "--turn--", 8) == 0)
            turn_marker_present = 1;
        error = ft_initiative_check(info, content, i);
        if (DEBUG == 1)
            pf_printf("%s\n", content[i]);
        if (DEBUG == 1)
            pf_printf("Error = %d\n", error);
        if (error != 0 && error != 1)
        {
            if (validated)
                free(validated);
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
            free(validated);
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
        *validated[i].newline_mark = '\n';
        i++;
    }
    if (validated)
        free(validated);
    cma_free_double(content);
    if (DEBUG == 1)
        pf_printf("added = %d\n", added);
    return ;
}
