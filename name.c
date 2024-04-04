#include "dnd_tools.h"

static t_name	*ft_add_node(char *new_name, c_name new_function)
{
	t_name *new_node;

	new_node = (t_name *)malloc(sizeof(t_name));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(new_name);
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->function = new_function;
	new_node->next = NULL;
	return (new_node);
}

static char	*ft_new_name(char *name, int index)
{
	int		new_name_length ;
	char	*new_name;
	int		i;


	new_name_length = ft_strlen(name) + 1 + 2;
	new_name = (char *)ft_calloc(new_name_length + 1, sizeof(char));
	if (!new_name)
		return (NULL);
	i = 0;
	while (name[i])
	{
		new_name[i] = name[i];
		i++;
	}
	new_name[i] = '_';
	i++;
	if (index >= 10)
	{
		index = index - 10;
		new_name[i] = '1';
	}
	else
		new_name[i] = '0';
	i++;
	new_name[i] = index + '0';
	return (new_name);
}

t_name	*ft_allocate_memory_name()
{
	t_name	*name;
	t_name	*temp;
	char	*new_name;
	int		i;

	name = ft_add_node("maverick", ft_maverick);
	if (!name)
		ft_free_memory_name(name, 1);
	name->next = ft_add_node("zephyr", ft_zephyr);
	if (!name->next)
		ft_free_memory_name(name, 1);
	temp = name->next;
	temp->next = ft_add_node("air_totem", ft_air_totem);
	if (!temp->next)
		ft_free_memory_name(name, 1);
	i = 1;
	while (i <= 10)
	{
		temp = temp->next;
		new_name = ft_new_name("air_goblin", i);
		if (!new_name)
			ft_free_memory_name(name, 1);
		if (DEBUG == 1)
			ft_printf("%s\n", new_name);
		temp->next = ft_add_node(new_name, ft_air_goblin);
		free(new_name);
		if (!temp->next)
			ft_free_memory_name(name, 1);
		i++;
	}
	i = 1;
	while (i <= 10)
	{
		temp = temp->next;
		new_name = ft_new_name("air_goblin_shaman", i);
		if (!new_name)
			ft_free_memory_name(name, 1);
		if (DEBUG == 1)
			ft_printf("%s\n", new_name);
		temp->next = ft_add_node(new_name, ft_air_goblin);
		free(new_name);
		if (!temp->next)
			ft_free_memory_name(name, 1);
		i++;
	}
	return (name);
}

void	ft_free_memory_name(t_name *name, int exit_failure)
{
	t_name	*current;
	t_name	*next_node;

	current = name;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->name);
		free(current);
		current = next_node;
	}
	if (exit_failure)
		exit(EXIT_FAILURE);
	return ;
}
