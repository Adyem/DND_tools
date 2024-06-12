#include "character.h"
#include "dnd_tools.h"

static void	ft_cast_hm_second_appli(t_char *target, char **input)
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

void ft_cast_hunters_mark(t_char *info, char **input) {
    char **temp;
    int i;
    int fd;
    t_char *target;

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
	ft_remove_concentration(info);
	if (ft_strcmp_dnd(target->name, info->name) == 0)
	{
		ft_printf_fd(2, "305-Error cant cast hunters mark on yourself\n");
		ft_free_info(target);
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
        return (ft_printf_fd(2, "299-Error allocating memory targets\n"), (void)0);
    temp[0] = (char *)malloc((strlen(input[3]) + 1) * sizeof(char));
    if (!temp[0])
	{
        free(temp);
        return (ft_printf_fd(2, "299-Error allocating memory targets[0]\n"), (void)0);
    }
    ft_remove_concentration(info);
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
	fd = open(target->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd)
		ft_npc_write_file(info, &info->stats, &info->c_resistance, fd);
	else
		ft_printf_fd(2, "264-Error opening file %s\n", strerror(errno));
	ft_free_info(target);
    return;
}

void	ft_cast_chaos_armor(t_char *info, char **input)
{
	ft_remove_concentration(info);
	info->concentration.concentration = 1;
	info->concentration.spell_id = CHAOS_ARMOR_ID;
	info->concentration.duration = 5;
	info->bufs.chaos_armor.duration = 5;
}
