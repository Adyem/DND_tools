#include "dnd_tools.h"

void	ft_kill(t_char *info)
{
	int temp;

	temp = info->stats.health;
	info->stats.health = 0;
	ft_print_character_status(info, temp, temp);
}
