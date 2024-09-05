#include "dnd_tools.h"

void	ft_cast_concentration_multi_target(t_char *info, const char **input, t_buff *buff)
{
	int		fd[20];
	int		i;
	char	*string;
	char	message[55];
	t_char	*target[20];

	if (buff->target_amount > 20)
	{
		ft_printf_fd(2, "110-Error too manny targets\n");
		return ;
	}
	i = 0;
	while (i < buff->target_amount)
	{
		sprintf(message, "Requesting the name of the %s target", ft_ordinal_suffix(i + 1));
		string = readline(message);
		if (!string)
		{
			ft_printf_fd(2, "108-Error: Failed to allocate memory readline target\n");
			return ;
		}
		if (ft_set_stats_check_name(string))
		{
			if (ft_check_player_character(string))
				return ;
			else
				target[i] = NULL;
		}
		else
		{
			target[i] = ft_get_info(string, info->struct_name);
			if (!target[i])
				return (ft_printf_fd(2, "109-Error getting info %s\n", input[2]), (void)0);
		}
		i++;
	}
}
