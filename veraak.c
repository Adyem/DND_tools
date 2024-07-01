#include "chaos_crystal.h"
#include "dnd_tools.h"

void	ft_veraak_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The veraak will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Veraak currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

static void	ft_veraak_initialize(t_char *info)
{
	char	*input[3];
	t_name	*name;
	int		found;
	int		i;
	char	*crystals[5] = {
		"chaos_crystal_01",
		"chaos_crystal_02",
		"chaos_crystal_03",
		"chaos_crystal_04",
		NULL
	};
	found = 0;
	i = 0;
	while (crystals[i] != NULL)
	{
		name = info->struct_name;
		while (name != NULL && !found)
		{
			if (ft_strcmp_dnd(name->name, crystals[i]) == 0)
			{
				input[0] = name->name;
				input[1] = "init";
				input[2] = NULL;
				name->function(2, input, name, 0);
				found = 1;
			}
			name = name->next;
			i++;
		}
	}
}

t_char	*ft_veraak(int index, char **input, t_name *name, int exception)
{
	t_char	*info;

	info = (t_char *)calloc(1, sizeof(t_char));
	if (!info)
		return (NULL);
	*info = VERAAK_INFO;
	info->name = input[0];
	info->struct_name = name;
	info->save_file = ft_strjoin("data/", input[0]);
	if (!info->save_file)
		return (NULL);
	if (exception)
		return (info);
	if (index == 2 && ft_strcmp_dnd(input[1], "init"))
		ft_veraak_initialize(info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
