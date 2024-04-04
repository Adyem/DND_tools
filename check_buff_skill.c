#include "dnd_tools.h"

int	ft_skill_check_buff(t_char *info, int *roll, char *skill)
{
	(void)skill;
	ft_reroll(info, roll);
	return (0);
}
