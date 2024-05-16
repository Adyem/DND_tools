#include "dnd_tools.h"

void ft_initiative_remove(t_char *info)
{
	char	**content;
	int		i;
	int		fd;

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
	while (content[i])
	{
		if ((ft_strncmp(info->name, content[i], ft_strlen(info->name)) == 0)
				&& (ft_strlen(content[i]) > ft_strlen(info->name))
				&& (content[i][ft_strlen(info->name) + 1] == '='))
		{
			i++;
			continue ;
		}
		ft_printf_fd(fd, "%s", content[i]);
		i++;
	}
	close(fd);
	ft_free_content(content);
	return ;
}

void ft_initiative_add(t_char *info)
{
	char	**content;
	int		i;
	int		fd;
	int		added;
	int		initiative;

	content = ft_open_and_read("data/data--initiative");
	if (!content)
		return ;
	i = 0;
	added = 0;
	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		if (!added && sscanf(content[i], "%*[^=]=%d", &initiative) == 1
				&& info->initiative > initiative)
		{
			ft_printf_fd(fd, "%s=%d\n", info->name, info->initiative);
			added = 1;
		}
		ft_printf_fd(2, "270-Error opening file: %s\n", strerror(errno));
		ft_free_content(content);
		return ;
	}
	i = 0;
	while (content[i])
	{
		ft_printf_fd(fd, "%s", content[i]);
		i++;
	}
	close(fd);
	ft_free_content(content);
	return ;
}
