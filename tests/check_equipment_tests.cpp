#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../identification.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

static void set_valid_equipment_slots(t_char *character)
{
    character->equipment.weapon.slot = SLOT_WEAPON;
    character->equipment.offhand_weapon.slot = SLOT_OFFHAND_WEAPON;
    character->equipment.ranged_weapon.slot = SLOT_RANGED_WEAPON;
    character->equipment.armor.slot = SLOT_ARMOR;
    character->equipment.helmet.slot = SLOT_HELMET;
    character->equipment.shield.slot = SLOT_SHIELD;
    character->equipment.boots.slot = SLOT_BOOTS;
    character->equipment.gloves.slot = SLOT_GLOVES;
    character->equipment.amulet.slot = SLOT_AMULET;
    character->equipment.ring_01.slot = SLOT_RING_01;
    character->equipment.ring_02.slot = SLOT_RING_02;
    character->equipment.belt.slot = SLOT_BELT;
    return ;
}

static void test_check_equipment_accepts_valid_configuration()
{
    t_char  character;
    int     result;

    character = {};
    set_valid_equipment_slots(&character);
    result = ft_check_equipment_slots(&character);
    test_assert_true(result == 0, "ft_check_equipment_slots should accept matching slots");
    return ;
}

static void test_check_equipment_detects_two_handed_offhand()
{
    t_char  character;
    int     result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    character = {};
    character.equipment.offhand_weapon.slot = SLOT_TWO_HANDED_WEAPON;
    file_path = "tests_output/check_equipment_two_handed_offhand.log";
    test_begin_error_capture(file_path);
    result = ft_check_equipment_slots(&character);
    test_end_error_capture();
    test_assert_true(result == 1, "ft_check_equipment_slots should flag two-handed offhand weapon");
    error_output = test_read_file_to_string(file_path);
    expected_message = "135-Error: Two-handed weapon in offhand slot\n";
    test_assert_true(error_output == expected_message,
        "ft_check_equipment_slots should log two-handed offhand error message");
    test_delete_file(file_path);
    return ;
}

static void test_check_equipment_detects_mismatched_armor_slot()
{
    t_char  character;
    int     result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    character = {};
    set_valid_equipment_slots(&character);
    character.equipment.armor.slot = SLOT_SHIELD;
    file_path = "tests_output/check_equipment_mismatched_armor.log";
    test_begin_error_capture(file_path);
    result = ft_check_equipment_slots(&character);
    test_end_error_capture();
    test_assert_true(result == 4, "ft_check_equipment_slots should return armor error code when armor slot mismatches");
    error_output = test_read_file_to_string(file_path);
    expected_message = "126-Error: Armor is not in the correct slot.\n";
    test_assert_true(error_output == expected_message,
        "ft_check_equipment_slots should log armor mismatch error message");
    test_delete_file(file_path);
    return ;
}

void    run_check_equipment_tests()
{
    test_begin_suite("check_equipment_tests");
    test_check_equipment_accepts_valid_configuration();
    test_check_equipment_detects_two_handed_offhand();
    test_check_equipment_detects_mismatched_armor_slot();
    test_end_suite_success();
    return ;
}
