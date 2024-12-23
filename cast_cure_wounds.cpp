#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"

static int ft_check_cure_wounds_learned(ft_sharedptr<t_char> &character)
{
    if (character->spells.cure_wounds.learned == 0)
    {
        pf_printf_fd(2, "%s hasn't learned Cure Wounds\n", character->name);
        return (0);
    }
    return (1);
}

void ft_cast_cure_wounds(ft_sharedptr<t_char> &character)
{
    if (!ft_check_cure_wounds_learned(character))
        return ;
    int base_level = character->spells.cure_wounds.base_level;
    int cast_at_level = ft_prompt_spell_level(character, base_level);
    if (cast_at_level == -1)
        return ;
    t_spell_cure_wounds *cure_wounds = &character->spells.cure_wounds;
    int upcast_level = cast_at_level - base_level;
    if (upcast_level < 0)
    {
        pf_printf_fd(2, "Error: Cast level cannot be lower than base level for Cure Wounds.\n");
        return ;
    }
    int total_dice = cure_wounds->dice_amount
                  + (cure_wounds->upcast_extra_dice_amount * upcast_level);
    int dice_faces = cure_wounds->dice_faces
                  + (cure_wounds->upcast_extra_dice_face * upcast_level);
    int extra_healing = cure_wounds->extra_healing
                      + (cure_wounds->upcast_extra_healing * upcast_level);
    int healing = ft_calculate_spell_healing(total_dice, dice_faces, extra_healing);
    if (healing == -1)
    {
        pf_printf_fd(2, "Error: Failed to calculate healing for Cure Wounds.\n");
        return ;
    }
    pf_printf("%s cast Cure Wounds at level %i and healed %i HP\n",
              character->name, cast_at_level, healing);
    ft_remove_spell_slot(&character->spell_slots, cast_at_level);
	return ;
}
