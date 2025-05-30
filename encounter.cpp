#include "dnd_tools.hpp"

void	ft_encounter(const char *encounter_name, t_name *name)
{
	if (ft_strcmp_dnd(encounter_name, "xavius") == 0)
	{
		ft_excecute_test("shield_spell_a", "init", name);
		ft_excecute_test("demonic_portal_a", "init", name);
		ft_excecute_test("xavius", "init", name);
		ft_excecute_test("malfurion", "init", name);
	}
	return ;
}
