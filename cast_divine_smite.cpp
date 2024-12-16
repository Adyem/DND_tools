#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/shared_ptr.hpp"

static int ft_check_divine_smite_learned(ft_sharedptr<t_char> &character)
{
    if (character->spells.divine_smite.learned == 0)
    {
        pf_printf_fd(2, "%s hasn't learned Divine Smite\n", character->name);
        return (0);
    }
    return (1);
}

void ft_cast_divine_smite(ft_sharedptr<t_char> &character)
{
	if (!ft_check_divine_smite_learned(character))
		return ;
    int base_level = character->spells.divine_smite.base_level;
	int cast_at_level = ft_prompt_spell_level(character, base_level);
    if (cast_at_level == -1)
        return ;
    t_divine_smite *divine_smite = &character->spells.divine_smite;
	int upcast_level = base_level - cast_at_level;
    int total_dice = divine_smite->dice_amount
                	+ (divine_smite->upcast_extra_dice_amount * upcast_level);
    int dice_faces = divine_smite->dice_faces
                    + (divine_smite->upcast_extra_dice_face * upcast_level);
    int extra_damage = divine_smite->extra_damage
                    + (divine_smite->upcast_extra_damage * upcast_level);
    int damage = ft_calculate_spell_damage(total_dice, dice_faces, extra_damage);
    if (damage == -1)
    {
        pf_printf_fd(2, "Error: Failed to calculate damage for Divine Smite.\n");
        return ;
    }
    pf_printf("%s cast Divine Smite at level %i and dealt %i %s damage\n",
            character->name, cast_at_level, damage, DAMAGE_TYPE_RADIANT);
	ft_remove_spell_slot(&character->spell_slots, cast_at_level);
    return ;
}
