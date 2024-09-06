#include "dnd_tools.hpp"

t_char	*ft_get_info(const char *tf_name, t_name *name)
{
	t_name		*temp;
	t_char		*info;
	int			found;
	const char	*input[2];

	info = NULL;
	found = 0;
	temp = name;
	input[0] = tf_name;
	input[1] = NULL;
	while (temp != NULL && !found)
	{
		if (ft_strcmp_dnd(tf_name, temp->name) == 0)
		{
			info = temp->function(0, input, name, 1);
			found = 1;
		}
		temp = temp->next;
	}
	return (info);
}
