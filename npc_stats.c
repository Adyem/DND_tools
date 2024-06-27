#include "dnd_tools.h"

int	ft_npc_open_file(t_char *info)
{
	int		error;
	int		fd;
	char	**content;
	
	fd = open(info->save_file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "1-Error opening file %s: %s\n",
			info->save_file, strerror(errno));
		return (1);
	}
	content = ft_read_file_dnd(fd);
	if (!content)
	{
		ft_printf_fd(2, "Malloc in read file failed");
		return (1);
	}
	close(fd);
	error = ft_initialize_info(info, content);
	if (DEBUG == 1)
		ft_printf("the value of error is %i\n", error);
	if (info->error || error)
		return (1);
	error = ft_npc_check_info(info);
	ft_free_double_char(content);
	if (error)
		error = 1;
	return (error);
}

void	ft_npc_change_stats(t_char *info, int index, char **input)
{
	int	error;
	int	i;

	i = 0;
	while (DEBUG == 1 && input[i])
	{
		ft_printf("%s\n", input[i]);
		i++;
	}
	if (index == 2)
	{
		if (ft_strcmp_dnd(input[1], "init") == 0)
		{
			ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
			ft_printf("Stats for %s written on a file\n", info->name);
			return ;
		}
	}
	error = ft_npc_open_file(info);
	if (error)
		return ;
	error = ft_npc_check_info(info);
	if (error)
		return ;
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
