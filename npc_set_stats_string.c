#include "dnd_tools.h"

char **ft_set_stats_con_targets(char *content, int ofset, char **data, t_char *info)
{
	char	**temp;
	int		i;

	if (ft_set_stats_check_name(&content[ofset]))
			return (ft_printf_fd(2, "292-Error Target does not exist\n"), NULL);
	if (!data)
	{
		data = (char **)malloc(sizeof(char *) * 2);
		if (!data)
		{
			info->error = 1;
			return (ft_printf_fd(2, "293-Error allocating memory\n"), NULL);
		}
		data[0] = ft_strdup(&content[ofset]);
		if (!data[0])
		{
			info->error = 1;
			ft_free_double_char(data);
			return (ft_printf_fd(2, "294-Error allocating memory\n"), NULL);
		}
		data[1] = NULL;
	}
	else if (data)
	{
		i = 0;
		while (data[i])
			i++;
		temp = (char **)malloc((i + 2) * sizeof(char *));
		if (!temp)
		{
			info->error = 1;
			ft_free_double_char(data);
			return (ft_printf_fd(2, "295-Error allocating memory\n"), NULL);
		}
		i = 0;
		while (data[i])
		{
			temp[i] = data[i];
			i++;
		}
		free(data);
		data = temp;
		data[i] = ft_strdup(&content[ofset]);
		if (!data[i])
		{
			info->error = 1;
			ft_free_double_char(data);
			return (ft_printf_fd(2, "296-Error allocating memory\n"), NULL);
		}
		data[i + 1] = NULL;
	}
	ft_printf("Memory address of data struct: %p\n", (void *)data);
	return (data);
}
