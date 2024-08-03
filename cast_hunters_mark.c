#include "dnd_tools.h"

void	ft_cast_hunters_mark(t_char *info, const char **input)
{
	t_buff	buff;

	buff.error = 1;
	buff.duration = 50;
	buff.dice_faces_mod = 6;
	buff.dice_amount_mod = 1;
	buff.spell_id = HUNTERS_MARK_ID;
	buff.buff = 0;
	buff.cast_spell = ft_cast_hunters_mark_second_appli;
	ft_cast_concentration(info, input, &buff);
	return ;
}

void	ft_cast_hunters_mark_second_appli(t_char *target, const char **input, t_buff *buff)
{
	int	i;

	if (DEBUG == 1)
		ft_printf("setting the caster name in the target %s %p\n", input[0], (void *)target);
	if (target)
		ft_update_caster_name(&target->debufs.hunters_mark.caster_name, input[0], buff);
	if (DEBUG == 1 && target)
	{
		i = 0;
		while (target->debufs.hunters_mark.caster_name && target->debufs.hunters_mark.caster_name[i])
		{
			ft_printf("%s has cast hunters mark\n", target->debufs.hunters_mark.caster_name[i]);
			i++;
		}
	}
	target->debufs.hunters_mark.amount++;
	return ;
}
