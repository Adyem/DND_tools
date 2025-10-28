#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/rng.hpp"
#include "libft/Template/vector.hpp"

static int ft_append_spell_slot_reference(ft_vector<t_spell_slot*> &slots,
        t_spell_slot *spell_slot)
{
    slots.push_back(spell_slot);
    if (slots.get_error() != ER_SUCCESS)
    {
        ft_errno = slots.get_error();
        return (-1);
    }
    return (0);
}

static int ft_collect_spell_slots(t_spell_slots *spell_slots,
        ft_vector<t_spell_slot*> &slots)
{
    if (spell_slots == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-1);
    }
    slots.clear();
    if (slots.get_error() != ER_SUCCESS)
    {
        ft_errno = slots.get_error();
        return (-1);
    }
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_1) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_2) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_3) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_4) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_5) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_6) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_7) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_8) != 0)
        return (-1);
    if (ft_append_spell_slot_reference(slots, &spell_slots->level_9) != 0)
        return (-1);
    ft_errno = ER_SUCCESS;
    return (0);
}

static int ft_get_collected_slot(ft_vector<t_spell_slot*> &slots,
        size_t slot_count,
        size_t index,
        t_spell_slot **out_slot)
{
    if (out_slot == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-1);
    }
    if (index >= slot_count)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-1);
    }
    *out_slot = slots[index];
    if (slots.get_error() != ER_SUCCESS)
    {
        ft_errno = slots.get_error();
        return (-1);
    }
    ft_errno = ER_SUCCESS;
    return (0);
}

static int ft_auto_cast(t_char *character, int base_level, const char *spell_name)
{
    int current_level;
    ft_vector<t_spell_slot*> spell_slots(9);
    size_t slot_count;
    t_spell_slot *spell_slot;

    current_level = base_level;
    if (ft_collect_spell_slots(&character->spell_slots, spell_slots) != 0)
        return (-1);
    slot_count = spell_slots.size();
    if (spell_slots.get_error() != ER_SUCCESS)
    {
        ft_errno = spell_slots.get_error();
        return (-1);
    }
    if (current_level < 1)
        current_level = 1;
    while (current_level <= 9)
    {
        size_t slot_index;

        slot_index = static_cast<size_t>(current_level - 1);
        if (slot_index >= slot_count)
            break;
        if (ft_get_collected_slot(spell_slots, slot_count, slot_index,
                &spell_slot) != 0)
            return (-1);
        if (spell_slot != ft_nullptr && spell_slot->available > 0)
        {
            ft_errno = ER_SUCCESS;
            return (current_level);
        }
        current_level++;
    }
    pf_printf_fd(2, "Error: No available spell slots for %s to cast %s.\n",
            character->name, spell_name);
    return (-1);
}

static ft_string ft_check_availeble_spell_slots(t_char *character, int base_level)
{
    ft_string available_levels;
    ft_vector<t_spell_slot*> spell_slots(9);
    size_t slot_count;
    size_t index;

    if (ft_collect_spell_slots(&character->spell_slots, spell_slots) != 0)
        return (ft_string(ft_errno));
    slot_count = spell_slots.size();
    if (spell_slots.get_error() != ER_SUCCESS)
    {
        ft_errno = spell_slots.get_error();
        return (ft_string(ft_errno));
    }
    index = 0;
    while (index < slot_count)
    {
        int level_value;
        t_spell_slot *spell_slot;
        char *level_string;

        level_value = static_cast<int>(index + 1);
        if (base_level >= level_value)
        {
            if (ft_get_collected_slot(spell_slots, slot_count, index,
                    &spell_slot) != 0)
                return (ft_string(ft_errno));
            if (spell_slot != ft_nullptr && spell_slot->available > 0)
            {
                available_levels.append(" ");
                if (available_levels.get_error() != ER_SUCCESS)
                    return (ft_string(available_levels.get_error()));
                level_string = cma_itoa(level_value);
                if (level_string == ft_nullptr)
                    return (ft_string(ft_errno));
                available_levels.append(level_string);
                if (available_levels.get_error() != ER_SUCCESS)
                {
                    cma_free(level_string);
                    return (ft_string(available_levels.get_error()));
                }
                cma_free(level_string);
                available_levels.append(",");
                if (available_levels.get_error() != ER_SUCCESS)
                    return (ft_string(available_levels.get_error()));
            }
        }
        index++;
    }
    if (!available_levels.empty())
    {
        available_levels.erase(available_levels.size() - 1, 1);
        if (available_levels.get_error() != ER_SUCCESS)
            return (ft_string(available_levels.get_error()));
    }
    ft_errno = ER_SUCCESS;
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
    ft_vector<t_spell_slot*> spell_slots_vector(9);
    size_t slot_count;
    size_t slot_index;
    t_spell_slot *spell_slot;

    if (!(level_spell_used >= 1 && level_spell_used <= 9))
    {
        pf_printf_fd(2, "Error: Invalid spell slot level %d.\n", level_spell_used);
        return ;
    }

    if (ft_collect_spell_slots(spell_slots, spell_slots_vector) != 0)
    {
        pf_printf_fd(2,
            "Error: Failed to access spell slots for level %d.\n",
            level_spell_used);
        return ;
    }
    slot_count = spell_slots_vector.size();
    if (spell_slots_vector.get_error() != ER_SUCCESS)
    {
        pf_printf_fd(2,
            "Error: Failed to access spell slots for level %d.\n",
            level_spell_used);
        return ;
    }
    slot_index = static_cast<size_t>(level_spell_used - 1);
    if (ft_get_collected_slot(spell_slots_vector, slot_count, slot_index,
            &spell_slot) != 0)
    {
        pf_printf_fd(2,
            "Error: Failed to access spell slots for level %d.\n",
            level_spell_used);
        return ;
    }
    if (spell_slot != ft_nullptr && spell_slot->available > 0)
        ft_set_slot_used(spell_slot);
    return ;
}
