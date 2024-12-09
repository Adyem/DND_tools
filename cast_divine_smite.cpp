#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/CPP_class/string.hpp"
#include "libft/Printf/printf.hpp"

void	ft_cast_divine_smite(t_char *character)
{
	ft_string	availeble_slots = ft_check_availeble_spell_slots(character);

	if (availeble_slots.empty())
		return ;
	if (availeble_slots.getError())
		return ;
	ft_string message = "select the level u wanne cast the spell at: ";
	if (message.getError())
		return ;
	message.append(availeble_slots);
	if (message.getError())
		return ;
	message.append(": ");
	if (message.getError())
		return ;
	int level = ft_readline_spell_level(message.c_str(), character);
	int dice_roll_result = ft_dice_roll(level + 1, 8);
	if (dice_roll_result == -1)
		return ;
	pf_printf("%s cast divine smite at level %i and dealt %i %s damage\n",
			character->name, level, dice_roll_result, DAMAGE_TYPE_RADIANT);
	return ;
}
