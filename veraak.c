#include "dnd_tools.h"

static void ft_veraak_kill_crystal(const char *crystal, t_char *info, int phase)
{
    const char *input[3];
    t_name *name;

    if (DEBUG == 1)
        ft_printf("killing crystal: %s\n", crystal);
    name = info->struct_name;
    while (name != NULL)
	{
        if (ft_strcmp_dnd(name->name, crystal) == 0)
		{
            input[0] = name->name;
            input[1] = "kill";
            input[2] = NULL;
            if (DEBUG == 1)
                ft_printf("initializing: %s\n", name->name);
            name->function(2, input, name, 0);
            break;
        }
        name = name->next;
    }
	info->stats.phase = phase;
	info->stats.turn = 1;
	ft_printf("veraak transitions to the next phase dropping 2 green orbs at random " \
			"locations in the arena\n");
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

static void	ft_veraak_phase_transition(t_char *info)
{
	if (info->stats.health <= 200 && info->stats.phase == 1)
		ft_veraak_kill_crystal("chaos_crystal_01", info, 2);
	if (info->stats.health <= 160 && info->stats.phase == 2)
		ft_veraak_kill_crystal("chaos_crystal_02", info, 3);
	if (info->stats.health <= 120 && info->stats.phase == 3)
		ft_veraak_kill_crystal("chaos_crystal_03", info, 4);
	if (info->stats.health <= 80 && info->stats.phase == 4)
		ft_veraak_kill_crystal("chaos_crystal_04", info, 5);
}

void	ft_veraak_turn(t_char *info)
{
	ft_update_buf(info);
	ft_veraak_phase_transition(info);
	ft_veraak_check_phase(info);
	if (info->flags.prone)
	{
		ft_printf("%s will use his/her action to stand up\n", info->name);
		info->flags.prone = 0;
	}
	else
		ft_printf("The veraak will try to make either a ranged or melee attack during his turn\n");
	ft_printf("Veraak currently has %i/%i hp\n",
			info->stats.health, info->dstats.health);
}

t_char	*ft_veraak(const int index, const char **input, t_name *name, int exception)
{
	int		error;
	t_char	*info;
	
	error = 0;
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
	{
		ft_free_info(info);
		return (NULL);
	}
	if (index == 2 && ft_strcmp_dnd(input[1], "init") == 0)
	{
		ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
		ft_printf("Stats for %s written on a file\n", info->name);
		ft_veraak_initialize(info);
		ft_free_info(info);
		return (NULL);
	}
	error = ft_npc_open_file(info);
	if (error)
	{
		ft_free_info(info);
		return (NULL);
	}
	error = ft_npc_check_info(info);
	if (error)
	{
		ft_free_info(info);
		return (NULL);
	}
	ft_initialize_gear(info);
	if (exception)
		return (info);
	ft_npc_change_stats(info, index, input);
	ft_free_info(info);
	return (NULL);
}
