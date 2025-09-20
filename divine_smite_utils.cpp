#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/rng.hpp"

int ft_divine_smite_damage_roll(t_spell_divine_smite *divine_smite,
        int cast_at_level, bool critical_strike)
{
    int multiplyer = 1;
    int upcast_level = cast_at_level - divine_smite->base_level;
    int total_dice;
    int dice_faces;
    int extra_damage;
    int dice_roll_result;

    if (critical_strike)
        multiplyer = 2;
    if (upcast_level < 0)
        upcast_level = 0;
    total_dice = (divine_smite->dice_amount
            + (divine_smite->upcast_extra_dice_amount * upcast_level)) * multiplyer;
    dice_faces = divine_smite->dice_faces
                    + (divine_smite->upcast_extra_dice_face * upcast_level);
    extra_damage = divine_smite->extra_damage
                    + (divine_smite->upcast_extra_damage * upcast_level);
    dice_roll_result = ft_dice_roll(total_dice, dice_faces);
    if (dice_roll_result == -1)
    {
        pf_printf_fd(2, "Error: Dice roll failed.\n");
        return (-1);
    }
    return (dice_roll_result + extra_damage);
}
