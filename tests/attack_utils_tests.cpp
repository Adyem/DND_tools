#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../identification.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

static void test_weapon_find_stat_returns_strength_score()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    int             result;

    character.stats.str = 16;
    weapon.attack.stat = STAT_STR;
    result = ft_weapon_find_stat(&character, &weapon);
    test_assert_true(result == 16, "ft_weapon_find_stat should return character strength when weapon uses STR");
    return ;
}

static void test_weapon_find_stat_uses_highest_for_finesse()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    int             result;

    character.stats.str = 12;
    character.stats.dex = 18;
    weapon.attack.stat = FINESSE;
    result = ft_weapon_find_stat(&character, &weapon);
    test_assert_true(result == 18, "ft_weapon_find_stat should use the higher of STR or DEX for finesse weapons");
    return ;
}

static void test_weapon_find_stat_returns_zero_for_unknown_stat()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    int             result;

    weapon.attack.stat = "mystery";
    result = ft_weapon_find_stat(&character, &weapon);
    test_assert_true(result == 0, "ft_weapon_find_stat should return zero when the weapon stat tag is unknown");
    return ;
}

static void test_check_dice_amount_selects_secondary_for_offhand()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    t_damage_info   damage = {};

    weapon.slot = SLOT_OFFHAND_WEAPON;
    weapon.attack.effect_dice_amount = 3;
    weapon.attack.effect_dice_faces = 6;
    weapon.attack.effect_secund_dice_amount = 1;
    weapon.attack.effect_secund_dice_faces = 8;
    ft_check_dice_amount_and_faces(&weapon, &damage, 1, &character);
    test_assert_true(damage.dice_amount == 1, "ft_check_dice_amount_and_faces should use secondary dice amount for offhand attacks");
    test_assert_true(damage.dice_faces == 8, "ft_check_dice_amount_and_faces should use secondary dice faces for offhand attacks");
    return ;
}

static void test_check_dice_amount_keeps_primary_for_main_hand()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    t_damage_info   damage = {};

    weapon.slot = SLOT_WEAPON;
    weapon.attack.effect_dice_amount = 2;
    weapon.attack.effect_dice_faces = 10;
    weapon.attack.effect_secund_dice_amount = 5;
    weapon.attack.effect_secund_dice_faces = 12;
    ft_check_dice_amount_and_faces(&weapon, &damage, 0, &character);
    test_assert_true(damage.dice_amount == 2, "ft_check_dice_amount_and_faces should keep primary dice amount for main hand attacks");
    test_assert_true(damage.dice_faces == 10, "ft_check_dice_amount_and_faces should keep primary dice faces for main hand attacks");
    return ;
}

static void test_check_dice_amount_handles_two_weapon_setup()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    t_damage_info   damage = {};

    weapon.slot = SLOT_WEAPON;
    character.equipment.offhand_weapon.equipment_id = 42;
    weapon.attack.effect_dice_amount = 4;
    weapon.attack.effect_dice_faces = 6;
    weapon.attack.effect_secund_dice_amount = 7;
    weapon.attack.effect_secund_dice_faces = 8;
    ft_check_dice_amount_and_faces(&weapon, &damage, 0, &character);
    test_assert_true(damage.dice_amount == 4, "ft_check_dice_amount_and_faces should use primary dice when offhand weapon is equipped");
    test_assert_true(damage.dice_faces == 6, "ft_check_dice_amount_and_faces should keep primary faces when offhand weapon is equipped");
    return ;
}

static void test_calculate_damage_applies_growth_reduction()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    t_damage_info   damage = {};
    const char      *file_path;
    ft_string       output;
    const char      *expected_output;

    character.bufs.growth.stacks = 3;
    weapon.attack.damage_type = DAMAGE_TYPE_FIRE;
    damage.stat_mod = 10;
    damage.dice_amount = 0;
    damage.dice_faces = 0;
    file_path = "tests_output/attack_utils_growth.log";
    expected_output = "growth reduces damage by 3\n"
        "deals 7 fire damage\n";
    test_begin_output_capture(file_path);
    ft_calculate_damage(&character, &weapon, &damage, false);
    test_end_output_capture();
    test_assert_true(damage.damage == 7, "ft_calculate_damage should subtract growth stacks from total damage");
    output = test_read_file_to_string(file_path);
    test_assert_true(output == expected_output,
        "ft_calculate_damage should log growth reduction and resulting damage");
    test_delete_file(file_path);
    return ;
}

static void test_calculate_damage_never_drops_below_zero()
{
    t_char          character = {};
    t_equipment_id  weapon = {};
    t_damage_info   damage = {};
    const char      *file_path;
    ft_string       output;
    const char      *expected_output;

    character.bufs.growth.stacks = 20;
    weapon.attack.damage_type = DAMAGE_TYPE_SLASHING;
    damage.stat_mod = 5;
    damage.dice_amount = 0;
    damage.dice_faces = 0;
    file_path = "tests_output/attack_utils_floor.log";
    expected_output = "growth reduces damage by 20\n"
        "deals 0 slashing damage\n";
    test_begin_output_capture(file_path);
    ft_calculate_damage(&character, &weapon, &damage, false);
    test_end_output_capture();
    test_assert_true(damage.damage == 0, "ft_calculate_damage should floor total damage at zero after reductions");
    output = test_read_file_to_string(file_path);
    test_assert_true(output == expected_output,
        "ft_calculate_damage should report growth reduction and floored damage");
    test_delete_file(file_path);
    return ;
}

void    run_attack_utils_tests()
{
    test_begin_suite("attack_utils_tests");
    test_weapon_find_stat_returns_strength_score();
    test_weapon_find_stat_uses_highest_for_finesse();
    test_weapon_find_stat_returns_zero_for_unknown_stat();
    test_check_dice_amount_selects_secondary_for_offhand();
    test_check_dice_amount_keeps_primary_for_main_hand();
    test_check_dice_amount_handles_two_weapon_setup();
    test_calculate_damage_applies_growth_reduction();
    test_calculate_damage_never_drops_below_zero();
    test_end_suite_success();
    return ;
}
