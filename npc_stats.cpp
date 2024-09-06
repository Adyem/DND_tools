#include "dnd_tools.hpp"
#include <cerrno>
#include "libft/printf/ft_printf.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	ft_npc_open_file(t_char *info)
{
	int		error;
	int		fd;
	char	**content;

	fd = open(info->save_file, O_RDONLY);
	if (DEBUG == 1)
		ft_printf("opening file %s on fd %i\n", info->save_file, fd);
	if (fd == -1)
	{
		ft_printf_fd(2, "1-Error opening file %s: %s\n",
			info->save_file, strerror(errno));
		return (1);
	}
	content = ft_read_file_dnd(fd);
	if (DEBUG == 1)
		ft_printf("content is at adress %p\n", content);
	if (!content)
		return (1);
	close(fd);
	error = ft_initialize_info(info, content);
	if (DEBUG == 1)
		ft_printf("the value of error is %i %i\n", error, info->flags.error);
	if (info->flags.error || error)
		return (1);
	error = ft_npc_check_info(info);
	ft_free_double_char(content);
	if (error)
		error = 1;
	return (error);
}

void	ft_npc_change_stats(t_char *info, const int index, const char **input)
{
	int	i;

	i = 0;
	while (DEBUG == 1 && input[i])
	{
		ft_printf("%s\n", input[i]);
		i++;
	}
	i = 0;
	if (DEBUG == 1)
	{
		while (input[i])
		{
			ft_printf("%s\n", input[i]);
			i++;
		}
	}
	if (index == 1)
	{
		if (info->turn)
			info->turn(info);
		else
			ft_printf("%s doesn't take anny actions on his/her turn\n", info->name);
	}
	else if (index == 2)
		ft_npc_sstuff(info, input);
	else if (index == 3)
		ft_npc_set_stat(info, input);
	else if	(index == 4)
		ft_change_stats_04(info, input);
	else
		ft_printf_fd(2, "Error: too manny arguments given\n");
	ft_npc_write_file(info, &info->stats, &info->c_resistance, -1);
	return ;
}
