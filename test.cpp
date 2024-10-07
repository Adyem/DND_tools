#include "dnd_tools.hpp"
#include "character.hpp"

int ft_test_excecute(const char **input, int argc, t_name *name)
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

void	ft_test(t_name *name)
{
	ft_excecute_test("veraak", "init", name);
	ft_excecute_test("veraak", "attack", name);
	ft_excecute_test("veraak", "20", "poison", "damage", name);
	ft_excecute_test("veraak", "prone", name);
	ft_excecute_test("veraak", name);
	return ;
}
