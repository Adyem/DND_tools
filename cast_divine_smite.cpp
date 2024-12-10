#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/CPP_class/string.hpp"
#include "libft/Printf/printf.hpp"

static int ft_check_divine_smite_learned(t_char *character)
{
    if (character->spells.divine_smite.learned == 0)
    {
        pf_printf_fd(2, "%s hasn't learned Divine Smite\n", character->name);
        return (0);
    }
    return (1);
}

void ft_cast_divine_smite(t_char *character)
{
    if (!ft_check_divine_smite_learned(character))
        return;
    ft_string available_slots = ft_get_available_spell_slots(character);
    if (available_slots.empty())
    {
        pf_printf_fd(2, "Error: No available spell slots for %s to cast Divine Smite.\n",
                character->name);
        return;
    }
    if (available_slots.getError())
    {
        pf_printf_fd(2, "Error: Failed to retrieve available spell slots for %s.\n",
                character->name);
        return;
    }
    int base_level = character->spells.divine_smite.base_level;
    int level = ft_prompt_spell_level(character, &available_slots, base_level);
    if (level == -1)
        return;
    t_divine_smite *divine_smite = &character->spells.divine_smite;
    int total_dice = divine_smite->dice_amount
                     + divine_smite->upcast_extra_dice_amount * level
                     - divine_smite->upcast_extra_dice_amount;

    int dice_faces = divine_smite->upcast_extra_dice_face
                     * (level - divine_smite->base_level)
                     - divine_smite->upcast_extra_dice_amount;

    int extra_damage = divine_smite->upcast_extra_damage
                       * (level - divine_smite->base_level)
                       - divine_smite->upcast_extra_damage;

    int damage = ft_calculate_spell_damage(total_dice, dice_faces, extra_damage);
    if (damage == -1)
    {
        pf_printf_fd(2, "Error: Failed to calculate damage for Divine Smite.\n");
        return;
    }

    pf_printf("%s cast Divine Smite at level %i and dealt %i %s damage\n",
            character->name, level, damage, DAMAGE_TYPE_RADIANT);
    return;
}
