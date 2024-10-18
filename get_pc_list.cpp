#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

char **ft_get_pc_list()
{
    char		**content;
	char		**result;
    int			fd;
    int			i;
	int			j;

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
	result = (char **)cma_calloc(6, sizeof(char *), false);
	i = 0;
	j = 0;
    while (content[i])
    {
		if (ft_strncmp("pc--", content[i], 4))
		{
			result[j] = cma_strdup(&content[i][4], false);
			j++;
		}
		if (ft_strncmp("--turn--pc--", &content[i][12], 12))
		{
			result[j] = cma_strdup(&content[i][12], false);
			j++;
		}
		if (DEBUG == 1)
			ft_printf("found player %s\n", result[j - 1]);
		if (j == MAX_PLAYERS)
			break ;
		i++;
    }
	if (j == 0)
	{
		ft_printf_fd(2, "282-Error no player characcter found\n");
		cma_free(result);
		return (nullptr);
	}
	return (result);
}
