#include "dnd_tools.h"

t_char	*ft_get_info(char *tf_name, t_name *name)
{
	t_name	*temp;
	t_char	*info;
	int		found;

	info = NULL;
	found = 0;
	temp = name;
	while (temp != NULL && !found)
	{
		if (ft_strcmp_dnd(tf_name, temp->name) == 0)
		{
			info = temp->function(0, NULL, name, 1);
			found = 1;
		}
		temp = temp->next;
	}
	return (info);
}
