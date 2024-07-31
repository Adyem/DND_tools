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
	ft_cast_concentration(info, input, &buff);
	return ;
}

void	ft_cast_hunters_mark_second_appli(t_char *target, const char **input)
{
	if (target && target->version_number >= 2)
		ft_update_caster_name(&target->debufs.hunters_mark.caster_name, input[0]);
	else
		ft_printf_fd(2, "297-Error allocating memory target\n");
	return ;
}
