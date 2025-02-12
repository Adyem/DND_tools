#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "treeNode.hpp"

static int ft_handle_int_mapping(char **content, int index, t_char * info)
{
	const t_treeNode_value *return_value
		= tree_node_search(*(ft_return_main_treeNode()), content[index]);
	if (!return_value)
		return (1);
	if (return_value->return_field_integer && (return_value->key_length != 0
				&& return_value->return_field_integer != ft_nullptr)
				&& ((return_value->unset_value == -1
				|| *(return_value->return_field_integer) == return_value->unset_value)))
    {
        *(return_value->return_field_integer) = ft_check_stat(info, content[index],
				return_value->key_length);
        return (0);
    }
	else if (return_value->return_field_double)
	{
		*return_value->return_field_double = ft_set_stats_con_targets(content[index],
				return_value->key_length, *return_value->return_field_double, info);
		return (0);
	}
	else if (return_value->return_field_string)
	{
		ft_set_stat_player(return_value->key_length,
				(const char **)return_value->return_field_string, content[index]);
		return (0);
	}
    return (1);
}

int ft_set_stats(t_char * info, char **content)
{
    if (initialize_stat_key_value_pairs(info))
		return (1);
    int index = 0;
    while (content[index])
	{
        if (ft_handle_int_mapping(content, index, info) == 0)
		{
            index++;
            continue ;
        }
        pf_printf_fd(2, "1-Something is wrong with the save file for %s at the line: %s"
                         ", please reinitialize the save\n", info->name, content[index]);
        info->flags.error = 1;
        return (1);
    }
    return (0);
}
