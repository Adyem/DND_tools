#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/Printf/printf.hpp"

static void test_calculate_athletics_totals_all_sources()
{
    t_char  character = {};
    int     result;

    character.skill_mod.athletics = 1;
    character.equipment.weapon.skill_mod.athletics = 2;
    character.equipment.offhand_weapon.skill_mod.athletics = 3;
    character.equipment.ranged_weapon.skill_mod.athletics = 4;
    character.equipment.armor.skill_mod.athletics = 5;
    character.equipment.helmet.skill_mod.athletics = 6;
    character.equipment.shield.skill_mod.athletics = 7;
    character.equipment.boots.skill_mod.athletics = 8;
    character.equipment.gloves.skill_mod.athletics = 9;
    character.equipment.amulet.skill_mod.athletics = 10;
    character.equipment.ring_01.skill_mod.athletics = 11;
    character.equipment.ring_02.skill_mod.athletics = 12;
    character.equipment.belt.skill_mod.athletics = 13;
    result = ft_calculate_athletics(&character);
    char message[128];

    pf_snprintf(message, sizeof(message),
        "ft_calculate_athletics expected 91 but got %d", result);
    test_assert_true(result == 91, message);
    return ;
}

static void test_calculate_perception_handles_negative_modifiers()
{
    t_char  character = {};
    int     result;

    character.skill_mod.perception = 5;
    character.equipment.weapon.skill_mod.perception = -2;
    character.equipment.boots.skill_mod.perception = 3;
    character.equipment.gloves.skill_mod.perception = -1;
    result = ft_calculate_perception(&character);
    test_assert_true(result == 5, "ft_calculate_perception should include negative and positive bonuses");
    return ;
}

static void test_calculate_deception_isolated_from_other_skills()
{
    t_char  character = {};
    int     result;

    character.skill_mod.deception = 4;
    character.equipment.weapon.skill_mod.deception = 1;
    character.equipment.helmet.skill_mod.deception = 2;
    character.equipment.ring_02.skill_mod.deception = 3;
    character.skill_mod.performance = 99;
    character.equipment.weapon.skill_mod.performance = 88;
    character.equipment.helmet.skill_mod.performance = 77;
    result = ft_calculate_deception(&character);
    test_assert_true(result == 10, "ft_calculate_deception should ignore modifiers from other skills");
    return ;
}

static void test_calculate_stealth_handles_mixed_modifiers()
{
    t_char  character = {};
    int     result;

    character.skill_mod.stealth = 2;
    character.equipment.armor.skill_mod.stealth = -1;
    character.equipment.boots.skill_mod.stealth = 4;
    character.equipment.amulet.skill_mod.stealth = 3;
    character.equipment.ring_01.skill_mod.stealth = -2;
    character.equipment.belt.skill_mod.stealth = 5;
    result = ft_calculate_stealth(&character);
    test_assert_true(result == 11, "ft_calculate_stealth should total base and equipment modifiers");
    return ;
}

static void test_calculate_arcana_totals_positive_and_negative_sources()
{
    t_char  character = {};
    int     result;

    character.skill_mod.arcana = -1;
    character.equipment.weapon.skill_mod.arcana = 2;
    character.equipment.offhand_weapon.skill_mod.arcana = -3;
    character.equipment.ranged_weapon.skill_mod.arcana = 4;
    character.equipment.armor.skill_mod.arcana = -5;
    character.equipment.helmet.skill_mod.arcana = 6;
    character.equipment.shield.skill_mod.arcana = -7;
    character.equipment.boots.skill_mod.arcana = 8;
    character.equipment.gloves.skill_mod.arcana = -9;
    character.equipment.amulet.skill_mod.arcana = 10;
    character.equipment.ring_01.skill_mod.arcana = -11;
    character.equipment.ring_02.skill_mod.arcana = 12;
    character.equipment.belt.skill_mod.arcana = -13;
    result = ft_calculate_arcana(&character);
    test_assert_true(result == -7, "ft_calculate_arcana should include every equipment slot even with negative totals");
    return ;
}

static void test_calculate_persuasion_includes_ring_slots()
{
    t_char  character = {};
    int     result;

    character.skill_mod.persuasion = 1;
    character.equipment.ring_01.skill_mod.persuasion = 5;
    character.equipment.ring_02.skill_mod.persuasion = 6;
    result = ft_calculate_persuasion(&character);
    test_assert_true(result == 12, "ft_calculate_persuasion should include both ring slots");
    return ;
}

static void test_calculate_survival_defaults_to_zero()
{
    t_char  character = {};
    int     result;

    result = ft_calculate_survival(&character);
    test_assert_true(result == 0, "ft_calculate_survival should be zero when no bonuses are provided");
    return ;
}

static void test_calculate_acrobatics_includes_jewelry_slots()
{
    t_char  character = {};
    int     result;

    character.skill_mod.acrobatics = 2;
    character.equipment.amulet.skill_mod.acrobatics = 5;
    character.equipment.ring_01.skill_mod.acrobatics = 6;
    character.equipment.ring_02.skill_mod.acrobatics = 7;
    character.equipment.belt.skill_mod.acrobatics = 8;
    result = ft_calculate_acrobatics(&character);
    test_assert_true(result == 28, "ft_calculate_acrobatics should total base and jewelry modifiers");
    return ;
}

static void test_calculate_investigation_isolated_from_other_skills()
{
    t_char  character = {};
    int     result;

    character.skill_mod.investigation = 4;
    character.equipment.weapon.skill_mod.investigation = 1;
    character.equipment.offhand_weapon.skill_mod.investigation = 2;
    character.equipment.armor.skill_mod.investigation = 3;
    character.skill_mod.arcana = 90;
    character.equipment.weapon.skill_mod.arcana = 80;
    character.equipment.armor.skill_mod.arcana = 70;
    result = ft_calculate_investigation(&character);
    test_assert_true(result == 10, "ft_calculate_investigation should ignore other skill modifiers");
    return ;
}

static void test_calculate_medicine_handles_armor_and_gloves()
{
    t_char  character = {};
    int     result;

    character.skill_mod.medicine = -1;
    character.equipment.armor.skill_mod.medicine = 4;
    character.equipment.gloves.skill_mod.medicine = 3;
    result = ft_calculate_medicine(&character);
    test_assert_true(result == 6, "ft_calculate_medicine should sum armor and glove bonuses with the base value");
    return ;
}

static void test_calculate_intimidation_handles_negative_bonuses()
{
    t_char  character = {};
    int     result;

    character.skill_mod.intimidation = 3;
    character.equipment.helmet.skill_mod.intimidation = -2;
    character.equipment.shield.skill_mod.intimidation = 5;
    character.equipment.boots.skill_mod.intimidation = -1;
    result = ft_calculate_intimidation(&character);
    test_assert_true(result == 5, "ft_calculate_intimidation should apply negative and positive modifiers");
    return ;
}

static void test_calculate_performance_includes_belt_bonus()
{
    t_char  character = {};
    int     result;

    character.skill_mod.performance = 1;
    character.equipment.belt.skill_mod.performance = 4;
    result = ft_calculate_performance(&character);
    test_assert_true(result == 5, "ft_calculate_performance should include belt contributions");
    return ;
}

static void test_calculate_sleight_of_hand_includes_weapon_and_gloves()
{
    t_char  character = {};
    int     result;

    character.skill_mod.sleight_of_hand = 2;
    character.equipment.weapon.skill_mod.sleight_of_hand = 3;
    character.equipment.gloves.skill_mod.sleight_of_hand = 4;
    result = ft_calculate_sleight_of_hand(&character);
    test_assert_true(result == 9, "ft_calculate_sleight_of_hand should total base, weapon, and glove bonuses");
    return ;
}

static void test_calculate_history_ignores_other_skills()
{
    t_char  character = {};
    int     result;

    character.skill_mod.history = 5;
    character.equipment.helmet.skill_mod.history = 4;
    character.equipment.amulet.skill_mod.history = 3;
    character.skill_mod.religion = 77;
    character.equipment.helmet.skill_mod.religion = 66;
    result = ft_calculate_history(&character);
    test_assert_true(result == 12, "ft_calculate_history should ignore modifiers from other skills");
    return ;
}

static void test_calculate_nature_handles_negative_equipment()
{
    t_char  character = {};
    int     result;

    character.skill_mod.nature = 4;
    character.equipment.weapon.skill_mod.nature = -2;
    character.equipment.boots.skill_mod.nature = 5;
    character.equipment.ring_01.skill_mod.nature = -1;
    result = ft_calculate_nature(&character);
    test_assert_true(result == 6, "ft_calculate_nature should include positive and negative modifiers");
    return ;
}

static void test_calculate_religion_includes_jewelry()
{
    t_char  character = {};
    int     result;

    character.skill_mod.religion = 1;
    character.equipment.amulet.skill_mod.religion = 5;
    character.equipment.ring_01.skill_mod.religion = 6;
    character.equipment.ring_02.skill_mod.religion = 7;
    character.equipment.belt.skill_mod.religion = 8;
    result = ft_calculate_religion(&character);
    test_assert_true(result == 27, "ft_calculate_religion should total jewelry modifiers with the base value");
    return ;
}

static void test_calculate_animal_handling_defaults_to_zero()
{
    t_char  character = {};
    int     result;

    result = ft_calculate_animal_handling(&character);
    test_assert_true(result == 0, "ft_calculate_animal_handling should be zero without bonuses");
    return ;
}

static void test_calculate_insight_sums_all_sources()
{
    t_char  character = {};
    int     result;

    character.skill_mod.insight = 3;
    character.equipment.weapon.skill_mod.insight = 4;
    character.equipment.offhand_weapon.skill_mod.insight = 5;
    character.equipment.ranged_weapon.skill_mod.insight = 6;
    character.equipment.armor.skill_mod.insight = 7;
    character.equipment.helmet.skill_mod.insight = 8;
    character.equipment.shield.skill_mod.insight = 9;
    character.equipment.boots.skill_mod.insight = 10;
    character.equipment.gloves.skill_mod.insight = 11;
    character.equipment.amulet.skill_mod.insight = 12;
    character.equipment.ring_01.skill_mod.insight = 13;
    character.equipment.ring_02.skill_mod.insight = 14;
    character.equipment.belt.skill_mod.insight = 15;
    result = ft_calculate_insight(&character);
    test_assert_true(result == 117, "ft_calculate_insight should include every equipment slot");
    return ;
}

void run_calculate_skills_tests()
{
    test_begin_suite("calculate_skills_tests");
    test_calculate_athletics_totals_all_sources();
    test_calculate_perception_handles_negative_modifiers();
    test_calculate_deception_isolated_from_other_skills();
    test_calculate_stealth_handles_mixed_modifiers();
    test_calculate_arcana_totals_positive_and_negative_sources();
    test_calculate_persuasion_includes_ring_slots();
    test_calculate_survival_defaults_to_zero();
    test_calculate_acrobatics_includes_jewelry_slots();
    test_calculate_investigation_isolated_from_other_skills();
    test_calculate_medicine_handles_armor_and_gloves();
    test_calculate_intimidation_handles_negative_bonuses();
    test_calculate_performance_includes_belt_bonus();
    test_calculate_sleight_of_hand_includes_weapon_and_gloves();
    test_calculate_history_ignores_other_skills();
    test_calculate_nature_handles_negative_equipment();
    test_calculate_religion_includes_jewelry();
    test_calculate_animal_handling_defaults_to_zero();
    test_calculate_insight_sums_all_sources();
    test_end_suite_success();
    return ;
}
