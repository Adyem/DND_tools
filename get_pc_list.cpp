#include "dnd_tools.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/File/open_dir.hpp"

int ft_check_player_entry(const char *entry)
{
    if (entry && ft_strcmp(entry, "INVALID_PLAYER_ENTRY") == 0)
        return (1);
    char *filename = cma_strjoin("data/", entry);
    if (!filename)
        return 1;
    ft_file permission_check(filename, O_RDWR);
    if (!permission_check.get_error())
    {
        permission_check.close();
        cma_free(filename);
        return 1;
    }
    cma_free(filename);
    return 0;
}

ft_vector<ft_string>    ft_get_pc_list()
{
    ft_vector<ft_string>    player_list;
    file_dir                *dir;
    file_dirent             *dir_entry;

    dir = file_opendir("data");
    if (!dir)
        return (player_list);
    dir_entry = ft_nullptr;
    while ((dir_entry = file_readdir(dir)) != ft_nullptr
        && player_list.size() < static_cast<size_t>(MAX_PLAYERS))
    {
        if (ft_strncmp("PC--", dir_entry->d_name, 4) == 0)
        {
            ft_string player_name(dir_entry->d_name + 4);
            if (player_name.get_error() != ER_SUCCESS)
            {
                file_closedir(dir);
                player_list.clear();
                return (player_list);
            }
            player_list.push_back(player_name);
            if (player_list.get_error() != ER_SUCCESS)
            {
                file_closedir(dir);
                player_list.clear();
                return (player_list);
            }
        }
    }
    file_closedir(dir);
    if (player_list.size() == 0)
    {
        pf_printf_fd(2, "Error: No player character found\n");
        return (player_list);
    }
    if (DEBUG == 1)
    {
        size_t index = 0;
        while (index < player_list.size())
        {
            pf_printf("player %i on the list is %s\n", static_cast<int>(index),
                    player_list[index].c_str());
            index++;
        }
    }
    return (player_list);
}
