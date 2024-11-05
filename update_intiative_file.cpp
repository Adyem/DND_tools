#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp" // Including the pf_printf header
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

void ft_initiative_remove(t_char *info)
{
    char    *temp;
    char    **content;
    int     turn_marker;
    int     i;
    int     fd;

    if (DEBUG == 1)
        pf_printf("removing initiative %s\n", info->name);
    if (access("data/data--initiative", F_OK) == -1)
    {
        if (DEBUG == 1)
            pf_printf("File does not exist: data/data--initiative\n");
        return ;
    }
    content = ft_open_and_read("data/data--initiative");
    if (!content)
        return ;
    i = 0;
    fd = open("data/data--initiative", O_WRONLY | O_TRUNC);
    if (fd == -1)
    {
        pf_printf("Error opening file: %s\n", strerror(errno));
        cma_free_double(content);
        return ;
    }
    i = 0;
    turn_marker = 0;
    while (content[i])
    {
        if (ft_strncmp(content[i], "--turn--", 8) == 0)
        {
            turn_marker = 1;
            temp = &content[i][8];
        }
        else
            temp = content[i];
        if ((ft_strncmp(info->name, temp, ft_strlen(info->name)) == 0)
                && (ft_strlen(temp) > ft_strlen(info->name))
                && (temp[ft_strlen(info->name)] == '=')
                && (ft_check_value(&temp[ft_strlen(info->name) + 1])))
        {
            if (DEBUG == 1)
                pf_printf("found one %s and %c\n", content[i], content[i][ft_strlen(info->name)]);
            i++;
            if (turn_marker)
                pf_printf_fd(fd, "--turn--");
            continue ;
        }
        pf_printf_fd(fd, "%s", content[i]);
        turn_marker = 0;
        i++;
    }
    close(fd);
    cma_free_double(content);
    return ;
}

static int ft_initiative_check(t_char *info, char **content, int i)
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

static int ft_initiative_check_content(t_char *info, char **content)
{
    int i = 0;

    while (content[i])
    {
        if (ft_strncmp(content[i], info->name, ft_strlen(info->name)) == 0)
            return (1);
        i++;
    }
    return (0);
}

void ft_initiative_add(t_char *info)
{
    char    *n_line;
    char    **content;
    int     i;
    int     added;
    int     error;
    int     fd;

    if (DEBUG == 1)
        pf_printf("readding initiative %s %d\n", info->name, info->initiative);
    if (info->initiative <= 0)
        return ;
    content = ft_open_and_read("data/data--initiative");
    if (!content)
        return ;
    if (ft_initiative_check_content(info, content))
    {
        cma_free_double(content);
        pf_printf("%s is already in initiative\n", info->name);
        return ;
    }
    fd = open("data/data--initiative", O_WRONLY | O_TRUNC);
    if (fd == -1)
    {
        pf_printf("Error opening file: %s\n", strerror(errno));
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
            close(fd);
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
            pf_printf_fd(fd, "%s=%d\n", info->name, info->initiative);
            added = 1;
        }
        if (error != 1 && error != 0)
        {
            close(fd);
            cma_free_double(content);
            pf_printf("Error: data--initiative file is corrupted\n");
            return ;
        }
        pf_printf_fd(fd, "%s\n", content[i]);
        i++;
    }
    if (!content && !added)
    {
        pf_printf_fd(fd, "%s=%d\n", info->name, info->initiative);
        added = 1;
    }
    close(fd);
    cma_free_double(content);
    if (DEBUG == 1)
        pf_printf("added = %d\n", added);
    return ;
}
