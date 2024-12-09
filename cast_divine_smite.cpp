#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/CPP_class/string.hpp"
#include "libft/Printf/printf.hpp"

void	ft_cast_divine_smite(t_char *character)
{
	ft_string	availeble_slots = ft_check_availeble_spell_slots(character);

	if (availeble_slots.empty())
	{
		pf_printf_fd(2, "Error: No available spell slots for %s to cast Divine Smite.\n",
				character->name);
		return;
	}
	if (availeble_slots.getError())
	{
		pf_printf_fd(2, "Error: Failed to retrieve available spell slots for %s.\n",
				character->name);
		return;
	}
	ft_string message = "select the level u wanne cast the spell at: " + availeble_slots + ": ";
	if (message.getError())
	{
		pf_printf_fd(2, "Error: Failed to initialize message string.\n");
		return;
	}
	int level = ft_readline_spell_level(message.c_str(), character);
	int dice_roll_result = ft_dice_roll(level + 1, 8);
	if (dice_roll_result == -1)
	{
		pf_printf_fd(2, "Error: Dice roll for Divine Smite failed.\n");
		return;
	}
	pf_printf("%s cast Divine Smite at level %i and dealt %i %s damage\n",
			character->name, level, dice_roll_result, DAMAGE_TYPE_RADIANT);
	return;
}
