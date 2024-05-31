#include "dnd_tools.h"

void	ft_cast_hunters_mark(t_char *info, char **input)
{
	char	**temp;
	int		i;
	int		fd;
	t_char	*target;

	temp = NULL;
	if (ft_set_stats_check_name(input[2]))
		return (ft_printf_fd(2, "Error target does not exist"), (void)0);
	target = ft_get_info(input[2], info->struct_name);
	if (!target)
		return (ft_printf_fd(2, "295-Error getting info %s\n", input[2]), (void)0);
	if (!target->debufs.hunters_mark.caster_name)
		target->debufs.hunters_mark.caster_name = (char **)malloc(2 * sizeof(char *));
	else
	{
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
		{
			ft_printf_fd(2, "297-Error allocating memory target\n");
			return ;
		}
	}
	info->concentration.targets = (char **)ft_calloc((1 + 1), sizeof(char *));
	if (!info->concentration.targets)
		return (ft_printf_fd(2, "299-Error allocating memory targets\n"), (void)0);
	info->concentration.concentration = 1;
	info->concentration.spell_id = HUNTERS_MARK_ID;
	info->concentration.dice_faces_mod = 6;
	info->concentration.dice_amount_mod = 1;
	info->concentration.duration = 50;
	fd = open(target->save_file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	ft_npc_write_file(info, &info->stats, &info->c_resistance, fd);
	return ;
}
