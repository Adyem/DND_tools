#include "dnd_tools.hpp"
#include "character.hpp"

void	ft_test(t_name *name)
{
	g_dnd_test = true;
	ft_excecute_test("fclean", name);
	ft_excecute_test("veraak", "init", name);
	ft_excecute_test("veraak", "attack", name);
	ft_excecute_test("veraak", "20", "poison", "damage", name);
	ft_excecute_test("veraak", name);
	ft_excecute_test("veraak", "20", "poison", "damage", name);
	ft_excecute_test("veraak", "prone", name);
	ft_excecute_test("veraak", name);
	ft_excecute_test("maverick", "init", name);
	ft_excecute_test("goblin_01", "init", name);
	ft_excecute_test("goblin_02", "init", name);
	ft_excecute_test("veraak", "cast", "hunters_mark", "goblin_01", name);
	ft_excecute_test("goblin_02", "cast", "hunters_mark", "goblin_01", name);
	ft_excecute_test("frank", "init", name);
	ft_excecute_test("add", "player", "Adyem", name);
	ft_excecute_test("add", "player", "Stormking", name);
	ft_excecute_test("initiative", name);
	ft_excecute_test("ancient predatory beast", "init", name);
	ft_excecute_test("ancient predatory beast", "attack", name);
	ft_excecute_test("snow_goblin_01", "init", name);
	ft_excecute_test("snow_goblin_01", "ranged_attack", name);
	ft_excecute_test("night_elven_guard_01", "init", name);
	ft_excecute_test("night_elven_guard_01", "ranged_attack", name);
	ft_excecute_test("encounter", "xavius", name);
	g_dnd_test = false;
	return ;
}
