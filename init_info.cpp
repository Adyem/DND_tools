#include "dnd_tools.hpp"
#include "libft/printf/ft_printf.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"

int	ft_check_stat(t_char *info, const char *stat, int index)
{
	int	temp;
	int	result;

	temp = index;
	if (DEBUG == 1)
		ft_printf("%s\n", stat);
	while (index)
	{
		stat++;
		index--;
	}
	if (ft_check_value(stat))
	{
		while (temp)
		{
			stat--;
			temp--;
		}
		ft_printf_fd(2, "2-Something is wrong with the save file from %s at the line: %s\n",
			info->name ,stat);
		return (-99999);
	}
	result = ft_atoi(stat);
	return (result);
}

void	ft_print_info(t_char *info)
{
	if (DEBUG != 1)
		return ;
	ft_printf("info->stats.health=%i\n", info->stats.health);
	return ;
}

int	ft_initialize_info(t_char *info, char **content)
{
	int	j;
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (content[i])
	{
		j = 0;
		while (content[i][j])
		{
			if (content[i][j] == '\n')
				content[i][j] = '\0';
			j++;
		}
		i++;
	}
	error += ft_set_stats(info, content);
	ft_print_info(info);
	return (error);
}
