#include "dnd_tools.h"

static void	ft_malloc_fail_gnl_dnd(char **return_v, int fd)
{
	int	i;

	close(fd);
	i = 0;
	if (return_v)
	{
		while (return_v[i])
		{
			free(return_v[i]);
			i++;
		}
		free(return_v);
	}
	return ;
}

static char	**ft_realloc_dnd(char **return_v, int index, int fd)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_calloc(index + 1, sizeof(char *));
	if (!temp)
	{
		ft_printf_fd(2, "165-Error: Malloc in read file failed\n");
		ft_malloc_fail_gnl_dnd(return_v, fd);
		return (NULL);
	}
	if (return_v)
	{
		while (return_v[i])
		{
			temp[i] = return_v[i];
			i++;
		}
	}
	free(return_v);
	return (temp);
}

char	**ft_read_file_dnd(int fd)
{
	char	**return_v;
	char	*line;
	int		i;

	return_v = NULL;
	line = NULL;
	i = 0;
	while (1)
	{
		ft_printf("HELLO %i\n", fd);
		line = get_next_line(fd);
		ft_printf("%p %s\n", line, strerror(errno));
		if (!line)
			break ;
		i++;
		return_v = ft_realloc_dnd(return_v, i, fd);
		if (!return_v)
			return (NULL);
		return_v[i - 1] = line;
	}
	return (return_v);
}

char		**ft_open_and_read(char *file)
{
	int		fd;
	char	**content;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("166-Error opening file :%s\n", strerror(errno));
		return (NULL);
	}
	content = ft_read_file_dnd(fd);
	close(fd);
	return (content);
}
