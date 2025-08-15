#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"

static int ft_check_lightning_bolt_learned(t_char * character)
{
    if (character->spells.lightning_bolt.learned == 0)
    {
        pf_printf_fd(2, "%s hasn't learned Lightning Bolt\n", character->name);
        return (0);
    }
    return (1);
}

void ft_cast_lightning_bolt(t_char * character)
{
    if (!ft_check_lightning_bolt_learned(character))
        return ;
    int base_level = character->spells.lightning_bolt.base_level;
    int cast_at_level = ft_prompt_spell_level(character, base_level, "Lightning Bolt");
    if (cast_at_level == -1)
        return ;
    t_spell_lightning_bolt *lightning_bolt = &character->spells.lightning_bolt;
    int upcast_level = cast_at_level - base_level;
    if (upcast_level < 0)
    {
        pf_printf_fd(2, "Error: Cast level cannot be lower than base level for Lightning Bolt.\n");
        return ;
    }
    int total_dice = lightning_bolt->dice_amount
                  + (lightning_bolt->upcast_extra_dice_amount * upcast_level);
    int dice_faces = lightning_bolt->dice_faces
                  + (lightning_bolt->upcast_extra_dice_face * upcast_level);
    int extra_damage = lightning_bolt->extra_damage
                      + (lightning_bolt->upcast_extra_damage * upcast_level);
    int damage = ft_calculate_spell_damage(total_dice, dice_faces, extra_damage);
    if (damage == -1)
    {
        pf_printf_fd(2, "Error: Failed to calculate damage for Lightning Bolt.\n");
        return ;
    }
    pf_printf("%s cast Lightning Bolt at level %i and dealt %i %s damage\n",
              character->name, cast_at_level, damage, DAMAGE_TYPE_LIGHTNING);
    ft_remove_spell_slot(&character->spell_slots, cast_at_level);
	return ;
}
