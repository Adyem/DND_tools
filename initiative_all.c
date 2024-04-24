#include "dnd_tools.h"

static t_char	*ft_check_name(t_name *name, char *file_name)
{
	int		found;
	t_char	*info;
	t_name	*temp;

	if (DEBUG == 1)
		ft_printf("%s\n", file_name);
	info = NULL;
	found = 0;
	temp = name;
	while (temp != NULL && !found)
	{
		info = temp->function(0, NULL, 1);
		found = 1;
		if (ft_strcmp_dnd(info->save_file, file_name) == 0)
			break ;
		temp = temp->next;
	}
	if (DEBUG == 1)
		ft_printf("%p\n", info);
	return (info);
}

static t_char	*ft_read_all_files(int fd, t_name *name, char *file_name)
{
	t_char	*info;
	char	**content;

	if (DEBUG == 1)
		ft_printf("printing file_name: %s", file_name);
	info = ft_check_name(name, file_name);
	if (!info)
		return (NULL);
	content = ft_read_file_dnd(fd);
	if (!content)
	{
		free(info);
		return (NULL);
	}
	ft_initialize_info(info, content);
	ft_roll_initiative(info);
	return (info);
}

void	ft_open_all_files(t_name *name)
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
		snprintf(filepath, sizeof(filepath), "%s/%s", "data", entry->d_name);
		if (DEBUG == 1)
			ft_printf("%s\n", filepath);
		if (entry->d_type == DT_REG)
		{
			fd = open(filepath, O_RDONLY);
			if (fd == -1)
			{
				ft_printf_fd(2, "unable to open file: %s\n", strerror(errno));
				continue ;
			}
			info = ft_read_all_files(fd, name, filepath);
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
