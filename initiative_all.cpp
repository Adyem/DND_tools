#include "libft/libft/libft.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <dirent.h>
#include <iostream>

static t_char *ft_check_name(t_name *name, char *file_name)
{
    const char *input[2];
    t_char *info;

    if (DEBUG == 1)
        std::cout << "Printing file name again: " << file_name << std::endl;
    info = nullptr;
    while (name != nullptr)
    {
        if (ft_strcmp_dnd(name->name, file_name) == 0)
        {
            input[0] = name->name;
            input[1] = nullptr;
            if (DEBUG == 1)
                std::cout << "Initializing: " << name->name << std::endl;
            info = name->function(1, input, name, 1);
            break ;
        }
        name = name->next;
    }
    if (DEBUG == 1)
        std::cout << "Memory location of info: " << info << std::endl;
    return (info);
}

static t_char *ft_read_all_files(int fd, t_name *name, char *file_name)
{
    t_char *info;

    if (DEBUG == 1)
        std::cout << "Printing file_name: " << file_name << std::endl;
    info = ft_check_name(name, file_name + 5);
    if (!info)
    {
        std::cerr << "255 Error allocating memory" << std::endl;
        return (nullptr);
    }
    if (DEBUG == 1)
        std::cout << "Initiative file descriptor is " << fd << std::endl;
    info->name = file_name + 5;
    ft_roll_initiative(info);
    return (info);
}

static void *ft_initiative_pc_error(const char *message)
{
    std::cerr << message << std::endl;
    return (nullptr);
}

static t_pc *ft_read_pc_file(int fd, char *filename, char *filepath)
{
    char **content;
    t_pc *player;
    int error;

    content = ft_read_file_dnd(fd);
    close(fd);
    if (!content)
        return (t_pc *)ft_initiative_pc_error("253 Error allocating memory");
    player = (t_pc *)malloc(sizeof(t_pc));
    if (!player)
    {
        free(content);
        return (t_pc *)ft_initiative_pc_error("252 Error allocating memory");
    }
    error = ft_check_stat_pc(player, content, filename);
    ft_free_double_char(content);
    if (error)
    {
        ft_free_pc(player);
        return (nullptr);
    }
    error = ft_request_initiative(player);
    if (!error)
    {
        fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd != -1)
            ft_save_pc(player, fd);
    }
    close(fd);
    return (player);
}

void ft_initiative_write(int initiative, char *name)
{
    int fd;

    if (DEBUG == 1)
        std::cout << "Printing initiative to data file" << std::endl;
    fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        std::cerr << "Error opening data--initiative: " << strerror(errno) << std::endl;
        return ;
    }
    if (DEBUG == 1)
        std::cout << name << "=" << initiative << std::endl;
    dprintf(fd, "%s=%i\n", name, initiative);
    close(fd);
}

void ft_open_all_files(t_name *name)
{
    int error;
    t_char *info;
    t_pc *player;
    DIR *dir;
    struct dirent *entry;
    char filepath[1024];
    int fd;

    fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    error = 0;
    if (fd == -1)
        error = 1;
    else
        close(fd);
    dir = opendir("data");
    if (dir == nullptr)
    {
        std::cerr << "Unable to open directory: " << strerror(errno) << std::endl;
        return ;
    }
    while ((entry = readdir(dir)) != nullptr)
    {
        if (ft_strcmp_dnd(entry->d_name, ".") == 0 || ft_strcmp_dnd(entry->d_name, "..") == 0)
            continue ;
        snprintf(filepath, sizeof(filepath), "%s/%s", "data", entry->d_name);
        if (DEBUG == 1)
            std::cout << filepath << std::endl;
        if (ft_strncmp(entry->d_name, "data--", 6) == 0)
            continue ;
        if (entry->d_type == DT_REG)
        {
            fd = open(filepath, O_RDONLY);
            if (fd == -1)
            {
                std::cerr << "Unable to open file: " << strerror(errno) << std::endl;
                continue ;
            }
            if (ft_strncmp(entry->d_name, "PC--", 4) == 0)
            {
                player = ft_read_pc_file(fd, entry->d_name, filepath);
                if (!player)
                    continue ;
                ft_initiative_write(player->initiative, entry->d_name);
                ft_free_pc(player);
                continue ;
            }
            info = ft_read_all_files(fd, name, filepath);
            close(fd);
            if (!info)
                continue ;
            if (DEBUG == 1)
                std::cout << "2. Name of the save file is " << filepath << std::endl;
            fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (fd == -1)
            {
                std::cerr << "Unable to open file: " << strerror(errno) << std::endl;
                ft_free_info(info);
                continue ;
            }
            ft_npc_write_file(info, &info->stats, &info->c_resistance, fd);
			close(fd);

            if (error == 0)
                ft_initiative_write(info->initiative, entry->d_name);
            ft_free_info(info);
        }
    }
    closedir(dir);
    ft_initiative_sort(open("data/data--initiative", O_RDONLY));
	return ;
}
