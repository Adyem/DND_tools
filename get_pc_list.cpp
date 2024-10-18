#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

char **ft_get_pc_list(t_char *info)
{
    char	**content;
    int		fd;
    int		length;
    int		result;

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
    length = ft_double_char_length(content);
    result = -1;
    while (result == -1 || (ft_strncmp(content[result], "PC--", 4) != 0
                && ft_strncmp(content[result], "--turn--PC--", 12) != 0))
    {
        result = ft_dice_roll(1, length) - 1;
        if (DEBUG == 1)
            ft_printf("result = %d\n", result);
    }
	return 
}
