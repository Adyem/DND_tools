#include "dnd_tools.hpp"
#include "character.hpp"

static int ft_handle_custom_commands(const char **input, int argc, t_name *name)
{
	t_name *temp;

	temp = name;
	while (temp != nullptr)
	{
		if (argc > 0 && ft_strcmp_dnd(input[0], temp->name) == 0)
		{
			temp->function(argc, (const char **)input, name, 0);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static int ft_handle_builtins(const char **input, int i, t_name *name)
{
	if (i == 1 && ft_strcmp_dnd(input[0], "exit") == 0)
		return (-1);
	else if (i == 1 && ft_strcmp_dnd(input[0], "fclean") == 0)
		ft_fclean();
	else if (i == 1 && ft_strcmp_dnd(input[0], "clean") == 0)
		ft_clean();
	else if (i == 1 && ft_strcmp_dnd(input[0], "initiative") == 0)
		ft_open_all_files(name);
	else if (i == 1 && ft_strcmp_dnd(input[0], "turn") == 0)
		ft_turn_next(name);
	else if (i == 1 && ft_strcmp_dnd(input[0], "test") == 0)
		ft_test(name);
	else if (i == 3 && ft_strcmp_dnd(input[1], "player") == 0)
		ft_player((const char **)input);
	else
		return (0);
	return (1);
}

int ft_test_excecute(const char **input, int argc, t_name *name)
{
	int	found;

	found = ft_handle_builtins(input, argc, name);
	if (found)
		return (0);
	found = ft_handle_custom_commands(input, argc, name);
	return (0);
}

void	ft_test(t_name *name)
{
	dnd_test = true;
	ft_fclean();
	ft_excecute_test("veraak", "init", name);
	ft_excecute_test("veraak", "attack", name);
	ft_excecute_test("veraak", "20", "poison", "damage", name);
	ft_excecute_test("veraak", "prone", name);
	ft_excecute_test("veraak", name);
	ft_excecute_test("goblin_01", "init", name);
	ft_excecute_test("goblin_02", "init", name);
	ft_excecute_test("veraak", "cast", "hunters_mark", "goblin_01", name);
	ft_excecute_test("goblin_02", "cast", "hunters_mark", "goblin_01", name);
	dnd_test = false;
	return ;
}
