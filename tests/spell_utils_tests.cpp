#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../character.hpp"
#include <cstring>

static void initialize_character(t_char *character, const char *name)
{
    std::memset(character, 0, sizeof(t_char));
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

    initialize_character(&character, "Tester");
    character.spell_slots.level_4.available = 1;
    g_dnd_test = true;
    cast_level = ft_prompt_spell_level(&character, 5, "Wall of Light");
    g_dnd_test = false;
    test_assert_true(cast_level == -1,
            "Auto cast should fail when no slots meet the required level");
    return ;
}

void run_spell_utils_tests()
{
    test_auto_cast_uses_exact_level_when_available();
    test_auto_cast_selects_next_highest_slot();
    test_auto_cast_reports_error_when_no_valid_slot();
    return ;
}
