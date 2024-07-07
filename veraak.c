#include "dnd_tools.h"

void	ft_veraak_turn(t_char *info)
{
	ft_update_buf(info);
	ft_printf("The veraak will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Veraak currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

static void ft_veraak_initialize(t_char *info)
{
    const char	*input[3];
    t_name		*name;
    int			i;
	const  char	*crystals[5] = {
        "chaos_crystal_01",
        "chaos_crystal_02",
        "chaos_crystal_03",
        "chaos_crystal_04",
        NULL
    };

    if (DEBUG == 1)
        ft_printf("initializing chaos crystals\n");
    i = 0;
    while (crystals[i] != NULL) {
        if (DEBUG == 1)
            ft_printf("checking crystal: %s\n", crystals[i]);
        name = info->struct_name;
        while (name != NULL) {
            if (ft_strcmp_dnd(name->name, crystals[i]) == 0) {
                input[0] = name->name;
                input[1] = "init";
                input[2] = NULL;
                if (DEBUG == 1)
                    ft_printf("initializing: %s\n", name->name);
                name->function(2, input, name, 0);
                break;
            }
            name = name->next;
        }
        i++;
    }
}

t_char	*ft_veraak(int index, const char **input, t_name *name, int exception)
{
	t_char	*info;

	if (DEBUG == 1) 
		ft_printf("index = %i\n", index);
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
	if (index == 2 && ft_strcmp_dnd(input[1], "init") == 0)
		ft_veraak_initialize(info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
