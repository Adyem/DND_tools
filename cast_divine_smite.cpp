#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"

static int ft_check_divine_smite_learned(t_char * character)
{
    if (character->spells.divine_smite.learned == 0)
    {
        pf_printf_fd(2, "%s hasn't learned Divine Smite\n", character->name);
        return (0);
    }
    return (1);
}

void ft_cast_divine_smite(t_char * character, bool critical_strike)
{
    if (!ft_check_divine_smite_learned(character))
        return ;
    int base_level = character->spells.divine_smite.base_level;
    int cast_at_level = ft_prompt_spell_level(character, base_level, "Divine Smite");
    if (cast_at_level == -1)
        return ;
    t_spell_divine_smite *divine_smite = &character->spells.divine_smite;
    int damage = ft_divine_smite_damage_roll(divine_smite, cast_at_level,
            critical_strike);
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
