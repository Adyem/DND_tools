#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/JSon/document.hpp"
#include "libft/File/open_dir.hpp"
#include "libft/Errno/errno.hpp"
#include "dnd_tools.hpp"

#ifndef DT_REG
# define DT_REG 8
#endif
#ifndef DT_UNKNOWN
# define DT_UNKNOWN 0
#endif

static t_char *ft_check_name(t_name *name, char *file_name)
{
    const char *input[2];
    t_char *info = ft_nullptr;

    if (DEBUG == 1)
        pf_printf("Printing file name again: %s\n", file_name);
    while (name != ft_nullptr)
    {
        if (ft_strcmp(name->name, file_name) == 0)
        {
            input[0] = name->name;
            input[1] = ft_nullptr;
            if (DEBUG == 1)
                pf_printf("Initializing: %s\n", name->name);
            info = name->function(1, input, name, 1);
            break ;
        }
        name = name->next;
    }
    return (info);
}

static t_char *ft_read_all_files(ft_file &file, t_name *name, char *file_name)
{
    t_char *info;

    if (DEBUG == 1)
        pf_printf("Printing file_name: %s\n", file_name);
    info = ft_check_name(name, file_name + 5);
    if (!info)
        return (ft_nullptr);
    if (DEBUG == 1)
        pf_printf("Initiative file descriptor is %d\n", file.get_fd());
    info->name = file_name + 5;
    ft_roll_initiative(info);
    return (info);
}

static void *ft_initiative_pc_error(const char *message)
{
    pf_printf_fd(2, "%s\n", message);
    return (ft_nullptr);
}

static int ft_initiative_parse_json_player(t_pc *player, const char *filepath, char *filename)
{
    json_document   document;
    json_group      *player_group;
    int             error;

    if (!player || !filepath)
        return (1);
    if (document.read_from_file(filepath) != 0)
        return (1);
    player_group = document.find_group(PLAYER_JSON_GROUP_NAME);
    if (!player_group)
    {
        if (filename)
            pf_printf_fd(2, "JSON player save missing group %s in %s\n", PLAYER_JSON_GROUP_NAME, filename);
        else
            pf_printf_fd(2, "JSON player save missing group %s\n", PLAYER_JSON_GROUP_NAME);
        return (1);
    }
    error = ft_check_stat_pc_json_object(player, &document, player_group, filename);
    if (error)
        return (1);
    return (0);
}

static t_pc *ft_read_pc_file(ft_file &file, char *filename, char *filepath)
{
    t_pc                *player;
    int                 error;

    player = static_cast<t_pc *>(cma_malloc(sizeof(t_pc)));
    if (!player)
        return (static_cast<t_pc *>(ft_initiative_pc_error("252 Error allocating memory")));
    ft_bzero(player, sizeof(t_pc));
    error = ft_initiative_parse_json_player(player, filepath, filename);
    if (error)
    {
        ft_free_pc(player);
        return (static_cast<t_pc *>(ft_initiative_pc_error("Failed to parse player JSON save")));
    }
    error = ft_request_initiative(player);
    if (error)
    {
        ft_free_pc(player);
        return (ft_nullptr);
    }
    file.open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file.get_error())
    {
        ft_free_pc(player);
        return (ft_nullptr);
    }
    ft_save_pc(player, file);
    return (player);
}

static void ft_initiative_write(int initiative, char *name)
{
    if (DEBUG == 1)
        pf_printf("Printing initiative to data file\n");
    ft_file file("data/data--initiative", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (file.get_error())
    {
        pf_printf_fd(2, "Error opening data--initiative: %s\n", file.get_error_str());
        return ;
    }
    if (DEBUG == 1)
        pf_printf("%s=%i\n", name, initiative);
    pf_printf_fd(file.get_fd(), "%s=%i\n", name, initiative);
}

void ft_open_all_files(t_name *name)
{
    int error = 0;
    t_char *info;
    t_pc *player = ft_nullptr;
    file_dir *dir = ft_nullptr;
    file_dirent *entry = ft_nullptr;
    char filepath[1024];
    ft_file info_save_file;

    info_save_file.open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (info_save_file.get_error())
        error = 1;
    dir = file_opendir("data");
    if (dir == ft_nullptr)
    {
        pf_printf_fd(2, "Unable to open directory: %s\n", ft_strerror(ft_errno));
        return ;
    }
    while ((entry = file_readdir(dir)) != ft_nullptr)
    {
        if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
            continue ;
        int format_result;

        format_result = pf_snprintf(filepath, sizeof(filepath), "%s/%s", "data", entry->d_name);
        if (format_result < 0)
        {
            pf_printf_fd(2, "Unable to prepare path for %s\n", entry->d_name);
            continue ;
        }
        if (DEBUG == 1)
            pf_printf("%s\n", filepath);
        if (ft_strncmp(entry->d_name, "data--", 6) == 0)
            continue ;
        int is_regular_file;
        int directory_check;

        is_regular_file = 0;
        if (entry->d_type == DT_REG)
            is_regular_file = 1;
        else if (entry->d_type == DT_UNKNOWN)
        {
            directory_check = file_dir_exists(filepath);
            if (directory_check < 0)
            {
                pf_printf_fd(2, "Unable to inspect '%s': %s\n", filepath,
                        ft_strerror(ft_errno));
            }
            else if (directory_check == 0)
                is_regular_file = 1;
        }
        if (is_regular_file == 0)
            continue ;
        ft_file file;
        file.open(filepath, O_RDONLY);
        if (file.get_error())
        {
            pf_printf_fd(2, "Unable to open file '%s': %s\n", filepath,
                    file.get_error_str());
            continue ;
        }
        if (ft_strncmp(entry->d_name, "PC--", 4) == 0)
        {
            player = ft_read_pc_file(file, entry->d_name, filepath);
            if (!player)
                continue ;
            ft_initiative_write(player->initiative, entry->d_name);
            ft_free_pc(player);
            continue ;
        }
        info = ft_read_all_files(file, name, filepath);
        if (!info)
            continue ;
        if (DEBUG == 1)
            pf_printf("2. Name of the save file is %s\n", filepath);
        ft_file write_file;
        write_file.open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (write_file.get_error())
        {
            pf_printf_fd(2, "Unable to open file '%s' for writing: %s\n",
                         filepath, write_file.get_error_str());
            ft_free_info(info);
            continue ;
        }
        ft_npc_write_file(info, &info->stats, &info->c_resistance, write_file);
        if (error == 0)
            ft_initiative_write(info->initiative, entry->d_name);

        ft_free_info(info);
    }
    file_closedir(dir);
    ft_file initiative_file;
    initiative_file.open("data/data--initiative", O_RDONLY);
    ft_initiative_sort(initiative_file);
    return ;
}
