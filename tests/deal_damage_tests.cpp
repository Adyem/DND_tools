#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

static void initialize_character(t_char &character, const char *name)
{
    character = {};
    character.name = name;
    character.dstats.health = 30;
    character.stats.health = 20;
    character.version_number = 1;
    character.bufs.growth.stacks = 0;
    return ;
}

static void test_deal_damage_applies_flat_reduction()
{
    t_char      character;
    const char  *output_path;
    ft_string   output;

    initialize_character(character, "Test Warrior");
    character.equipment.shield.flat_dr.slashing = 3;
    output_path = "tests_output/deal_damage_flat_reduction.log";
    test_begin_output_capture(output_path);
    ft_deal_damage(&character, "10", "slashing", 0, 1);
    test_end_output_capture();
    output = test_read_file_to_string(output_path);
    test_delete_file(output_path);
    test_assert_true(character.stats.health == 13, "ft_deal_damage should subtract flat reduction from damage");
    test_assert_true(output == "The slashing damage was reduced by 3.\n",
        "ft_deal_damage should report flat damage reduction");
    return ;
}

static void test_deal_damage_applies_resistance_and_growth()
{
    t_char      character;
    const char  *output_path;
    ft_string   output;

    initialize_character(character, "Test Guardian");
    character.stats.health = 18;
    character.bufs.growth.stacks = 2;
    output_path = "tests_output/deal_damage_resistance_growth.log";
    test_begin_output_capture(output_path);
    ft_deal_damage(&character, "10", "fire", 50, 1);
    test_end_output_capture();
    output = test_read_file_to_string(output_path);
    test_delete_file(output_path);
    test_assert_true(character.stats.health == 15, "ft_deal_damage should apply resistance and growth reduction");
    test_assert_true(output == "Test Guardian is resistant to fire damage and takes 50% less damage for a total of 5 less damage.\n"
        "growth reduces damage by 2.\n",
        "ft_deal_damage should print resistance and growth messages");
    return ;
}

static void test_deal_damage_handles_unknown_type()
{
    t_char      character;
    const char  *error_path;
    ft_string   error_output;

    initialize_character(character, "Test Ranger");
    character.stats.health = 25;
    error_path = "tests_output/deal_damage_unknown_type.log";
    test_begin_error_capture(error_path);
    ft_deal_damage(&character, "5", "unknown", 0, 1);
    test_end_error_capture();
    error_output = test_read_file_to_string(error_path);
    test_delete_file(error_path);
    test_assert_true(character.stats.health == 25, "ft_deal_damage should ignore unknown damage types");
    test_assert_true(error_output == "161-Error finding damage reduction\n",
        "ft_deal_damage should report failure to resolve damage reduction");
    return ;
}

void    run_deal_damage_tests()
{
    test_begin_suite("deal_damage_tests");
    test_deal_damage_applies_flat_reduction();
    test_deal_damage_applies_resistance_and_growth();
    test_deal_damage_handles_unknown_type();
    test_end_suite_success();
    return ;
}
