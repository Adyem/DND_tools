#include "dnd_tools.h"

t_char	*ft_read_all_files(int fd)
{
	t_char	*info;
	char	**content;

	content = ft_read_file_dnd(fd);
	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return (NULL);
	ft_initialize_info(info, content);
	ft_roll_initiative(info);
	return (info);
}

void	ft_open_all_files(void)
{
	t_char			*info;
	DIR				*dir;
	struct dirent	*entry;
	char			filepath[1024];
	int				fd;

	dir = opendir("data");
	if (dir == NULL)
	{
		perror("unable to open directory");
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strcmp_dnd(entry->d_name, ".") == 0 || ft_strcmp_dnd(entry->d_name, "..") == 0)
			continue ;
		snprintf(filepath, sizeof(filepath), "%s/%s", "data/%s", entry->d_name);
		if (entry->d_type == DT_REG)
		{
			fd = open(filepath, O_RDONLY);
			if (fd == -1)
			{
				ft_printf_fd(2, "unable to open file: %s\n", strerror(errno));
				continue ;
			}
			info = ft_read_all_files(fd);
			if (!info)
				continue ;
			close(fd);
			fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
			if (fd == -1)
			{
				ft_printf_fd(2, "unable to open file: %s\n", strerror(errno));
				free(info);
				continue ;
			}
			ft_npc_write_file(info, &info->stats, &info->c_resistance, fd);
			close(fd);
		}
	}
	closedir(dir);
	return ;
}
