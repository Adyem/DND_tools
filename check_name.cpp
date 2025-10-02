#include "dnd_tools.hpp"
#include "libft/File/open_dir.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <dirent.h>
#include <cctype>

static int has_prefix_case_insensitive(const char *value, const char *prefix)
{
    size_t  index;

    if (!value || !prefix)
        return (0);
    index = 0;
    while (prefix[index] != '\0')
    {
        if (value[index] == '\0')
            return (0);
        if (std::tolower(static_cast<unsigned char>(value[index]))
            != std::tolower(static_cast<unsigned char>(prefix[index])))
            return (0);
        index++;
    }
    return (1);
}

static void remove_exclude_prefix(char* filename)
{
    size_t  prefix_length;
    size_t  filename_length;

    prefix_length = ft_strlen(EXCLUDE_PREFIX);
    if (has_prefix_case_insensitive(filename, EXCLUDE_PREFIX) == 0)
        return ;
    filename_length = ft_strlen(filename);
    ft_memmove(filename, filename + prefix_length,
        filename_length - prefix_length + 1);
    return ;
}

int ft_set_stats_check_name(const char *name)
{
    file_dir *dir;
    file_dirent *entry;
    char filename[256];

    if (!name)
    {
        pf_printf_fd(2, "259-Error: Name does not exist\n");
        return (-1);
    }
    dir = file_opendir(DATA_FOLDER);
    if (dir == ft_nullptr)
    {
        pf_printf_fd(2, "295-Error: Opendir has failed: %s\n", strerror(errno));
        return (-2);
    }
    while (1)
    {
        entry = file_readdir(dir);
        if (!entry)
            break ;
        if (has_prefix_case_insensitive(entry->d_name, PREFIX_TO_SKIP) == 1)
            continue ;
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        if (ft_strcmp(filename, name) == 0)
        {
            file_closedir(dir);
            if (DEBUG == 1)
                pf_printf("Found %s\n", name);
            return (0);
        }
        remove_exclude_prefix(filename);
        if (DEBUG == 1)
            pf_printf("Checking %s %s\n", filename, name);
        if (ft_strcmp(filename, name) == 0)
        {
            file_closedir(dir);
            if (DEBUG == 1)
                pf_printf("Found %s\n", name);
            return (0);
        }
    }
    file_closedir(dir);
    pf_printf_fd(2, "258-Error: Target does not exist\n");
    return (1);
}

int ft_check_player_character(const char *name)
{
    file_dir *dir;
    file_dirent *entry;
    char filename[256];

    dir = file_opendir(DATA_FOLDER);
    if (dir == ft_nullptr)
    {
        pf_printf_fd(2, "307-Error: Opendir has failed: %s\n", strerror(errno));
        return (-2);
    }
    while (1)
    {
        entry = file_readdir(dir);
        if (!entry)
            break ;
        if (has_prefix_case_insensitive(entry->d_name, PC_PREFIX) == 0)
            continue ;
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        if (DEBUG == 1)
            pf_printf("Checking %s against %s\n", filename, name);
        if (ft_strcmp(filename, name) == 0)
        {
            file_closedir(dir);
            if (DEBUG == 1)
                pf_printf("Found %s\n", name);
            return (0);
        }
        remove_exclude_prefix(filename);
        if (ft_strcmp(filename, name) == 0)
        {
            file_closedir(dir);
            if (DEBUG == 1)
                pf_printf("Found %s\n", name);
            return (0);
        }
    }
    file_closedir(dir);
    return (1);
}
