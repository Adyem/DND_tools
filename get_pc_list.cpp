#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"
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
	int		fd;
	char	**content;

    fd = open("data/data--initiative", O_RDONLY);
    if (fd == -1)
    {
        ft_printf("280-Error opening file: %s\n", strerror(errno));
        return (nullptr);
    }
    content = ft_read_file_dnd(fd);
    close(fd);
    if (!content)
    {
        ft_printf("281-Error opening file: %s\n", strerror(errno));
        return (nullptr);
    }
	return (content);
}

bool ft_handle_player_entry(char **result, char *content, const char *prefix, int *j)
{
    if (ft_strncmp(prefix, content, strlen(prefix)) == 0)
    {
        result[*j] = cma_strdup(content + strlen(prefix), false);
        if (!result[*j])
        {
            cma_free_double(result);
            return false;
        }
        char *equal_sign = ft_strchr(result[*j], '=');
        if (equal_sign)
            *equal_sign = '\0';
        if (DEBUG == 1)
            ft_printf("found player %s\n", result[*j]);
        if (ft_check_player_entry(result[*j]))
        {
            cma_free_double(result);
            return false;
        }
        (*j)++;
    }
    return true;
}

char **ft_get_pc_list()
{
    char    **content;
    char    **result;
    int     i;
    int     j;

    content = ft_open_and_read_initiative();
    if (!content)
        return (nullptr);

    result = (char **)cma_calloc(MAX_PLAYERS, sizeof(char *), false);
    if (!result)
        return (nullptr);
    i = 0;
    j = 0;
    while (content[i] && j < MAX_PLAYERS)
    {
        if (!ft_handle_player_entry(result, content[i], "PC--", &j) ||
	            !ft_handle_player_entry(result, content[i], "--turn--PC--", &j))
		{
			cma_free_double(result);
			cma_free_double(content);
            return (nullptr);
		}
        i++;
    }
    if (j == 0)
    {
        ft_printf_fd(2, "282-Error: No player character found\n");
        cma_free_double(result);
		cma_free_double(content);
        return (nullptr);
    }
	cma_free_double(content);
    return (result);
}
