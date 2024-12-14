#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Template/shared_ptr.hpp"
#include "dnd_tools.hpp"
#include "veraak.hpp"

static void ft_veraak_kill_crystal(const char *crystal, SharedPtr<t_char>info, int phase)
{
    const char *input[3];
    t_name *name;

    if (DEBUG == 1)
        pf_printf("killing crystal: %s\n", crystal);
    name = info->struct_name;
    while (name != ft_nullptr)
    {
        if (ft_strcmp_dnd(name->name, crystal) == 0)
        {
            input[0] = name->name;
            input[1] = "kill";
            input[2] = ft_nullptr;
            if (DEBUG == 1)
                pf_printf("initializing: %s\n", name->name);
            name->function(2, input, name, 0);
            break ;
        }
        name = name->next;
    }
    info->stats.phase = phase;
    info->stats.turn = 1;
    pf_printf("veraak transitions to the next phase dropping 2 green orbs " \
			"at random locations in the arena\n");
	return ;
}

static void ft_veraak_initialize(SharedPtr<t_char>info)
{
    const char *input[3];
    t_name *name;
    int i;
    const char *crystals[5] = {
        "chaos_crystal_01", "chaos_crystal_02", "chaos_crystal_03", "chaos_crystal_04", ft_nullptr};

    if (DEBUG == 1)
        pf_printf("initializing chaos crystals\n");
    i = 0;
    while (crystals[i] != ft_nullptr)
    {
        if (DEBUG == 1)
            pf_printf("checking crystal: %s\n", crystals[i]);
        name = info->struct_name;
        while (name != ft_nullptr)
        {
            if (ft_strcmp_dnd(name->name, crystals[i]) == 0)
            {
                input[0] = name->name;
                input[1] = "init";
                input[2] = ft_nullptr;
                if (DEBUG == 1)
                    pf_printf("initializing: %s\n", name->name);
                name->function(2, input, name, 0);
                break ;
            }
            name = name->next;
        }
        i++;
    }
	return ;
}

static void ft_veraak_phase_transition(SharedPtr<t_char>info)
{
	if (info->stats.health <= 200 && info->stats.phase == 1)
		ft_veraak_kill_crystal("chaos_crystal_01", info, 2);
	if (info->stats.health <= 160 && info->stats.phase == 2)
		ft_veraak_kill_crystal("chaos_crystal_02", info, 3);
	if (info->stats.health <= 120 && info->stats.phase == 3)
		ft_veraak_kill_crystal("chaos_crystal_03", info, 4);
	if (info->stats.health <= 80 && info->stats.phase == 4)
		ft_veraak_kill_crystal("chaos_crystal_04", info, 5);
	return ;
}

void ft_veraak_turn(SharedPtr<t_char>info)
{
    ft_update_buf(info);
    ft_veraak_phase_transition(info);
    ft_veraak_check_phase(info);
    if (info->flags.prone)
    {
        pf_printf("%s will use his/her action to stand up\n", info->name);
        info->flags.prone = 0;
    }
    else
        pf_printf("The veraak will try to make either a ranged or melee attack during his turn\n");
    pf_printf("Veraak currently has %d/%d hp\n", info->stats.health, info->dstats.health);
	return ;
}

static void ft_initialize_gear_and_feats(SharedPtr<t_char>info)
{
	info->spells.hunters_mark = VERAAK_SPELLS_HUNTERS_MARK;
    return ;
}

SharedPtr<t_char>ft_veraak(const int index, const char **input, t_name *name, int exception)
{
    int error = 0;
    SharedPtr<t_char> info(1);

	if (!info)
    {
        pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
        return (SharedPtr<t_char>());
    }
    *info = VERAAK_INFO;
    info->name = input[0];
    info->struct_name = name;
    info->save_file = cma_strjoin("data/", input[0], false);
    if (!info->save_file)
    {
        ft_free_info(info);
        return (SharedPtr<t_char>());
    }
    if (index == 2 && ft_strcmp_dnd(input[1], "init") == 0)
    {
		ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
        pf_printf("Stats for %s written on a file\n", info->name);
        ft_veraak_initialize(info);
        ft_free_info(info);
        return (SharedPtr<t_char>());
    }
    error = ft_npc_open_file(info);
    if (error)
    {
        ft_free_info(info);
        return (SharedPtr<t_char>());
    }
    error = ft_npc_check_info(info);
    if (error)
    {
        ft_free_info(info);
        return (SharedPtr<t_char>());
    }
    ft_initialize_gear_and_feats(info);
    if (exception)
        return (info);
    ft_npc_change_stats(info, index, input);
    ft_free_info(info);
    return (SharedPtr<t_char>());
}
