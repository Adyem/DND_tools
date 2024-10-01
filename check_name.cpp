#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <dirent.h>
#include <iostream>

static void remove_exclude_prefix(char* filename)
{
    if (ft_strncmp(filename, EXCLUDE_PREFIX, ft_strlen(EXCLUDE_PREFIX)) == 0)
        ft_memmove(filename, filename + ft_strlen(EXCLUDE_PREFIX), ft_strlen(filename)
                - ft_strlen(EXCLUDE_PREFIX) + 1);
}

int ft_set_stats_check_name(const char *name)
{
    DIR *dir;
    struct dirent *entry;
    char filename[256];

    if (!name)
    {
        std::cerr << "259-Error: Name does not exist" << std::endl;
        return (-1) ;
    }
    dir = opendir(DATA_FOLDER);
    if (dir == nullptr)
    {
        std::cerr << "295-Error: Opendir has failed: " << strerror(errno) << std::endl;
        return (-2) ;
    }
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (ft_strncmp(entry->d_name, PREFIX_TO_SKIP, ft_strlen(PREFIX_TO_SKIP)) == 0)
            continue ;
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        remove_exclude_prefix(filename);
        if (DEBUG == 1)
            std::cout << "Checking " << filename << " " << name << std::endl;
        if (ft_strcmp_dnd(filename, name) == 0)
        {
            closedir(dir);
            if (DEBUG == 1)
                std::cout << "Found " << name << std::endl;
            return (0) ;
        }
    }
    closedir(dir);
    std::cerr << "258-Error: Target does not exist" << std::endl;
    return (1) ;
}

int ft_check_player_character(const char *name)
{
    DIR *dir;
    struct dirent *entry;
    char filename[256];

    dir = opendir(DATA_FOLDER);
    if (dir == nullptr)
    {
        std::cerr << "307-Error: Opendir has failed: " << strerror(errno) << std::endl;
        return (-2) ;
    }
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (ft_strncmp(entry->d_name, PC_PREFIX, ft_strlen(PC_PREFIX)) != 0)
            continue ;
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        if (DEBUG == 1)
            std::cout << "Checking " << filename << " against " << name << std::endl;
        if (ft_strcmp_dnd(filename, name) == 0)
        {
            closedir(dir);
            if (DEBUG == 1)
                std::cout << "Found " << name << std::endl;
            return (0) ;
        }
    }
    closedir(dir);
    return (1) ;
}
