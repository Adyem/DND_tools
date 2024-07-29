#include "character.h"
#include "dnd_tools.h"
#include "identification.h"

void	ft_cast_hunters_mark(t_char *info, const char **input)
{
	t_buff	buff;

	buff.error = 1;
	buff.duration = 50;
	buff.dice_faces_mod = 6;
	buff.dice_amount_mod = 1;
	buff.spell_id = HUNTERS_MARK_ID;
	buff.buff = 0;
	ft_cast_concentration(info, input, buff);
	return ;
}
