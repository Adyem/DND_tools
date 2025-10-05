#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
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
    turn_marker = 0;
    removed_turn = 0;
    while (content[index])
    {
        if (ft_strncmp(content[index], "--turn--", 8) == 0)
        {
            turn_marker = 1;
            temp = &content[index][8];
        }
        else
            temp = content[index];
        if ((ft_strncmp(info->name, temp, ft_strlen_size_t(info->name)) == 0)
                && (ft_strlen(temp) > ft_strlen(info->name))
                && (temp[ft_strlen(info->name)] == '=')
                && (ft_check_value(&temp[ft_strlen(info->name) + 1]) == FT_SUCCESS))
        {
            if (DEBUG == 1)
                pf_printf("found one %s and %c\n", content[index],
                        content[index][ft_strlen(info->name)]);
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
    char    *n_line;
    char    **content;
    int     i;
    int     added;
    int     error;

    if (DEBUG == 1)
        pf_printf("readding initiative %s %d\n", info->name, info->initiative);
    if (info->initiative <= 0)
        return ;
    content = ft_open_and_read_file("data/data--initiative", 1024);
    if (!content)
        return ;
    if (ft_initiative_check_content(info, content))
    {
        cma_free_double(content);
        pf_printf("%s is already in initiative\n", info->name);
        return ;
    }
    ft_file initiative_file("data/data--initiative", O_WRONLY | O_TRUNC);
    if (initiative_file == -1)
    {
        pf_printf("Error opening file: %s\n", initiative_file.get_error_str());
        cma_free_double(content);
        return ;
    }
    added = 0;
    i = 0;
    while (content[i])
    {
        n_line = ft_strchr(content[i], '\n');
        if (!n_line)
        {
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
        *n_line = '\0';
        if (DEBUG == 1)
            pf_printf("%s\n", content[i]);
        error = ft_initiative_check(info, content, i);
        if (DEBUG == 1)
            pf_printf("Error = %d\n", error);
        if (!added && error == 0)
        {
            pf_printf_fd(initiative_file, "%s=%d\n", info->name, info->initiative);
            added = 1;
        }
        if (error != 1 && error != 0)
        {
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
        pf_printf_fd(initiative_file, "%s\n", content[i]);
        i++;
    }
    if (added == 0)
    {
        pf_printf_fd(initiative_file, "%s=%d\n", info->name, info->initiative);
        added = 1;
    }
    cma_free_double(content);
    if (DEBUG == 1)
        pf_printf("added = %d\n", added);
    return ;
}
