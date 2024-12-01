#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int	ft_check_player_entry(const char *entry)
{
	char	*filename;

	filename = cma_strjoin("data/pc--", entry, false);
	if (!filename)
		return (1);
	if (access(filename, R_OK | W_OK) == 0)
	{
		cma_free(filename);
		return (1);
	}
	cma_free(filename);
	return (0);
}

static char	**ft_open_and_read_initiative()
{
	ft_file	initiative_file;
	char	**content;

    initiative_file = open("data/data--initiative", O_RDONLY);
    if (initiative_file.get_error_code())
    {
        pf_printf("280-Error opening file: %s\n", initiative_file.get_error_message());
        return (ft_nullptr);
    }
    content = ft_read_file_dnd(initiative_file);
    if (!content)
    {
        pf_printf("281-Error opening file: %s\n", strerror(errno));
        return (ft_nullptr);
    }
	return (content);
}

static bool ft_process_player_entry(char **player_list, char *line, const char *entry_prefix,
									int *player_count)
{
    if (ft_strncmp(entry_prefix, line, strlen(entry_prefix)) == 0)
    {
        player_list[*player_count] = cma_strdup(line + strlen(entry_prefix), false);
        if (!player_list[*player_count])
        {
            cma_free_double(player_list);
            return false;
        }
        char *delimiter = ft_strchr(player_list[*player_count], '=');
        if (delimiter)
            *delimiter = '\0';
        if (DEBUG == 1)
            pf_printf("found player %s\n", player_list[*player_count]);
        if (ft_check_player_entry(player_list[*player_count]))
        {
            cma_free_double(player_list);
            return false;
        }
        (*player_count)++;
    }
    return true;
}

char **ft_get_pc_list()
{
    char **lines;
    char **player_list;
    int line_index;
    int player_count;

    lines = ft_open_and_read_initiative();
    if (!lines)
        return (ft_nullptr);
    player_list = (char **)cma_calloc(MAX_PLAYERS, sizeof(char *), false);
    if (!player_list)
        return (ft_nullptr);
    line_index = 0;
    player_count = 0;
    while (lines[line_index] && player_count < MAX_PLAYERS)
    {
        if (!ft_process_player_entry(player_list, lines[line_index], "PC--", &player_count) ||
            !ft_process_player_entry(player_list, lines[line_index], "--turn--PC--", &player_count))
        {
            cma_free_double(player_list);
            cma_free_double(lines);
            return (ft_nullptr);
        }
        line_index++;
    }
    if (player_count == 0)
    {
        pf_printf_fd(2, "282-Error: No player character found\n");
        cma_free_double(player_list);
        cma_free_double(lines);
        return (ft_nullptr);
    }
    cma_free_double(lines);
    return (player_list);
}
