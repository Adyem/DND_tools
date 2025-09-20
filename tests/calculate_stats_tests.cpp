#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"

static void test_ability_mod_returns_zero_for_average_score()
{
    int result;

    result = ft_ability_mod(10);
    test_assert_true(result == 0, "ft_ability_mod should return zero for score of ten");
    return ;
}

static void test_ability_mod_rounds_down_positive_scores()
{
    int result;

    result = ft_ability_mod(15);
    test_assert_true(result == 2, "ft_ability_mod should round down positive modifiers");
    return ;
}

static void test_ability_mod_handles_negative_scores()
{
    int result;

    result = ft_ability_mod(7);
    test_assert_true(result == -2, "ft_ability_mod should bias toward negative on odd scores below ten");
    return ;
}

static void test_ability_mod_handles_minimum_score()
{
    int result;

    result = ft_ability_mod(1);
    test_assert_true(result == -5, "ft_ability_mod should return minus five for score of one");
    return ;
}

static void test_calculate_str_includes_equipment_bonus()
{
    t_char  character = {};
    int     result;

    character.stats.str = 12;
    character.equipment.weapon.str = 1;
    character.equipment.shield.str = 2;
    character.equipment.belt.str = 3;
    result = ft_calculate_str(&character);
    test_assert_true(result == 18, "ft_calculate_str should total base stats and equipment bonuses");
    return ;
}

static void test_calculate_con_sums_all_slots()
{
    t_char  character = {};
    int     result;

    character.stats.con = 8;
    character.equipment.weapon.con = 1;
    character.equipment.offhand_weapon.con = 1;
    character.equipment.ranged_weapon.con = 1;
    character.equipment.armor.con = 1;
    character.equipment.helmet.con = 1;
    character.equipment.shield.con = 1;
    character.equipment.boots.con = 1;
    character.equipment.gloves.con = 1;
    character.equipment.amulet.con = 1;
    character.equipment.ring_01.con = 1;
    character.equipment.ring_02.con = 1;
    character.equipment.belt.con = 1;
    result = ft_calculate_con(&character);
    test_assert_true(result == 20, "ft_calculate_con should include every equipment slot");
    return ;
}

static void test_calculate_dex_includes_equipment_bonus()
{
    t_char  character = {};
    int     result;

    character.stats.dex = 14;
    character.equipment.boots.dex = 1;
    character.equipment.gloves.dex = 2;
    character.equipment.ring_01.dex = 3;
    result = ft_calculate_dex(&character);
    test_assert_true(result == 20, "ft_calculate_dex should add base dex and equipment bonuses");
    return ;
}

static void test_calculate_wis_stacks_equipment_and_base()
{
    t_char  character = {};
    int     result;

    character.stats.wis = 8;
    character.equipment.helmet.wis = 2;
    character.equipment.amulet.wis = 4;
    result = ft_calculate_wis(&character);
    test_assert_true(result == 14, "ft_calculate_wis should total base wisdom and equipment bonuses");
    return ;
}

static void test_calculate_intelligence_totals_all_slots()
{
    t_char  character = {};
    int     result;

    character.stats.inte = 11;
    character.equipment.weapon.inte = 1;
    character.equipment.offhand_weapon.inte = 2;
    character.equipment.ranged_weapon.inte = 3;
    character.equipment.armor.inte = 4;
    character.equipment.helmet.inte = 5;
    character.equipment.shield.inte = 6;
    character.equipment.boots.inte = 7;
    character.equipment.gloves.inte = 8;
    character.equipment.amulet.inte = 9;
    character.equipment.ring_01.inte = 10;
    character.equipment.ring_02.inte = 11;
    character.equipment.belt.inte = 12;
    result = ft_calculate_inte(&character);
    test_assert_true(result == 89, "ft_calculate_inte should sum base intelligence and every equipment slot");
    return ;
}

static void test_calculate_cha_handles_negative_bonuses()
{
    t_char  character = {};
    int     result;

    character.stats.cha = 9;
    character.equipment.ring_02.cha = 1;
    character.equipment.belt.cha = -2;
    result = ft_calculate_cha(&character);
    test_assert_true(result == 8, "ft_calculate_cha should apply negative and positive modifiers");
    return ;
}

static void test_calculate_ac_caps_dex_bonus()
{
    t_char  character = {};
    int     result;

    character.stats.dex = 18;
    character.equipment.armor.dex_ac_max_bonus = 2;
    character.equipment.armor.ac = 5;
    result = ft_calculate_ac(&character);
    test_assert_true(result == 17, "ft_calculate_ac should respect the armor dex bonus cap");
    return ;
}

static void test_calculate_ac_uses_full_dex_when_under_cap()
{
    t_char  character = {};
    int     result;

    character.stats.dex = 12;
    character.equipment.boots.dex = 2;
    character.equipment.gloves.dex = 1;
    character.equipment.armor.dex_ac_max_bonus = 6;
    character.equipment.armor.ac = 3;
    character.equipment.shield.ac = 1;
    result = ft_calculate_ac(&character);
    test_assert_true(result == 16, "ft_calculate_ac should use the full dex modifier when under the cap");
    return ;
}

static void test_calculate_ac_applies_negative_dex_modifier()
{
    t_char  character = {};
    int     result;

    character.stats.dex = 7;
    character.equipment.armor.dex_ac_max_bonus = 5;
    character.equipment.armor.ac = 4;
    character.equipment.helmet.ac = 1;
    result = ft_calculate_ac(&character);
    test_assert_true(result == 13, "ft_calculate_ac should decrease AC when dex modifier is negative");
    return ;
}

void run_calculate_stats_tests()
{
    test_ability_mod_returns_zero_for_average_score();
    test_ability_mod_rounds_down_positive_scores();
    test_ability_mod_handles_negative_scores();
    test_ability_mod_handles_minimum_score();
    test_calculate_str_includes_equipment_bonus();
    test_calculate_con_sums_all_slots();
    test_calculate_dex_includes_equipment_bonus();
    test_calculate_wis_stacks_equipment_and_base();
    test_calculate_intelligence_totals_all_slots();
    test_calculate_cha_handles_negative_bonuses();
    test_calculate_ac_caps_dex_bonus();
    test_calculate_ac_uses_full_dex_when_under_cap();
    test_calculate_ac_applies_negative_dex_modifier();
    return ;
}
