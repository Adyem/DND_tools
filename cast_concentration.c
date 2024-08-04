#include "dnd_tools.h"

static void	ft_cast_concentration_cleanup(t_char *info, t_char *target, int fd[2], int error)
{
	if (info)
		ft_npc_write_file(info, &info->stats, &info->c_resistance, fd[0]);
	if (target)
	{
		ft_npc_write_file(target, &target->stats, &target->c_resistance, fd[1]);
		ft_free_info(target);
	}
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (error == 1)
		ft_printf_fd(0, "305-Error cant cast hunters mark on yourself\n");
	else if (error == 2)
        ft_printf_fd(2, "299-Error allocating memory targets\n");
	else if (error == 3)
		ft_printf_fd(2, "299-Error allocating memory targets[0]\n");
	else if (error == 4)
		ft_printf_fd(2, "320-Error opening file: %s", strerror(errno));
	else if (error == 5)
		ft_printf_fd(2, "321-Error opening file: %s", strerror(errno));
	return ;
}

int ft_apply_concentration_buff(t_char *info, t_char *target, int fd[2], const char **input, t_buff *buff)
{
	char	**temp;
	int		i;

	temp = (char **)ft_calloc(1 + 1, sizeof(char *));
    if (!temp)
	{
		ft_cast_concentration_cleanup(info, target, fd, 2);
		return (1);
	}
    temp[0] = (char *)malloc((ft_strlen(input[3]) + 1) * sizeof(char));
    if (!temp[0])
	{
		ft_cast_concentration_cleanup(info, target, fd, 3);
        free(temp);
        return (1);
    }
    info->concentration.targets = temp;
    i = 0;
    while (input[3][i])
	{
        info->concentration.targets[0][i] = input[3][i];
        i++;
    }
    info->concentration.targets[0][i] = '\0';
    info->concentration.concentration = 1;
    info->concentration.spell_id = buff->spell_id;
    info->concentration.dice_faces_mod = buff->dice_faces_mod;
    info->concentration.dice_amount_mod = buff->dice_amount_mod;
    info->concentration.duration = buff->duration;
	return (0);
}

static int	ft_cast_concentration_open_file(int fd[2], t_char *info, t_char *target)
{
	fd[0] = ft_open_file(info->save_file);
	if (fd[0] == -1)
	{
		info->flags.alreaddy_saved = 1;
		ft_cast_concentration_cleanup(info, target, fd, 4);
		return (1);
	}
	fd[1] = ft_open_file(target->save_file);
	if (fd[1] == -1)
	{
		ft_cast_concentration_cleanup(info, target, fd, 5);
		return (1);
	}
	return (0);
}

void	ft_cast_concentration(t_char *info, const char **input, t_buff *buff)
{
	t_char	*target;
	int		fd[2];

	if (ft_remove_concentration(info))
		return ;
	fd[0] = -1;
	fd[1] = -1;
	if (DEBUG == 1)
		ft_printf("%s %s\n", input[0], input[3]);
	if ((ft_set_stats_check_name(input[3])))
	{
		if ((ft_check_player_character(input[3])))
			return;
		else
			target = NULL;
	}
	else
	{
		target = ft_get_info(input[3], info->struct_name);
		if (!target)
			return (ft_printf_fd(2, "295-Error getting info %s\n", input[2]), (void)0);
	}
	if (ft_cast_concentration_open_file(fd, info, target))
		return ;
	if (ft_strcmp_dnd(target->name, info->name) == 0)
	{
		ft_cast_concentration_cleanup(info, target, fd, 1);
		return ;
	}
    if (target && target->version_number >= 2)
		buff->cast_spell(target, input, buff);
    if (ft_remove_concentration(info))
		return (ft_cast_concentration_cleanup(info, target, fd, 0), (void)0);
	if (ft_apply_concentration_buff(info, target, fd, input, buff))
		return ;
	ft_cast_concentration_cleanup(info, target, fd, 0);
    return;
}
