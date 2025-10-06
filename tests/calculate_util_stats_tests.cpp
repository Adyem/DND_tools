#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"

static void test_calculate_crit_attack_fail_bonus_sums_all_slots()
{
    t_char  character = {};
    int     result;

    character.crit.attack_fail = 1;
    character.equipment.weapon.crit_attack_fail_bonus = 2;
    character.equipment.offhand_weapon.crit_attack_fail_bonus = 3;
    character.equipment.ranged_weapon.crit_attack_fail_bonus = 4;
    character.equipment.armor.crit_attack_fail_bonus = 5;
    character.equipment.helmet.crit_attack_fail_bonus = 6;
    character.equipment.shield.crit_attack_fail_bonus = 7;
    character.equipment.boots.crit_attack_fail_bonus = 8;
    character.equipment.gloves.crit_attack_fail_bonus = 9;
    character.equipment.amulet.crit_attack_fail_bonus = 10;
    character.equipment.ring_01.crit_attack_fail_bonus = 11;
    character.equipment.ring_02.crit_attack_fail_bonus = 12;
    character.equipment.belt.crit_attack_fail_bonus = 13;
    result = ft_calculate_crit_attack_fail_bonus(&character);
    test_assert_true(result == 91, "ft_calculate_crit_attack_fail_bonus should total base and equipment bonuses");
    return ;
}

static void test_calculate_crit_attack_success_bonus_handles_negatives()
{
    t_char  character = {};
    int     result;

    character.crit.attack = 5;
    character.equipment.weapon.crit_attack_succes_bonus = -1;
    character.equipment.shield.crit_attack_succes_bonus = 2;
    character.equipment.boots.crit_attack_succes_bonus = 3;
    result = ft_calculate_crit_attack_success_bonus(&character);
    test_assert_true(result == 9, "ft_calculate_crit_attack_success_bonus should add positive and negative modifiers");
    return ;
}

static void test_calculate_crit_attack_success_bonus_defaults_to_zero()
{
    t_char  character = {};
    int     result;

    result = ft_calculate_crit_attack_success_bonus(&character);
    test_assert_true(result == 0, "ft_calculate_crit_attack_success_bonus should be zero with no modifiers");
    return ;
}

static void test_calculate_crit_attack_fail_bonus_handles_negative_modifiers()
{
    t_char  character = {};
    int     result;

    character.crit.attack_fail = 2;
    character.equipment.weapon.crit_attack_fail_bonus = -1;
    character.equipment.shield.crit_attack_fail_bonus = -2;
    result = ft_calculate_crit_attack_fail_bonus(&character);
    test_assert_true(result == -1, "ft_calculate_crit_attack_fail_bonus should add negative equipment modifiers");
    return ;
}

static void test_calculate_crit_attack_success_bonus_includes_belt_slot()
{
    t_char  character = {};
    int     result;

    character.equipment.belt.crit_attack_succes_bonus = 4;
    result = ft_calculate_crit_attack_success_bonus(&character);
    test_assert_true(result == 4, "ft_calculate_crit_attack_success_bonus should include belt contributions");
    return ;
}

void run_calculate_util_stats_tests()
{
    test_begin_suite("calculate_util_stats_tests");
    test_calculate_crit_attack_fail_bonus_sums_all_slots();
    test_calculate_crit_attack_success_bonus_handles_negatives();
    test_calculate_crit_attack_success_bonus_defaults_to_zero();
    test_calculate_crit_attack_fail_bonus_handles_negative_modifiers();
    test_calculate_crit_attack_success_bonus_includes_belt_slot();
    test_end_suite_success();
    return ;
}
