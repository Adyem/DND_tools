#include "dnd_tools.h"

static void	ft_cast_hm_second_appli(t_char *target, const char **input)
{
	char	**temp;
	int		i;

	temp = ft_resize_double_char(target->debufs.hunters_mark.caster_name, input[2], 1);
	if (temp)
	{
		i = 0;
		while (target->debufs.hunters_mark.caster_name[i])
		{
			free(target->debufs.hunters_mark.caster_name[i]);
			i++;
		}
		free(target->debufs.hunters_mark.caster_name);
		target->debufs.hunters_mark.caster_name = temp;
	}
	else
		ft_printf_fd(2, "297-Error allocating memory target\n");
	return ;
}

static void	ft_cast_hunters_mark_cleanup(t_char *info, t_char *target, int fd[2], int error)
{
	if (info)
	{
		ft_npc_write_file(info, &info->stats, &info->c_resistance, fd[0]);
		ft_free_info(info);
	}
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

void ft_apply_hunters_mark(t_char *info, char **temp, const char **input)
{
	int	i;

    info->concentration.targets = temp;
    i = 0;
    while (input[3][i])
	{
        info->concentration.targets[0][i] = input[3][i];
        i++;
    }
    info->concentration.targets[0][i] = '\0';
    info->concentration.concentration = 1;
    info->concentration.spell_id = HUNTERS_MARK_ID;
    info->concentration.dice_faces_mod = 6;
    info->concentration.dice_amount_mod = 1;
    info->concentration.duration = 500;
}

void	ft_cast_hunters_mark(t_char *info, const char **input)
{
    char	**temp;
    t_char	*target;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	target = NULL;
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
	fd[0] = ft_open_file(info->name);
	if (fd[0] == -1)
	{
		info->flags.alreaddy_saved = 1;
		ft_cast_hunters_mark_cleanup(info, target, fd, 4);
		return ;
	}
	fd[1] = ft_open_file(target->name);
	if (fd[1] == -1)
	{
		ft_cast_hunters_mark_cleanup(info, target, fd, 5);
		return ;
	}
	ft_remove_concentration(info);
	if (ft_strcmp_dnd(target->name, info->name) == 0)
	{
		ft_cast_hunters_mark_cleanup(info, target, fd, 1);
		return ;
	}
    if (target && target->version_number >= 2)
	{
        if (!target->debufs.hunters_mark.caster_name)
            target->debufs.hunters_mark.caster_name = (char **)ft_calloc(2, sizeof(char *));
        else
            ft_cast_hm_second_appli(target, input);
    }
    temp = (char **)ft_calloc(1 + 1, sizeof(char *));
    if (!temp)
		return (ft_cast_hunters_mark_cleanup(info, target, fd, 2), (void)0);
    temp[0] = (char *)malloc((strlen(input[3]) + 1) * sizeof(char));
    if (!temp[0])
	{
		ft_cast_hunters_mark_cleanup(info, target, fd, 3);
        free(temp);
        return ( (void)0);
    }
    if (ft_remove_concentration(info))
		return (ft_cast_hunters_mark_cleanup(info, target, fd, 0), (void)0);
	ft_apply_hunters_mark(info, temp, input);
	ft_cast_hunters_mark_cleanup(info, target, fd, 0);
    return;
}
