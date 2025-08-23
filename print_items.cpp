#include "dnd_tools.hpp"
#include "melee_weapons.hpp"
#include "libft/Printf/printf.hpp"

void print_weapon_info(const t_equipment_id *weapon)
{
    pf_printf("%s:\n", weapon->name);
    pf_printf("  %dd%d %s damage (one hand)\n",
              weapon->attack.effect_dice_amount,
              weapon->attack.effect_dice_faces,
              weapon->attack.damage_type);
    if (weapon->attack.effect_secund_dice_amount &&
        weapon->attack.effect_secund_dice_faces)
    {
        pf_printf("  %dd%d %s damage (two hands)\n",
                  weapon->attack.effect_secund_dice_amount,
                  weapon->attack.effect_secund_dice_faces,
                  weapon->attack.damage_type);
    }
    pf_printf("  Uses %s for attack rolls\n", weapon->attack.stat);
    return ;
}

void print_basic_weapons(void)
{
    print_weapon_info(&STEEL_SWORD);
    print_weapon_info(&STEEL_BATTLE_AXE);
    print_weapon_info(&LONGSWORD);
    return ;
}
