#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CPP_class/string.hpp"
#include "libft/Printf/printf.hpp"
#include <cassert>

static ft_string ft_check_availeble_spell_slots(t_char *character, int base_level)
{
	ft_string available_levels;

	if (base_level >= 1 && character->spell_slots.level_1.available > 0)
		available_levels.append(" 1,");
	if (base_level >= 2 && character->spell_slots.level_2.available > 0)
		available_levels.append(" 2,");
	if (base_level >= 3 && character->spell_slots.level_3.available > 0)
		available_levels.append(" 3,");
	if (base_level >= 4 && character->spell_slots.level_4.available > 0)
		available_levels.append(" 4,");
	if (base_level >= 5 && character->spell_slots.level_5.available > 0)
		available_levels.append(" 5,");
	if (base_level >= 6 && character->spell_slots.level_6.available > 0)
		available_levels.append(" 6,");
	if (base_level >= 7 && character->spell_slots.level_7.available > 0)
		available_levels.append(" 7,");
	if (base_level >= 8 && character->spell_slots.level_8.available > 0)
		available_levels.append(" 8,");
	if (base_level >= 9 && character->spell_slots.level_9.available > 0)
		available_levels.append(" 9,");
	if (!available_levels.empty())
		available_levels.erase(available_levels.size() - 1, 1);
	return (available_levels);
}

int ft_prompt_spell_level(t_char *character, int base_level)
{
	assert (base_level >= 0 && base_level <= 9);

	ft_string available_slots = ft_check_availeble_spell_slots(character, base_level);
    if (available_slots.getError())
    {
        pf_printf_fd(2, "Error: Failed to retrieve available spell slots for %s.\n",
                character->name);
        return (-1);
    }
    if (available_slots.empty())
    {
        pf_printf_fd(2, "Error: No available spell slots for %s to cast Divine Smite.\n",
                character->name);
        return (-1);
    }
    ft_string message = "Select the level you want to cast the spell at: "
        + available_slots + ": ";
    if (message.getError())
    {
        pf_printf_fd(2, "Error: Failed to initialize message string %s\n", message.errorStr());
        return (-1);
    }
    int level = 0;
    int invalid_input_amount = 0;
    while (level < base_level)
    {
        if (invalid_input_amount >= 5)
        {
            pf_printf_fd(2, "Error: Too many invalid attempts to select spell level.\n");
            return (-1);
        }
        level = ft_readline_spell_level(message, character, &invalid_input_amount);
        if (level == -1)
            return (-1);
        if (level < base_level)
        {
            pf_printf_fd(2, "Error: Selected level %d is below the minimum required level %d.\n",
                          level, base_level);
            invalid_input_amount++;
        }
    }
    return (level);
}

static int ft_perform_dice_roll(int total_dice, int dice_faces)
{
    int result = ft_dice_roll(total_dice, dice_faces);
    if (result == -1)
    {
        pf_printf_fd(2, "Error: Dice roll failed.\n");
        return (-1);
    }
    return (result);
}

int ft_calculate_spell_damage(int total_dice, int dice_faces, int extra_damage)
{
    int dice_roll_result = ft_perform_dice_roll(total_dice, dice_faces);
    if (dice_roll_result == -1)
        return (-1);
    return (dice_roll_result + extra_damage);
}

void ft_remove_spell_slot(t_spell_slots *spell_slots, int level_spell_used)
{
	assert(level_spell_used >= 1 && level_spell_used <= 9);

	if (level_spell_used == 1 && spell_slots->level_1.available > 0)
        spell_slots->level_1.available--;
	else if (level_spell_used == 2 && spell_slots->level_2.available > 0)
        spell_slots->level_2.available--;
	else if (level_spell_used == 3 && spell_slots->level_3.available > 0)
        spell_slots->level_3.available--;
	else if (level_spell_used == 4 && spell_slots->level_4.available > 0)
        spell_slots->level_4.available--;
	else if (level_spell_used == 5 && spell_slots->level_5.available > 0)
        spell_slots->level_5.available--;
	else if (level_spell_used == 6 && spell_slots->level_6.available > 0)
        spell_slots->level_6.available--;
	else if (level_spell_used == 7 && spell_slots->level_7.available > 0)
        spell_slots->level_7.available--;
	else if (level_spell_used == 8 && spell_slots->level_8.available > 0)
        spell_slots->level_8.available--;
	else if (level_spell_used == 9 && spell_slots->level_9.available > 0)
        spell_slots->level_9.available--;
	return ;
}