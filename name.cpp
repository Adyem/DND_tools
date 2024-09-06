#include "dnd_tools.hpp"
#include "character.hpp"
#include "libft/libft/libft.hpp"
#include "libft/printf/ft_printf.hpp"

void ft_free_memory_name(t_name *name, int exit_failure)
{
    t_name *current;
    t_name *next_node;

    current = name;
    while (current != NULL)
    {
        next_node = current->next;
        free(current->name);
        free(current);
        current = next_node;
    }
	if (exit_failure)
		exit(exit_failure);
	return ;
}

static t_name *ft_add_node(t_name *first_node, t_name **last_node, const char *new_name, c_name new_function)
{
    t_name *new_node;

    new_node = (t_name *)malloc(sizeof(t_name));
    if (!new_node)
        ft_free_memory_name(first_node, 1);
    new_node->name = ft_strdup(new_name);
    if (!new_node->name)
    {
        free(new_node);
        ft_free_memory_name(first_node, 1);
    }
    new_node->function = new_function;
    new_node->next = NULL;
	if (*last_node)
		(*last_node)->next = new_node;
	else
		first_node = new_node;
	*last_node = new_node;
    return new_node;
}

static char *ft_new_name(const char *name, int index)
{
    int		new_name_length;
    char	*new_name;

    new_name_length = ft_strlen(name) + 4;
    new_name = (char *)ft_calloc(new_name_length, sizeof(char));
    if (!new_name)
        return (NULL);
    snprintf(new_name, new_name_length, "%s_%02d", name, index);
    return new_name;
}

static void ft_add_mob_series(t_name *first_node, t_name **last_node, const char *base_name, c_name function, int count)
{
    int		i;
    char	*new_name;

	i = 1;
	while (i <= count)
    {
		if (i > 99)
			break ;
        new_name = ft_new_name(base_name, i);
        if (!new_name)
            ft_free_memory_name(first_node, 1);
        if (DEBUG == 1)
            ft_printf("%s\n", new_name);
        ft_add_node(first_node, last_node, new_name, function);
        free(new_name);
		i++;
    }
	return ;
}

t_name *ft_allocate_memory_name()
{
    t_name *last_node;
    t_name *first_node;

    first_node = NULL;
    last_node = NULL;
    // template is always the first node
	first_node = ft_add_node(NULL, &last_node, "template", ft_template);
	ft_add_mob_series(first_node, &last_node, "template", ft_template, 10);
	ft_add_mob_series(first_node, &last_node, "goblin", ft_goblin, 10);
	ft_add_mob_series(first_node, &last_node, "chaos_goblin", ft_chaos_goblin, 10);
	ft_add_node(first_node, &last_node, "veraak", ft_veraak);
	ft_add_mob_series(first_node, &last_node, "chaos_crystal", ft_chaos_crystal, 4);
    return first_node;
}
