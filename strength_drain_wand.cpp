#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "identification.hpp"
#include "libft/RNG/RNG.hpp"

void ft_strength_drain(t_char *info, t_equipment_id *weapon,
        t_equipment_effect *effect, t_attack_info *attack_info)
{
    (void)weapon;
    (void)effect;
    (void)info;
    if (weapon->equipment_id != WAND_OF_DRAINING_ID)
        return ;
    if (attack_info->is_hit)
    {
        int point_to_drain = weapon->action_01.bonus_mod
            + ft_dice_roll(weapon->action_01.effect_dice_faces,
                    weapon->action_01.effect_dice_amount);
        pf_printf("If this attack hits, the target temporarily loses %i Strength. " \
                "They must then make a Strength saving throw (DC %i). On a failure, " \
                "they fall unconscious. If this reduction would bring their Strength " \
                "to 1 or lower, it is set to 1 and the saving throw automatically " \
                "fails.\n", point_to_drain, weapon->action_01.effect_dice_amount);
    }
    return ;
}
