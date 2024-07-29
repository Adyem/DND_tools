#include "dnd_tools.h"

void	ft_detect_buff_debuff(t_char *target, const char **input, t_buff *buff)
{
	if (buff->spell_id == HUNTERS_MARK_ID)
		ft_cast_hunters_mark_second_appli(target, input);
	else
		ft_printf_fd(2, "164-Error invalid spell id\n");
	return ;
}
