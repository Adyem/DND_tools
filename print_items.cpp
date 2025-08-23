#include "dnd_tools.hpp"
#include "melee_weapons.hpp"
#include "ranged_weapons.hpp"
#include "armor.hpp"
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

void print_steel_sword(void)
{
    print_weapon_info(&STEEL_SWORD);
    return ;
}

void print_steel_battle_axe(void)
{
    print_weapon_info(&STEEL_BATTLE_AXE);
    return ;
}

void print_longsword(void)
{
    print_weapon_info(&LONGSWORD);
    return ;
}

void print_wooden_club(void)
{
    print_weapon_info(&WOODEN_CLUB);
    return ;
}

void print_claw(void)
{
    print_weapon_info(&CLAW);
    return ;
}

void print_felbeast_claw(void)
{
    print_weapon_info(&FELBEAST_CLAW);
    pf_printf("  On hit: target must succeed on a DC15 constitution save "
              "or take %dd%d+%d poison damage and suffer disadvantage on "
              "attacks for 2 turns.\n",
              FELBEAST_CLAW.action_01.effect_dice_amount,
              FELBEAST_CLAW.action_01.effect_dice_faces,
              FELBEAST_CLAW.action_01.bonus_mod);
    return ;
}

void print_ancient_predatory_beast_claw(void)
{
    print_weapon_info(&ANCIENT_PREDATORY_BEAST_CLAW);
    pf_printf("  Attacking with this weapon triggers two additional claw attacks.\n");
    return ;
}

void print_shadow_claw(void)
{
    print_weapon_info(&SHADOW_CLAW);
    pf_printf("  On hit: target's armor class is reduced by %d for %d turns.\n",
              SHADOW_CLAW.action_01.bonus_mod,
              SHADOW_CLAW.action_01.effect_dice_faces);
    return ;
}

void print_claw_oh(void)
{
    print_weapon_info(&CLAW_OH);
    return ;
}

void print_ghostly_sword(void)
{
    print_weapon_info(&GHOSTLY_SWORD);
    return ;
}

void print_felbeast_claw_oh(void)
{
    print_weapon_info(&FELBEAST_CLAW_OH);
    pf_printf("  On hit: target must succeed on a DC15 constitution save "
              "or take %dd%d+%d poison damage and suffer disadvantage on "
              "attacks for 2 turns.\n",
              FELBEAST_CLAW_OH.action_01.effect_dice_amount,
              FELBEAST_CLAW_OH.action_01.effect_dice_faces,
              FELBEAST_CLAW_OH.action_01.bonus_mod);
    return ;
}

void print_nightmare_claw(void)
{
    print_weapon_info(&NIGHTMARE_CLAW);
    pf_printf("  On hit: target must succeed on a DC20 charisma save or "
              "become frightened and have disadvantage on their next "
              "turn.\n");
    return ;
}

void print_wooden_staff(void)
{
    print_weapon_info(&WOODEN_STAFF);
    return ;
}

void print_felguard_posioned_axe(void)
{
    print_weapon_info(&FELGUARD_POSIONED_AXE);
    pf_printf("  On hit: target must succeed on a DC15 constitution save "
              "or take %dd%d+%d poison damage and suffer disadvantage on "
              "attacks for 2 turns.\n",
              FELGUARD_POSIONED_AXE.action_01.effect_dice_amount,
              FELGUARD_POSIONED_AXE.action_01.effect_dice_faces,
              FELGUARD_POSIONED_AXE.action_01.bonus_mod);
    return ;
}

void print_mithril_axe(void)
{
    print_weapon_info(&MITHRIL_AXE);
    return ;
}

void print_mannoroth_glaive(void)
{
    print_weapon_info(&MANNOROTH_GLAIVE);
    return ;
}

void print_wooden_bow(void)
{
    print_weapon_info(&WOODEN_BOW);
    return ;
}

void print_chaos_wand(void)
{
    print_weapon_info(&CHAOS_WAND);
    return ;
}

void print_wand_of_draining(void)
{
    print_weapon_info(&WAND_OF_DRAINING);
    pf_printf("  On hit: target temporarily loses %d Strength and must succeed on a DC%d "
              "Strength save or fall unconscious. Strength cannot drop below 1.\n",
              WAND_OF_DRAINING.action_01.bonus_mod,
              WAND_OF_DRAINING.action_01.effect_dice_amount);
    return ;
}

void print_shadow_wand(void)
{
    print_weapon_info(&SHADOW_WAND);
    return ;
}

void print_snowball_wand(void)
{
    print_weapon_info(&SNOWBALL_WAND);
    pf_printf("  On hit: target's speed is reduced by %d feet (%d on a critical hit).\n",
              SNOWBALL_WAND.action_01.bonus_mod,
              SNOWBALL_WAND.action_01.bonus_mod * 2);
    return ;
}

void print_basic_weapons(void)
{
    print_steel_sword();
    print_steel_battle_axe();
    print_longsword();
    print_wooden_club();
    print_claw();
    return ;
}

void print_basic_ranged_weapons(void)
{
    print_wooden_bow();
    return ;
}

void print_armor_info(const t_equipment_id *armor)
{
    pf_printf("%s:\n", armor->name);
    pf_printf("  AC: %d\n", armor->ac);
    if (armor->dex_ac_max_bonus)
        pf_printf("  Max dex bonus: %d\n", armor->dex_ac_max_bonus);
    if (armor->str || armor->dex || armor->con ||
        armor->inte || armor->wis || armor->cha)
    {
        pf_printf("  Stat bonuses:");
        if (armor->str)
            pf_printf(" STR %+d", armor->str);
        if (armor->dex)
            pf_printf(" DEX %+d", armor->dex);
        if (armor->con)
            pf_printf(" CON %+d", armor->con);
        if (armor->inte)
            pf_printf(" INT %+d", armor->inte);
        if (armor->wis)
            pf_printf(" WIS %+d", armor->wis);
        if (armor->cha)
            pf_printf(" CHA %+d", armor->cha);
        pf_printf("\n");
    }
    return ;
}

void print_leather_armor(void)
{
    print_armor_info(&LEATHER_ARMOR);
    return ;
}

void print_wolf_pelt(void)
{
    print_armor_info(&WOLF_PELT);
    return ;
}

void print_ghost_armor(void)
{
    print_armor_info(&GHOST_ARMOR);
    pf_printf("  Provides resistance to necrotic damage and 50%% resistance to "
              "bludgeoning, piercing, and slashing damage.\n");
    return ;
}

void print_steel_armor(void)
{
    print_armor_info(&STEEL_ARMOR);
    return ;
}

void print_felbeast_hide(void)
{
    print_armor_info(&FELBEAST_HIDE);
    pf_printf("  Grants 50%% resistance to piercing and slashing damage.\n");
    return ;
}

void print_ancient_predatory_beast_hide(void)
{
    print_armor_info(&ANCIENT_REDATORY_BEAST_HIDE);
    pf_printf("  Grants 50%% resistance to bludgeoning, piercing, and slashing "
              "damage.\n");
    return ;
}

void print_magic_steel_armor(void)
{
    print_armor_info(&MAGIC_STEEL_ARMOR);
    pf_printf("  Grants +2 to Strength, Dexterity, and Constitution.\n");
    return ;
}

void print_felguard_plate_armor(void)
{
    print_armor_info(&FELGUARD_PLATE_ARMOR);
    return ;
}

void print_mannoroth_plate_armor(void)
{
    print_armor_info(&MANNOROTH_PLATE_ARMOR);
    return ;
}

void print_xavius_mage_armor(void)
{
    print_armor_info(&XAVIUS_MAGE_ARMOR);
    return ;
}

void print_basic_armors(void)
{
    print_leather_armor();
    print_steel_armor();
    return ;
}
