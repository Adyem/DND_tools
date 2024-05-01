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
		ft_printf("printing file_name: %s\n", file_name);
	info = ft_check_name(name, file_name);
	if (!info)
	{
		ft_printf_fd(2, "255 Error allocating memory\n");
		return (NULL);
	}
	if (DEBUG == 1)
		ft_printf("Iniaitive file descriptor is %i\n", fd);
	content = ft_read_file_dnd(fd);
	if (!content)
	{
		free(info);
		return (NULL);
	}
	info->save_file = ft_strdup(file_name);
	if (!info->save_file)
	{
		ft_printf_fd(2, "254 Error allocating memory\n");
		return (NULL);
	}
	if (DEBUG == 1)
		ft_printf("name of the safe file is %s\n", file_name);
	ft_initialize_info(info, content);
	info->name = file_name + 5;
	info->name[ft_strlen(info->name) - 4] = '\0';
	ft_roll_initiative(info);
	info->name[ft_strlen(info->name)] = '.';
	info->name = file_name - 5;
	free(info->save_file);
	ft_free_content(content);
	return (info);
}

static void	*ft_initiative_pc_error(char *message)
{
	ft_printf_fd(2, "%s", message);
	return (NULL);
}

static t_pc	*ft_read_pc_file(int fd, char *filename)
{
	char	**content;
	t_pc	*player;
	int		error;

	content = ft_read_file_dnd(fd);
	if (!content)
		return (ft_initiative_pc_error("251 Error allocating memory"));
	player = malloc(sizeof(t_pc));
	if (!player)
	{
		free(content);
		return (ft_initiative_pc_error("252 Error allocating memory"));
	}
	player->name = NULL;
	player->initiative = -2;
	error = ft_check_stat_pc(player, content, filename);
	if (error)
	{
		ft_free_pc(player);
		ft_free_content(content);
		return (NULL);
	}
	ft_free_content(content);
	error = ft_request_initiative(player);
	if (!error)
	{
	}
	return (player);
}

void	ft_initiative_write(int	initiative, char *name)
{
	int	fd;

	if (DEBUG == 1)
		ft_printf("printing initiative to data file\n");
	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf_fd(2, "error opening data--initiative: %s\n", strerror(errno));
		return ;
	}
	ft_printf_fd(fd, "%s %i\n", name, initiative);
	return ;
}

void	ft_open_all_files(t_name *name)
{
	int				error;
	t_char			*info;
	t_pc			*player;
	DIR				*dir;
	struct dirent	*entry;
	char			filepath[1024];
	int				fd;

	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	error = 0;
	if (fd == -1)
		error = 1;
	else
		close(fd);
	dir = opendir("data");
	if (dir == NULL)
	{
		ft_printf_fd(2, "Unable to open directory: ", strerror(errno));
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strcmp_dnd(entry->d_name, ".") == 0
				|| ft_strcmp_dnd(entry->d_name, "..") == 0)
			continue ;
		snprintf(filepath, sizeof(filepath), "%s/%s", "data", entry->d_name);
		if (DEBUG == 1)
			ft_printf("%s\n", filepath);
		if (ft_strncmp(entry->d_name, "data--", 6) == 0)
			continue ;
		if (entry->d_type == DT_REG)
		{
			fd = open(filepath, O_RDONLY);
			if (ft_strncmp(entry->d_name, "PC--", 6) == 0)
			{
				player = ft_read_pc_file(fd, entry->d_name);
				close(fd);
				if (!player)
					continue ;
				ft_initiative_write(player->initiative, entry->d_name);
				continue ;
			}
			if (fd == -1)
			{
				ft_printf_fd(2, "unable to open file: %s\n", strerror(errno));
				continue ;
			}
			info = ft_read_all_files(fd, name, filepath);
			if (!info)
				continue ;
			close(fd);
			if (DEBUG == 1)
				ft_printf("2 name of the save file is %s\n", filepath);
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
			if (error == 0)
				ft_initiative_write(info->initiative, entry->d_name);
			free(info);
		}
	}
	closedir(dir);
	return ;
}
