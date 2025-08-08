#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/RNG.hpp"

void ft_fel_poison_attack_effects(t_char *info, t_equipment_id *weapon, t_equipment_effect *effect,
		t_attack_info *attack_info)
{
	(void)info;
	(void)effect;
	if (!attack_info->is_hit)
		return ;
    const char *message =
        "the target needs to succeed on a DC15 constitution save or become poisoned.\n"
        "Enter \"crit succes\", \"succes\", \"fail\" or \"crit fail\": ";
    if (!message)
        return ;
    int result_check = ft_readline_check_succes_or_fail(message);
    if (result_check == RL_FAIL || result_check == RL_CRIT_FAIL)
    {
        int result = ft_dice_roll(weapon->action_01.effect_dice_amount,
                weapon->action_01.effect_dice_faces) + weapon->action_01.bonus_mod;
        pf_printf("The target is poisoned by fell poison, taking %i damage and "
                  "suffering disadvantage on their attacks for the next 2 turns.", result);
    }
    return ;
}
