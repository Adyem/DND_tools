#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../character.hpp"
#include "../libft/CPP_class/class_string_class.hpp"
static void initialize_character(t_char *character, const char *name)
{
    t_spell_slot empty_slot;
    t_spell_slots empty_slots;

    empty_slot.available = 0;
    empty_slot.total = 0;
    empty_slot.level = 0;
    empty_slot.replenishing_slot = 0;
    empty_slots.level_1 = empty_slot;
    empty_slots.level_2 = empty_slot;
    empty_slots.level_3 = empty_slot;
    empty_slots.level_4 = empty_slot;
    empty_slots.level_5 = empty_slot;
    empty_slots.level_6 = empty_slot;
    empty_slots.level_7 = empty_slot;
    empty_slots.level_8 = empty_slot;
    empty_slots.level_9 = empty_slot;
    empty_slots.warlock = empty_slot;
    character->spell_slots = empty_slots;
    character->name = name;
    return ;
}

static void test_auto_cast_uses_exact_level_when_available()
{
    t_char character;
    int cast_level;

    initialize_character(&character, "Tester");
    character.spell_slots.level_3.available = 1;
    g_dnd_test = true;
    cast_level = ft_prompt_spell_level(&character, 3, "Guiding Bolt");
    g_dnd_test = false;
    test_assert_true(cast_level == 3,
            "Auto cast should use an available slot matching the base level");
    return ;
}

static void test_auto_cast_selects_next_highest_slot()
{
    t_char character;
    int cast_level;

    initialize_character(&character, "Tester");
    character.spell_slots.level_4.available = 2;
    g_dnd_test = true;
    cast_level = ft_prompt_spell_level(&character, 3, "Shatter");
    g_dnd_test = false;
    test_assert_true(cast_level == 4,
            "Auto cast should pick the lowest slot at or above the base level");
    return ;
}

static void test_auto_cast_reports_error_when_no_valid_slot()
{
    t_char character;
    int cast_level;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    initialize_character(&character, "Tester");
    character.spell_slots.level_4.available = 1;
    file_path = "tests_output/spell_utils_auto_cast_error.log";
    test_begin_error_capture(file_path);
    g_dnd_test = true;
    cast_level = ft_prompt_spell_level(&character, 5, "Wall of Light");
    g_dnd_test = false;
    test_end_error_capture();
    test_assert_true(cast_level == -1,
            "Auto cast should fail when no slots meet the required level");
    error_output = test_read_file_to_string(file_path);
    expected_message = "Error: No available spell slots for Tester to cast Wall of Light.\n";
    test_assert_true(error_output == expected_message,
            "Auto cast should report missing spell slots in error output");
    test_delete_file(file_path);
    return ;
}

void run_spell_utils_tests()
{
    test_begin_suite("spell_utils_tests");
    test_auto_cast_uses_exact_level_when_available();
    test_auto_cast_selects_next_highest_slot();
    test_auto_cast_reports_error_when_no_valid_slot();
    test_end_suite_success();
    return ;
}
