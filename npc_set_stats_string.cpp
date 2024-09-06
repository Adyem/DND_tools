#include "dnd_tools.hpp"
#include "libft/libft/libft.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"

static int	ft_check_target_exists(char *target)
{
	if (ft_set_stats_check_name(target))
	{
		ft_printf_fd(2, "292-Error Target does not exist\n");
		return (1);
	}
	return (0);
}

static char **ft_handle_memory_error(t_char *info, char **data, int error_code)
{
	info->flags.error = 1;
	ft_free_double_char(data);
	ft_printf_fd(2, "%d-Error allocating memory\n", error_code);
	return (NULL);
}

static char **ft_allocate_initial_data(char *content, int ofset, t_char *info)
{
	char **data;

	data = (char **)malloc(sizeof(char *) * 2);
	if (!data)
		return (ft_handle_memory_error(info, NULL, 293));
	data[0] = ft_strdup(&content[ofset]);
	if (!data[0])
		return (ft_handle_memory_error(info, data, 294));
	data[1] = NULL;
	return (data);
}

static char **ft_reallocate_data_array(char **data, int new_size, t_char *info)
{
	char **temp;
	int i;

	temp = (char **)malloc(new_size * sizeof(char *));
	if (!temp)
		return (ft_handle_memory_error(info, data, 295));
	i = 0;
	while (data[i])
	{
		temp[i] = data[i];
		i++;
	}
	free(data);
	return (temp);
}

static char **ft_append_target_to_data(char **data, char *content, int ofset, t_char *info)
{
	int i;

	i = 0;
	while (data[i])
		i++;
	data = ft_reallocate_data_array(data, i + 2, info);
	if (!data)
		return (NULL);
	data[i] = ft_strdup(&content[ofset]);
	if (!data[i])
		return (ft_handle_memory_error(info, data, 296));
	data[i + 1] = NULL;
	return (data);
}

char **ft_set_stats_con_targets(char *content, int ofset, char **data, t_char *info)
{
	if (ft_check_target_exists(&content[ofset]))
		return (NULL);
	if (!data)
		return (ft_allocate_initial_data(content, ofset, info));
	else
		return (ft_append_target_to_data(data, content, ofset, info));
}
