#include "dnd_tools.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <readline/readline.h>

static void ft_initialize_variables(int *fd, char **string, t_char **target)
{
	int i = 0;
	while (i < 20)
	{
		string[i] = nullptr;
		fd[i] = -1;
		target[i] = nullptr;
		i++;
	}
}

static int ft_check_target_amount(int target_amount)
{
	if (target_amount > 20)
	{
		ft_printf_fd(2, "110-Error too many targets\n");
		return (0);
	}
	return (1);
}

static char *ft_read_target_name(int i)
{
	char message[55];
	char *target_name;

	sprintf(message, "Requesting the name of the %s target", ft_ordinal_suffix(i + 1));
	target_name = readline(message);
	if (!target_name)
	{
		ft_printf_fd(2, "108-Error: Failed to allocate memory for readline target\n");
		return (NULL);
	}
	return (target_name);
}

static t_char *ft_validate_and_fetch_target(char *target_name, t_char *info)
{
	if (ft_set_stats_check_name(target_name))
	{
		if (ft_check_player_character(target_name))
		{
			ft_printf_fd(2, "111-Error: target does not exist\n");
			return (NULL);
		}
		return (NULL);
	}
	else
	{
		t_char *target_info = ft_get_info(target_name, info->struct_name);
		if (!target_info)
		{
			ft_printf_fd(2, "109-Error getting info for %s\n", target_name);
			return (NULL);
		}
		return (target_info);
	}
}

static void ft_free_memory_on_error(t_char **target, char **string, int amount)
{
	int j = 0;
	while (j < amount)
	{
		if (target[j])
			ft_free_info(target[j]);
		if (string[j])
			free(string[j]);
		target[j] = NULL;
		string[j] = NULL;
		j++;
	}
}

void	ft_cast_concentration_multi_target(t_char *info, const char **input, t_buff *buff)
{
	int		fd[20];
	char	*string[20];
	t_char	*target[20];
	int		i;

	(void)input;
	ft_initialize_variables(fd, string, target);
	if (!ft_check_target_amount(buff->target_amount))
		return ;
	i = 0;
	while (i < buff->target_amount)
	{
		string[i] = ft_read_target_name(i);
		if (!string[i])
		{
			ft_free_memory_on_error(target, string, i);
			return ;
		}
		target[i] = ft_validate_and_fetch_target(string[i], info);
		if (!target[i])
			continue ;
		i++;
	}
}
