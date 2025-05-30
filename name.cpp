#include "dnd_tools.hpp"
#include "character.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <cstdlib>

void ft_free_memory_name(t_name *name, int exit_failure)
{
    t_name *current;
    t_name *next_node;

    current = name;
    while (current != ft_nullptr)
    {
        next_node = current->next;
        cma_free(current->name);
        cma_free(current);
        current = next_node;
    }
    if (exit_failure)
	{
		rl_clear_suggestions();
		cma_cleanup();
        exit(exit_failure);
	}
    return ;
}

static t_name *ft_add_node(t_name *first_node, t_name **last_node, const char *new_name,
							c_name new_function)
{
    t_name *new_node;

    new_node = static_cast<t_name *>(cma_malloc(sizeof(t_name)));
    if (!new_node)
    {
        pf_printf_fd(2, "112-Error: Malloc failure in Name Struct\n");
        ft_free_memory_name(first_node, 1);
    }
    new_node->name = cma_strdup(new_name);
    if (!new_node->name)
    {
        cma_free(new_node);
        pf_printf_fd(2, "113-Error: Malloc failure in Name Struct\n");
        ft_free_memory_name(first_node, 1);
    }
    new_node->function = new_function;
    new_node->next = ft_nullptr;
    if (*last_node)
        (*last_node)->next = new_node;
    else
        first_node = new_node;
    *last_node = new_node;
	rl_add_suggestion(new_node->name);
    return (new_node);
}

static char *ft_new_name(const char *name, int index)
{
    size_t new_name_length = static_cast<size_t>(ft_strlen(name) + 4);
    char *new_name;

        new_name = static_cast<char *>(cma_calloc(new_name_length, sizeof(char)));
    if (!new_name)
    {
        pf_printf_fd(2, "114-Error: Malloc failure in Name Struct\n");
        return (ft_nullptr);
    }
    snprintf(new_name, new_name_length, "%s_%02d", name, index);
    return (new_name);
}

static void ft_add_mob_series(t_name *first_node, t_name **last_node, const char *base_name,
								c_name function, int count)
{
    int index = 1;
    char *new_name;

    while (index <= count)
    {
        if (index > 50)
            break ;
        new_name = ft_new_name(base_name, index);
        if (!new_name)
        {
            pf_printf_fd(2, "115-Error: Malloc failure in Name Struct\n");
            ft_free_memory_name(first_node, 1);
        }
        if (DEBUG == 1)
            pf_printf("%s\n", new_name);
        ft_add_node(first_node, last_node, new_name, function);
        cma_free(new_name);
        index++;
    }
	return ;
}

t_name *ft_allocate_memory_name()
{
    t_name *last_node;
    t_name *first_node;

    last_node = ft_nullptr;
    first_node = ft_add_node(ft_nullptr, &last_node, "template", ft_template);
    ft_add_mob_series(first_node, &last_node, "template", ft_template, 10);
    ft_add_mob_series(first_node, &last_node, "goblin", ft_goblin, 10);
    ft_add_mob_series(first_node, &last_node, "chaos_goblin", ft_chaos_goblin, 10);
    ft_add_mob_series(first_node, &last_node, "chaos_crystal", ft_chaos_crystal, 4);
    ft_add_node(first_node, &last_node, "gundren_rockseeker", ft_gundren_rockseeker);
    ft_add_node(first_node, &last_node, "thorbald_ironpocket", ft_thorbald_ironpocket);
    ft_add_node(first_node, &last_node, "murna_claygrip", ft_murna_claygrip);
    ft_add_node(first_node, &last_node, "dorgar_stoneguard", ft_dorgar_stoneguard);
    ft_add_node(first_node, &last_node, "hilda_stormshield", ft_hilda_stormshield);
    ft_add_node(first_node, &last_node, "goblin_warmaster", ft_goblin_warmaster);
    ft_add_node(first_node, &last_node, "maverick", ft_maverick);
    ft_add_node(first_node, &last_node, "grizz", ft_grizz);
    ft_add_node(first_node, &last_node, "frank", ft_frank);
	ft_add_mob_series(first_node, &last_node, "ghost", ft_ghost, 10);
	ft_add_mob_series(first_node, &last_node, "dwarf_paladin", ft_dwarf_paladin, 10);
	ft_add_mob_series(first_node, &last_node, "felbeast", ft_felbeast, 10);
	ft_add_node(first_node, &last_node, "veraak", ft_veraak);
	ft_add_node(first_node, &last_node, "ancient predatory beast", ft_ancient_predatory_beast);
	ft_add_mob_series(first_node, &last_node, "snow_goblin", ft_snow_goblin, 10);
	ft_add_mob_series(first_node, &last_node, "night_elven_guard", ft_night_elven_guard, 10);
	ft_add_node(first_node, &last_node, "xavius", ft_xavius);
	ft_add_node(first_node, &last_node, "malfurion", ft_malfurion);
	ft_add_node(first_node, &last_node, "shield_spell_a", ft_shield_spell_a);
	ft_add_node(first_node, &last_node, "demonic_portal_a", ft_demonic_portal_a);
    return (first_node);
}
