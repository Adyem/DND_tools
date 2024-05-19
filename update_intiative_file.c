#include "dnd_tools.h"
#include <stdint.h>

void ft_initiative_remove(t_char *info)
{
	char	*temp;
	char	**content;
	int		turn_marker;
	int		i;
	int		fd;

	if (DEBUG == 1)
		ft_printf("removing initiative %s\n", info->name);
	content = ft_open_and_read("data/data--initiative");
	if (!content)
		return ;
	i = 0;
	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf_fd(2, "270-Error opening file: %s\n", strerror(errno));
		ft_free_content(content);
		return ;
	}
	i = 0;
	turn_marker = 0;
	while (content[i])
	{
		if (ft_strncmp(content[i], "--turn--", 8) == 0)
		{
			turn_marker = 1;
			temp = &content[i][8];
		}
		else
			temp = content[i];
		if (DEBUG == 1)
		{
			ft_printf("checking entry: %s\n", content[i]);
			ft_printf("comparing with: %s\n", info->name);
			ft_printf("ft_strncmp result: %d\n", ft_strncmp(info->name,
					content[i], ft_strlen(info->name)));
			ft_printf("content length: %i\n", ft_strlen(content[i]));
			ft_printf("name length: %i\n", ft_strlen(info->name));
			ft_printf("character after name: %c\n", content[i][ft_strlen(info->name)]);
			ft_printf("value to check: %s\n", &content[i][ft_strlen(info->name) + 1]);
		}
		if ((ft_strncmp(info->name, temp, ft_strlen(info->name)) == 0)
				&& (ft_strlen(temp) > ft_strlen(info->name))
				&& (temp[ft_strlen(info->name)] == '=')
				&& (ft_check_value(&temp[ft_strlen(info->name) + 1])))
		{
			if (DEBUG == 1)
				ft_printf("found one %s and %c\n", content[i],
					content[i][ft_strlen(info->name)]);
			i++;
			if (turn_marker)
				ft_printf_fd(fd, "--turn--");
			continue ;

		}
		ft_printf_fd(fd, "%s", content[i]);
		i++;
	}
	close(fd);
    ft_free_content(content);
	return ;
}

static int ft_initiative_check(t_char *info, char **content)
{
    int i;

    i = 0;
    while (content[i])
    {
        if (ft_strncmp(content[i], info->name, ft_strlen(info->name)))
            return (1);
        i++;
    }
    return (0);
}

void ft_initiative_add(t_char *info)
{
	char	**content;
	int		i;
	int		fd;
	int		added;

	if (DEBUG == 1)
		ft_printf("readding initiative %s\n", info->name);
	if (info->initiative <= 0)
		return ;
	content = ft_open_and_read("data/data--initiative");
	if (!content)
		return ;
	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf_fd(2, "270-Error opening file: %s\n", strerror(errno));
		ft_free_content(content);
		return ;
	}
    added = 0;
	i = 0;
	while (content[i])
	{
		if (DEBUG == 1)
			ft_printf("%s\n", content[i]);
		if (!added && (ft_initiative_check(info, content) == 0))
		{
			ft_printf_fd(fd, "%s=%d\n", info->name, info->initiative);
			added = 1;
		}
		ft_printf_fd(fd, "%s", content[i]);
		i++;
	}
	close(fd);
    ft_free_content(content);
	return ;
}
