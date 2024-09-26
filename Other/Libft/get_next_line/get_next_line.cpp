/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:27:29 by bvangene          #+#    #+#             */
/*   Updated: 2023/12/09 15:14:21 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.hpp"
#include "get_next_line.hpp"

char	*leftovers(char *readed_string)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	while (readed_string[i] && readed_string[i] != '\n')
		i++;
	if (!readed_string[i])
	{
		free(readed_string);
		return (nullptr);
	}
	string = (char *)malloc(ft_strlen(readed_string) - i + 1);
	if (!string)
		return (nullptr);
	i++;
	j = 0;
	while (readed_string[i])
		string[j++] = readed_string[i++];
	string[j] = '\0';
	free(readed_string);
	return (string);
}

char	*malloc_gnl(char *readed_string, size_t i)
{
	char	*string;

	if (readed_string && readed_string[i] == '\n')
		string = (char *)malloc(i + 2);
	else
		string = (char *)malloc(i + 1);
	if (!string)
		return (nullptr);
	return (string);
}

char	*fetch_line(char *readed_string)
{
	size_t	i;
	char	*string;

	i = 0;
	if (!readed_string[i])
		return (nullptr);
	while (readed_string[i] && readed_string[i] != '\n')
		i++;
	string = malloc_gnl(readed_string, i);
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

char	*read_fd(int fd, char *readed_string)
{
	char	*buffer;
	int		readed_bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (nullptr);
	readed_bytes = 1;
	while (!ft_strchr(readed_string, '\n') && readed_bytes != 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes == -1)
		{
			free(buffer);
			free(readed_string);
			return (nullptr);
		}
		buffer[readed_bytes] = '\0';
		readed_string = ft_strjoin_gnl(readed_string, buffer);
	}
	free(buffer);
	return (readed_string);
}

char	*get_next_line(int fd)
{
	char		*string;
	static char	*readed_string[4096];
	int			i;

	i = 0;
	while (fd == -1 && i < 4096)
	{
		free(readed_string[i]);
		readed_string[i] = nullptr;
		i++;
	}
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (nullptr);
	readed_string[fd] = read_fd(fd, readed_string[fd]);
	if (!readed_string[fd])
		return (nullptr);
	string = fetch_line(readed_string[fd]);
	readed_string[fd] = leftovers(readed_string[fd]);
	return (string);
}
