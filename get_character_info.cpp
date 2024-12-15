#include "dnd_tools.hpp"
#include "libft/CPP_class/nullptr.hpp"

ft_sharedptr<t_char> ft_get_info(const char *tf_name, t_name *name)
{
	t_name				*temp;
	ft_sharedptr<t_char> 	info;
	int					found;
	const char			*input[2];

	found = 0;
	temp = name;
	input[0] = tf_name;
	input[1] = ft_nullptr;
	while (temp != ft_nullptr && !found)
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
