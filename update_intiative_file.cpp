#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <fstream>

void ft_initiative_remove(t_char *info)
{
    char    *temp;
    char    **content;
    int     turn_marker;
    int     i;
    std::ofstream file;

    if (DEBUG == 1)
        std::cout << "removing initiative " << info->name << "\n";
    if (access("data/data--initiative", F_OK) == -1)
    {
        if (DEBUG == 1)
            std::cout << "File does not exist: data/data--initiative\n";
        return ;
    }
    content = ft_open_and_read("data/data--initiative");
    if (!content)
        return ;
    i = 0;
    file.open("data/data--initiative", std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << strerror(errno) << "\n";
        ft_free_double_char(content);
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
                std::cout << "found one " << content[i] << " and " << content[i][ft_strlen(info->name)] << "\n";
            i++;
            if (turn_marker)
                file << "--turn--";
            continue ;
        }
        file << content[i];
        turn_marker = 0;
        i++;
    }
    file.close();
    ft_free_double_char(content);
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
    std::ofstream file;

    if (DEBUG == 1)
        std::cout << "readding initiative " << info->name << " " << info->initiative << "\n";
    if (info->initiative <= 0)
        return ;
    content = ft_open_and_read("data/data--initiative");
    if (!content)
        return ;
    if (ft_initiative_check_content(info, content))
    {
        ft_free_double_char(content);
        std::cout << info->name << " is already in initiative\n";
        return ;
    }
    file.open("data/data--initiative", std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << strerror(errno) << "\n";
        ft_free_double_char(content);
        return ;
    }
    added = 0;
    i = 0;
    while (content[i])
    {
        n_line = ft_strchr(content[i], '\n');
        if (!n_line)
        {
            file.close();
            ft_free_double_char(content);
            std::cerr << "Error: data--initiative file is corrupted\n";
            return ;
        }
        *n_line = '\0';
        if (DEBUG == 1)
            std::cout << content[i] << "\n";
        error = ft_initiative_check(info, content, i);
        if (DEBUG == 1)
            std::cout << "Error = " << error << "\n";
        if (!added && error == 0)
        {
            file << info->name << "=" << info->initiative << "\n";
            added = 1;
        }
        if (error != 1 && error != 0)
        {
            file.close();
            ft_free_double_char(content);
            std::cerr << "Error: data--initiative file is corrupted\n";
            return ;
        }
        file << content[i] << "\n";
        i++;
    }
    if (!content && !added)
    {
        file << info->name << "=" << info->initiative << "\n";
        added = 1;
    }
    file.close();
    ft_free_double_char(content);
    if (DEBUG == 1)
        std::cout << "added = " << added << "\n";
    return ;
}
