#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"

static void test_divine_smite_upcast_adds_extra_dice()
{
    t_spell_divine_smite divine_smite;
    int base_damage;
    int upcast_damage;

    divine_smite.learned = 1;
    divine_smite.base_level = 1;
    divine_smite.casting_at_level = 0;
    divine_smite.dice_amount = 2;
    divine_smite.dice_faces = 1;
    divine_smite.extra_damage = 0;
    divine_smite.upcast_extra_dice_face = 0;
    divine_smite.upcast_extra_dice_amount = 1;
    divine_smite.upcast_extra_damage = 0;

    base_damage = ft_divine_smite_damage_roll(&divine_smite, 1, false);
    upcast_damage = ft_divine_smite_damage_roll(&divine_smite, 2, false);
    test_assert_true(base_damage == 2,
            "Base damage should equal the number of dice when faces are one");
    test_assert_true(upcast_damage == 3,
            "Upcast damage should add one die when cast above base level");
    test_assert_true(upcast_damage > base_damage,
            "Upcast damage should be greater than base damage");
    return ;
}

static void test_divine_smite_critical_upcast_doubles_dice()
{
    t_spell_divine_smite divine_smite;
    int normal_damage;
    int critical_damage;

    divine_smite.learned = 1;
    divine_smite.base_level = 1;
    divine_smite.casting_at_level = 0;
    divine_smite.dice_amount = 2;
    divine_smite.dice_faces = 1;
    divine_smite.extra_damage = 1;
    divine_smite.upcast_extra_dice_face = 0;
    divine_smite.upcast_extra_dice_amount = 1;
    divine_smite.upcast_extra_damage = 2;

    normal_damage = ft_divine_smite_damage_roll(&divine_smite, 3, false);
    critical_damage = ft_divine_smite_damage_roll(&divine_smite, 3, true);
    test_assert_true(normal_damage == 9,
            "Casting two levels above base should add upcast bonuses before critical");
    test_assert_true(critical_damage == 13,
            "Critical upcast should double dice while keeping extra damage additions");
    test_assert_true(critical_damage > normal_damage,
            "Critical damage should exceed non-critical damage for the same cast level");
    return ;
}

static void test_divine_smite_does_not_reduce_damage_when_cast_lower()
{
    t_spell_divine_smite divine_smite;
    int base_damage;
    int lower_level_damage;

    divine_smite.learned = 1;
    divine_smite.base_level = 3;
    divine_smite.casting_at_level = 0;
    divine_smite.dice_amount = 2;
    divine_smite.dice_faces = 1;
    divine_smite.extra_damage = 0;
    divine_smite.upcast_extra_dice_face = 5;
    divine_smite.upcast_extra_dice_amount = 7;
    divine_smite.upcast_extra_damage = 11;

    base_damage = ft_divine_smite_damage_roll(&divine_smite, 3, false);
    lower_level_damage = ft_divine_smite_damage_roll(&divine_smite, 1, false);
    test_assert_true(base_damage == 2,
            "Base damage should remain unchanged when no upcast is applied");
    test_assert_true(lower_level_damage == base_damage,
            "Casting below the base level should not apply negative upcast bonuses");
    return ;
}

void run_divine_smite_tests()
{
    test_divine_smite_upcast_adds_extra_dice();
    test_divine_smite_critical_upcast_doubles_dice();
    test_divine_smite_does_not_reduce_damage_when_cast_lower();
    return ;
}
