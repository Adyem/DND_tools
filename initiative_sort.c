#include "dnd_tools.h"

void	ft_initiative_sort(int fd)
{
	char	**content;
	int		i;

	if (fd == -1)
	{
		ft_printf_fd(2, "Error opening file: %s\n", strerror(errno));
		return ;
	}
	content = ft_read_file_dnd(fd);
	if (!content)
		return (NULL);
}
