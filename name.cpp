#include "dnd_tools.hpp"
#include "character.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include <cstdlib>

void ft_free_memory_name(t_name *name, int exit_failure)
{
    t_name *current;
    t_name *next_node;

    current = name;
    while (current != nullptr)
    {
        next_node = current->next;
        cma_free(current->name);
        cma_free(current);
        current = next_node;
    }
    if (exit_failure)
	{
		rl_clear_suggestions();
        exit(exit_failure);
	}
    return ;
}

static t_name *ft_add_node(t_name *first_node, t_name **last_node, const char *new_name, c_name new_function)
{
    t_name *new_node;

    new_node = (t_name *)cma_malloc(sizeof(t_name), true);
    if (!new_node)
    {
        ft_printf_fd(2, "112-Error: Malloc failure in Name Struct\n");
        ft_free_memory_name(first_node, 1);
    }
    new_node->name = cma_strdup(new_name, true);
    if (!new_node->name)
    {
        cma_free(new_node);
        ft_printf_fd(2, "113-Error: Malloc failure in Name Struct\n");
        ft_free_memory_name(first_node, 1);
    }
    new_node->function = new_function;
    new_node->next = nullptr;
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
    int new_name_length;
    char *new_name;

    new_name_length = ft_strlen(name) + 4;
    new_name = (char *)cma_calloc(new_name_length, sizeof(char), true);
    if (!new_name)
    {
        ft_printf_fd(2, "114-Error: Malloc failure in Name Struct\n");
        return (nullptr);
    }
    snprintf(new_name, new_name_length, "%s_%02d", name, index);
    return (new_name);
}

static void ft_add_mob_series(t_name *first_node, t_name **last_node, const char *base_name, c_name function, int count)
{
    int i;
    char *new_name;

    i = 1;
    while (i <= count)
    {
        if (i > 99)
            break ;
        new_name = ft_new_name(base_name, i);
        if (!new_name)
        {
            ft_printf_fd(2, "115-Error: Malloc failure in Name Struct\n");
            ft_free_memory_name(first_node, 1);
        }
        if (DEBUG == 1)
            ft_printf("%s\n", new_name);
        ft_add_node(first_node, last_node, new_name, function);
        cma_free(new_name);
        i++;
    }
}

t_name *ft_allocate_memory_name()
{
    t_name *last_node;
    t_name *first_node;

	last_node = nullptr;
    first_node = ft_add_node(nullptr, &last_node, "template", ft_template);
    ft_add_mob_series(first_node, &last_node, "template", ft_template, 10);
    ft_add_mob_series(first_node, &last_node, "goblin", ft_goblin, 10);
    ft_add_mob_series(first_node, &last_node, "chaos_goblin", ft_chaos_goblin, 10);
    ft_add_node(first_node, &last_node, "veraak", ft_veraak);
    ft_add_mob_series(first_node, &last_node, "chaos_crystal", ft_chaos_crystal, 4);
    ft_add_node(first_node, &last_node, "gundren_rockseeker", ft_gundren_rockseeker);
    ft_add_node(first_node, &last_node, "goblin_warmaster", ft_goblin_warmaster);
	ft_add_node(first_node, &last_node, "maverick", ft_maverick);
    return (first_node);
}
