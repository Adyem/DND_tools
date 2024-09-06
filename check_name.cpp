#include "dnd_tools.hpp"
#include "libft/libft/libft.hpp"
#include "libft/printf/ft_printf.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <dirent.h>

static void remove_exclude_prefix(char* filename)
{
    if (ft_strncmp(filename, EXCLUDE_PREFIX, ft_strlen(EXCLUDE_PREFIX)) == 0)
        ft_memmove(filename, filename + ft_strlen(EXCLUDE_PREFIX), ft_strlen(filename)
				- ft_strlen(EXCLUDE_PREFIX) + 1);
}

int ft_set_stats_check_name(const char *name)
{
    DIR				*dir;
    struct dirent	*entry;
	char			filename[256];

	if (!name)
	{
		ft_printf_fd(2, "259-Error name does not exist\n");
		return (-1);
	}
	dir = opendir(DATA_FOLDER);
    if (dir == NULL)
	{
		ft_printf_fd(2, "295-Error Opendir has failed: %s", strerror(errno));
        return (-2);
    }
    while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
        if (ft_strncmp(entry->d_name, PREFIX_TO_SKIP, strlen(PREFIX_TO_SKIP)) == 0)
            continue ;
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        remove_exclude_prefix(filename);
		if (DEBUG == 1)
			ft_printf("Checking %s %s\n", filename, name);
        if (ft_strcmp_dnd(filename, name) == 0)
		{
            closedir(dir);
			if (DEBUG == 1)
				ft_printf("found %s\n", name);
            return (0);
		}
    }
    closedir(dir);
	ft_printf_fd(2, "258-Error target does not exist\n");
    return (1);
}

int ft_check_player_character(const char *name)
{
    DIR* dir;
    struct dirent* entry;
    char filename[256];

	dir = opendir(DATA_FOLDER);
    if (dir == NULL)
    {
        ft_printf_fd(2, "307-Error: Opendir has failed: %s\n", strerror(errno));
        return (-2);
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
            ft_printf("Checking %s against %s\n", filename, name);
        if (ft_strcmp_dnd(filename, name) == 0)
        {
            closedir(dir);
            if (DEBUG == 1)
                ft_printf("Found %s\n", name);
            return (0);
        }
    }
    closedir(dir);
    return (1);
}
