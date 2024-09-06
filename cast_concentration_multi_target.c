#include "dnd_tools.h"

void	ft_cast_concentration_multi_target(t_char *info, const char **input, t_buff *buff)
{
	int		j;
	int		fd[20];
	int		i;
	char	*string[20];
	char	message[55];
	t_char	*target[20];

	i = 0;
	while (i < 20)
	{
		string[i] = NULL;
		fd[i] = -1;
		target[i] = NULL;
		i++;
	}
	(void)fd;
	if (buff->target_amount > 20)
	{
		ft_printf_fd(2, "110-Error too manny targets\n");
		return ;
	}
	i = 0;
	while (i < buff->target_amount)
	{
		sprintf(message, "Requesting the name of the %s target", ft_ordinal_suffix(i + 1));
		string[i] = readline(message);
		if (!string[i])
		{
			j = 0;
			while (j < 20)
			{
				free(string[j]);
				j++;
			}
			ft_printf_fd(2, "108-Error: Failed to allocate memory readline target\n");
			return ;
		}
		if (ft_set_stats_check_name(string[i]))
		{
			if (ft_check_player_character(string[i]))
			{
				ft_printf_fd(2, "111-Error: target does not exist\n");
				continue ;
			}
			else
				target[i] = NULL;
		}
		else
		{
			target[i] = ft_get_info(string[i], info->struct_name);
			if (!target[i])
			{
				j = 0;
				while (target[j])
				{
					ft_free_info(target[j]);
					free(string[j]);
					target[j] = NULL;
					j++;
				}
				return (ft_printf_fd(2, "109-Error getting info %s\n", input[2]), (void)0);
			}
		}
		i++;
	}
}
