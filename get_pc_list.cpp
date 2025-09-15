#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/File/open_dir.hpp"
#include <fcntl.h>
#include <unistd.h>

int ft_check_player_entry(const char *entry)
{
    char *filename = cma_strjoin("data/", entry);
    if (!filename)
        return 1;
    if (access(filename, R_OK | W_OK) == 0)
    {
        cma_free(filename);
        return 1;
    }
    cma_free(filename);
    return 0;
}

char **ft_get_pc_list()
{
    file_dir *dir = file_opendir("data");
    if (!dir)
        return (ft_nullptr);
    char **player_list = static_cast<char **>(cma_calloc(MAX_PLAYERS, sizeof(char *)));
    if (!player_list)
    {
        file_closedir(dir);
        return (ft_nullptr);
    }
    int player_count = 0;
    file_dirent *dir_entry;
    while ((dir_entry = file_readdir(dir)) != ft_nullptr && player_count < MAX_PLAYERS)
    {
        if (ft_strncmp("PC--", dir_entry->d_name, 4) == 0)
        {
            char *player_name = cma_strdup(dir_entry->d_name + 4);
            if (!player_name)
            {
                cma_free_double(player_list);
                file_closedir(dir);
                return (ft_nullptr);
            }
            player_list[player_count++] = player_name;
        }
    }
    file_closedir(dir);
    if (player_count == 0)
    {
        pf_printf_fd(2, "Error: No player character found\n");
        cma_free_double(player_list);
        return ft_nullptr;
    }
    int index = 0;
    while (DEBUG == 1 && player_list[index])
    {
        pf_printf("player %i on the list is %s\n", index, player_list[index]);
        index++;
    }
    return (player_list);
}
