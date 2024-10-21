#include "../Libft/libft.hpp"
#include "../CMA/CMA.hpp"
#include <cstdio>
#include "get_next_line.hpp"

static char	*leftovers(char *readed_string, bool critical)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	while (readed_string[i] && readed_string[i] != '\n')
		i++;
	if (!readed_string[i])
	{
		cma_free(readed_string);
		return (nullptr);
	}
	string = (char *)cma_malloc(ft_strlen(readed_string) - i + 1, critical);
	if (!string)
		return (nullptr);
	i++;
	j = 0;
	while (readed_string[i])
		string[j++] = readed_string[i++];
	string[j] = '\0';
	cma_free(readed_string);
	return (string);
}

static char	*malloc_gnl(char *readed_string, size_t i, bool critical)
{
	char	*string;

	if (readed_string && readed_string[i] == '\n')
		string = (char *)cma_malloc(i + 2, critical);
	else
		string = (char *)cma_malloc(i + 1, critical);
	if (!string)
		return (nullptr);
	return (string);
}

static char	*fetch_line(char *readed_string, bool critical)
{
	size_t	i;
	char	*string;

	i = 0;
	if (!readed_string[i])
		return (nullptr);
	while (readed_string[i] && readed_string[i] != '\n')
		i++;
	string = malloc_gnl(readed_string, i, critical);
	if (!string)
		return (nullptr);
	i = 0;
	while (readed_string[i] && readed_string[i] != '\n')
	{
		string[i] = readed_string[i];
		i++;
	}
	if (readed_string[i] == '\n')
	{
		string[i] = '\n';
		i++;
	}
	string[i] = '\0';
	return (string);
}

static char	*read_fd(int fd, char *readed_string, bool critical)
{
	char	buffer[BUFFER_SIZE + 1];
	int		readed_bytes;

	readed_bytes = 1;
	while (!ft_strchr(readed_string, '\n') && readed_bytes != 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes == -1)
		{
			cma_free(buffer);
			cma_free(readed_string);
			return (nullptr);
		}
		buffer[readed_bytes] = '\0';
		readed_string = ft_strjoin_gnl(readed_string, buffer, critical);
	}
	return (readed_string);
}

char	*get_next_line(int fd, bool critical)
{
	char		*string;
	static char	*readed_string[4096];
	int			i;

	i = 0;
	while (fd == -1 && i < 4096)
	{
		cma_free(readed_string[i]);
		readed_string[i] = nullptr;
		i++;
	}
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (nullptr);
	readed_string[fd] = read_fd(fd, readed_string[fd], critical);
	if (!readed_string[fd])
		return (nullptr);
	string = fetch_line(readed_string[fd], critical);
	readed_string[fd] = leftovers(readed_string[fd], critical);
	return (string);
}
