#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/dice_roll.hpp"
#include "libft/CPP_class/nullptr.hpp"

static char *ft_fel_poison_attack_effect_construct_message(t_char *info)
{
    char *string_constitution = cma_itoa(ft_calculate_dex(info));
    if (!string_constitution)
    {
        pf_printf_fd(2, "148-Error: Allocation failure %s poison effect\n", info->name);
        return (ft_nullptr);
    }
    char *prefix = cma_strdup("the target needs to succeed on a DC15");
    if (!prefix)
    {
        pf_printf_fd(2, "149-Error: Allocation failure %s poison effect\n", info->name);
        cma_free(string_constitution);
        return (ft_nullptr);
    }
    char *temp = cma_strjoin(prefix, string_constitution);
    cma_free(prefix);
    if (!temp)
    {
        pf_printf_fd(2, "150-Error: Allocation failure %s poison effect\n", info->name);
        cma_free(string_constitution);
        return (ft_nullptr);
    }
    char *message = cma_strjoin(temp, " constitution save or become poisoned");
    cma_free(temp);
    cma_free(string_constitution);
    if (!message)
    {
        pf_printf_fd(2, "151-Error: Allocation failure %s poison effect\n", info->name);
        return (ft_nullptr);
    }
    return (message);
}

void ft_fel_poison_attack_effects(t_char *info, t_equipment_id *weapon, t_equipment_effect *effect,
		t_attack_info *attack_info)
{
	(void)effect;
	if (!attack_info->is_hit)
		return ;
    char *message = ft_fel_poison_attack_effect_construct_message(info);
    if (!message)
        return ;
    if (ft_readline_confirm(message))
    {
        int result = ft_dice_roll(weapon->action_01.effect_dice_amount,
                weapon->action_01.effect_dice_faces) + weapon->action_01.bonus_mod;
        pf_printf("The target is poisoned by fell poison, taking %i damage and "
                  "suffering disadvantage on their attacks for the next 2 turns.", result);
    }
    cma_free(message);
    return ;
}
