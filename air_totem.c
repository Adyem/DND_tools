#include "dnd_tools.h"

t_char	*ft_air_totem(int index, char **input, t_name *name, int exception)
{
	t_char	*info;

	info = (t_char *)malloc(sizeof(t_char));
	if (!info)
		return (NULL);
	*info = AIR_TOTEM_INFO;
	info->struct_name = name;
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	free(info);
	return (NULL);
}
