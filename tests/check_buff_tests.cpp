#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../identification.hpp"
#include "../libft/Libft/libft.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

static void verify_numeric_line(const ft_string &output,
    const char *prefix,
    const char *suffix)
{
    const char  *output_data;
    size_t      prefix_length;
    size_t      suffix_length;
    size_t      content_length;
    size_t      index;

    output_data = output.c_str();
    prefix_length = ft_strlen(prefix);
    suffix_length = ft_strlen(suffix);
    test_assert_true(output.size() >= prefix_length + suffix_length,
        "Captured output was shorter than the expected prefix and suffix");
    test_assert_true(ft_strncmp(output_data, prefix, prefix_length) == 0,
        "Captured output did not match the expected prefix");
    test_assert_true(ft_strncmp(output_data + output.size() - suffix_length,
            suffix,
            suffix_length) == 0,
        "Captured output did not match the expected suffix");
    content_length = output.size() - prefix_length - suffix_length;
    test_assert_true(content_length > 0,
        "Captured output did not contain a numeric value");
    index = 0;
    while (index < content_length)
    {
        char current;

        current = output_data[prefix_length + index];
        test_assert_true(current >= '0' && current <= '9',
            "Captured output contained non-numeric characters in the value segment");
        index++;
    }
    return ;
}

static void test_check_bless_returns_zero_when_duration_expired()
{
    t_char  character = {};
    int     result;

    character.name = "Cleric";
    character.bufs.bless.duration = 0;
    character.bufs.bless.base_mod = 7;
    character.bufs.bless.dice_amount_mod = 1;
    character.bufs.bless.dice_faces_mod = 8;
    result = ft_check_bless(&character);
    test_assert_true(result == 0, "ft_check_bless should return zero when the buff is not active");
    return ;
}

static void test_check_bless_returns_base_modifier_without_dice()
{
    t_char  character = {};
    int     result;
    const char  *file_path;
    ft_string   output;

    character.name = "Priest";
    character.bufs.bless.duration = 3;
    character.bufs.bless.dice_amount_mod = 0;
    character.bufs.bless.dice_faces_mod = 0;
    character.bufs.bless.base_mod = 5;
    file_path = "tests_output/check_buff_bless_base.log";
    test_begin_output_capture(file_path);
    result = ft_check_bless(&character);
    test_end_output_capture();
    test_assert_true(result == 5, "ft_check_bless should use the base modifier when no dice are rolled");
    output = test_read_file_to_string(file_path);
    verify_numeric_line(output,
        "Priest rolled a ",
        " as an additional modifier for his/her bless buff\n");
    test_delete_file(file_path);
    return ;
}

static void test_check_bless_returns_zero_on_dice_roll_error()
{
    t_char  character = {};
    int     result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    character.name = "Acolyte";
    character.bufs.bless.duration = 2;
    character.bufs.bless.dice_amount_mod = 1;
    character.bufs.bless.dice_faces_mod = -1;
    file_path = "tests_output/check_buff_bless_error.log";
    test_begin_error_capture(file_path);
    result = ft_check_bless(&character);
    test_end_error_capture();
    test_assert_true(result == 0, "ft_check_bless should return zero when dice rolling fails");
    error_output = test_read_file_to_string(file_path);
    expected_message =
        "410-Error: Dice roll parameters must be positive (dice=1 faces=-1)\n"
        "144-Error: dice rolling bless\n";
    test_assert_true(error_output == expected_message,
        "ft_check_bless should log dice roll failure message");
    test_delete_file(file_path);
    return ;
}

static void test_attack_roll_check_buffs_applies_bless_and_flanking()
{
    t_char  character = {};
    int     roll;
    int     bonus;
    const char  *file_path;
    ft_string   output;
    size_t      newline_position;
    ft_string   first_line;
    ft_string   second_line;

    character.name = "Fighter";
    character.bufs.bless.duration = 1;
    character.bufs.bless.dice_amount_mod = 0;
    character.bufs.bless.dice_faces_mod = 0;
    character.bufs.bless.base_mod = 3;
    character.flags.flanking = 1;
    roll = 12;
    file_path = "tests_output/check_buff_attack_bless.log";
    test_begin_output_capture(file_path);
    bonus = ft_attack_roll_check_buffs(&character, &roll);
    test_end_output_capture();
    test_assert_true(bonus == 3, "ft_attack_roll_check_buffs should include bless bonus");
    test_assert_true(character.flags.advantage == 1, "ft_attack_roll_check_buffs should grant advantage when flanking");
    output = test_read_file_to_string(file_path);
    newline_position = output.find("\n");
    test_assert_true(newline_position != ft_string::npos,
        "Attack buff output should contain a newline separating messages");
    first_line = output.substr(0, newline_position + 1);
    second_line = output.substr(newline_position + 1);
    verify_numeric_line(first_line,
        "Fighter rolled a ",
        " as an additional modifier for his/her bless buff\n");
    verify_numeric_line(second_line,
        "Fighter rolled ",
        " on his/her advantage\n");
    test_delete_file(file_path);
    return ;
}

static void test_attack_roll_check_buffs_penalizes_blinded_characters()
{
    t_char  character = {};
    int     roll;
    const char  *file_path;
    ft_string   output;

    character.name = "Rogue";
    character.debufs.blinded.duration = 1;
    roll = 14;
    file_path = "tests_output/check_buff_attack_disadvantage.log";
    test_begin_output_capture(file_path);
    ft_attack_roll_check_buffs(&character, &roll);
    test_end_output_capture();
    test_assert_true(character.flags.advantage == -1, "ft_attack_roll_check_buffs should apply disadvantage when blinded");
    output = test_read_file_to_string(file_path);
    verify_numeric_line(output,
        "Rogue rolled ",
        " on his/her disadvantage\n");
    test_delete_file(file_path);
    return ;
}

static void test_save_check_buff_grants_advantage_for_mighty_resilience()
{
    t_char  character = {};
    int     roll;
    int     bonus;
    const char  *file_path;
    ft_string   output;
    size_t      newline_position;
    ft_string   first_line;
    ft_string   second_line;

    character.name = "Paladin";
    character.bufs.bless.duration = 1;
    character.bufs.bless.dice_amount_mod = 0;
    character.bufs.bless.dice_faces_mod = 0;
    character.bufs.bless.base_mod = 2;
    character.feats.mighty_resilience.active = 1;
    roll = 9;
    file_path = "tests_output/check_buff_save_advantage.log";
    test_begin_output_capture(file_path);
    bonus = ft_save_check_buff(&character, &roll, STAT_STR);
    test_end_output_capture();
    test_assert_true(bonus == 2, "ft_save_check_buff should include bless bonus");
    test_assert_true(character.flags.advantage == 1, "ft_save_check_buff should grant advantage on strength saves with mighty resilience");
    output = test_read_file_to_string(file_path);
    newline_position = output.find("\n");
    test_assert_true(newline_position != ft_string::npos,
        "Save buff output should contain two lines");
    first_line = output.substr(0, newline_position + 1);
    second_line = output.substr(newline_position + 1);
    verify_numeric_line(first_line,
        "Paladin rolled a ",
        " as an additional modifier for his/her bless buff\n");
    verify_numeric_line(second_line,
        "Paladin rolled ",
        " on his/her advantage\n");
    test_delete_file(file_path);
    return ;
}

static void test_save_check_buff_ignores_non_strength_or_constitution()
{
    t_char  character = {};
    int     roll;
    int     bonus;

    character.name = "Paladin";
    character.bufs.bless.duration = 0;
    character.feats.mighty_resilience.active = 1;
    roll = 11;
    bonus = ft_save_check_buff(&character, &roll, "wisdom");
    test_assert_true(bonus == 0, "ft_save_check_buff should not add bless when the buff is inactive");
    test_assert_true(character.flags.advantage == 0, "ft_save_check_buff should not change advantage for other ability scores");
    return ;
}

static void test_skill_check_buff_leaves_roll_unchanged_without_advantage()
{
    t_char  character = {};
    int     roll;
    int     result;

    character.name = "Bard";
    roll = 15;
    result = ft_skill_check_buff(&character, &roll, "performance");
    test_assert_true(result == 0, "ft_skill_check_buff should return zero when no bonuses apply");
    test_assert_true(roll == 15, "ft_skill_check_buff should leave the roll unchanged without advantage");
    return ;
}

static void test_check_buff_damage_ignores_non_hunters_mark_spells()
{
    t_char  character = {};
    int     result;

    character.name = "Ranger";
    character.concentration.spell_id = 0;
    result = ft_check_buff_damage(&character);
    test_assert_true(result == 0, "ft_check_buff_damage should return zero when concentration is not hunter's mark");
    return ;
}

static void test_check_buff_damage_handles_hunters_mark_extra_damage()
{
    t_char  character = {};
    int     result;
    char    target_buffer[] = "Target";
    char    *targets[2];
    const char  *file_path;
    ft_string   output;

    character.name = "Ranger";
    character.concentration.spell_id = HUNTERS_MARK_ID;
    character.concentration.dice_amount_mod = 0;
    character.concentration.dice_faces_mod = 0;
    character.concentration.extra = 4;
    targets[0] = target_buffer;
    targets[1] = NULL;
    character.concentration.targets = targets;
    file_path = "tests_output/check_buff_hunters_mark.log";
    test_begin_output_capture(file_path);
    result = ft_check_buff_damage(&character);
    test_end_output_capture();
    test_assert_true(result == 0, "ft_check_buff_damage should leave the return value unchanged after reporting hunter's mark");
    output = test_read_file_to_string(file_path);
    verify_numeric_line(output,
        "Ranger deals ",
        " extra damage if the target is Target\n");
    test_delete_file(file_path);
    return ;
}

void    run_check_buff_tests()
{
    test_begin_suite("check_buff_tests");
    test_check_bless_returns_zero_when_duration_expired();
    test_check_bless_returns_base_modifier_without_dice();
    test_check_bless_returns_zero_on_dice_roll_error();
    test_attack_roll_check_buffs_applies_bless_and_flanking();
    test_attack_roll_check_buffs_penalizes_blinded_characters();
    test_save_check_buff_grants_advantage_for_mighty_resilience();
    test_save_check_buff_ignores_non_strength_or_constitution();
    test_skill_check_buff_leaves_roll_unchanged_without_advantage();
    test_check_buff_damage_ignores_non_hunters_mark_spells();
    test_check_buff_damage_handles_hunters_mark_extra_damage();
    test_end_suite_success();
    return ;
}
