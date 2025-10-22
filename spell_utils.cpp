#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/RNG/rng.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"

static t_spell_slot *ft_get_spell_slot(t_char *character, int level)
{
    if (level == 1)
        return (&character->spell_slots.level_1);
    else if (level == 2)
        return (&character->spell_slots.level_2);
    else if (level == 3)
        return (&character->spell_slots.level_3);
    else if (level == 4)
        return (&character->spell_slots.level_4);
    else if (level == 5)
        return (&character->spell_slots.level_5);
    else if (level == 6)
        return (&character->spell_slots.level_6);
    else if (level == 7)
        return (&character->spell_slots.level_7);
    else if (level == 8)
        return (&character->spell_slots.level_8);
    else if (level == 9)
        return (&character->spell_slots.level_9);
    return (ft_nullptr);
}

static int ft_auto_cast(t_char *character, int base_level, const char *spell_name)
{
    int current_level;
    t_spell_slot *spell_slot;

    current_level = base_level;
    if (current_level < 1)
        current_level = 1;
    while (current_level <= 9)
    {
        spell_slot = ft_get_spell_slot(character, current_level);
        if (spell_slot != ft_nullptr && spell_slot->available > 0)
            return (current_level);
        current_level++;
    }
    pf_printf_fd(2, "Error: No available spell slots for %s to cast %s.\n",
            character->name, spell_name);
    return (-1);
}

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

int ft_prompt_spell_level(t_char *character, int base_level, const char *spell_name)
{
    if (!(base_level >= 0 && base_level <= 9))
    {
        pf_printf_fd(2, "Error: Invalid base level %d for %s.\n", base_level,
                spell_name ? spell_name : "spell");
        return (-1);
    }

    if (g_dnd_test)
        return (ft_auto_cast(character, base_level, spell_name));
    ft_string available_slots = ft_check_availeble_spell_slots(character, base_level);
    if (available_slots.get_error())
    {
        pf_printf_fd(2, "Error: Failed to retrieve available spell slots for %s.\n",
                character->name);
        return (-1);
    }
    if (available_slots.empty())
    {
        pf_printf_fd(2, "Error: No available spell slots for %s to cast %s.\n",
                character->name, spell_name);
        return (-1);
    }
    ft_string message = "Select the level you want to cast the spell at: "
        + available_slots + ": ";
    if (message.get_error())
    {
        pf_printf_fd(2, "Error: Failed to initialize message string %s\n",
                message.get_error_str());
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

int ft_calculate_spell_healing(int total_dice, int dice_faces, int extra_damage)
{
    int dice_roll_result = ft_perform_dice_roll(total_dice, dice_faces);
    if (dice_roll_result == -1)
        return (-1);
    return (dice_roll_result + extra_damage);
}

int ft_calculate_spell_damage(int total_dice, int dice_faces, int extra_damage)
{
    int dice_roll_result = ft_perform_dice_roll(total_dice, dice_faces);
    if (dice_roll_result == -1)
        return (-1);
    return (dice_roll_result + extra_damage);
}

static void ft_set_slot_used(t_spell_slot *spell_slot)
{
    if (!spell_slot->replenishing_slot)
        spell_slot->available--;
    return ;
}

void ft_remove_spell_slot(t_spell_slots *spell_slots, int level_spell_used)
{
    if (!(level_spell_used >= 1 && level_spell_used <= 9))
    {
        pf_printf_fd(2, "Error: Invalid spell slot level %d.\n", level_spell_used);
        return ;
    }

    if (level_spell_used == 1 && spell_slots->level_1.available > 0)
        ft_set_slot_used(&spell_slots->level_1);
    else if (level_spell_used == 2 && spell_slots->level_2.available > 0)
        ft_set_slot_used(&spell_slots->level_2);
    else if (level_spell_used == 3 && spell_slots->level_3.available > 0)
        ft_set_slot_used(&spell_slots->level_3);
    else if (level_spell_used == 4 && spell_slots->level_4.available > 0)
        ft_set_slot_used(&spell_slots->level_4);
    else if (level_spell_used == 5 && spell_slots->level_5.available > 0)
        ft_set_slot_used(&spell_slots->level_5);
    else if (level_spell_used == 6 && spell_slots->level_6.available > 0)
        ft_set_slot_used(&spell_slots->level_6);
    else if (level_spell_used == 7 && spell_slots->level_7.available > 0)
        ft_set_slot_used(&spell_slots->level_7);
    else if (level_spell_used == 8 && spell_slots->level_8.available > 0)
        ft_set_slot_used(&spell_slots->level_8);
    else if (level_spell_used == 9 && spell_slots->level_9.available > 0)
        ft_set_slot_used(&spell_slots->level_9);
    return ;
}
