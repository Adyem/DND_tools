#include "dnd_tools.hpp"

int	ft_skill_check_buff(t_char * info, int *roll, const char *skill)
{
	(void)skill;
	ft_reroll(info, roll);
	return (0);
}
