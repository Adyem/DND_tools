#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../identification.hpp"

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

    character = {};
    character.equipment.offhand_weapon.slot = SLOT_TWO_HANDED_WEAPON;
    result = ft_check_equipment_slots(&character);
    test_assert_true(result == 1, "ft_check_equipment_slots should flag two-handed offhand weapon");
    return ;
}

static void test_check_equipment_detects_mismatched_armor_slot()
{
    t_char  character;
    int     result;

    character = {};
    set_valid_equipment_slots(&character);
    character.equipment.armor.slot = SLOT_SHIELD;
    result = ft_check_equipment_slots(&character);
    test_assert_true(result == 4, "ft_check_equipment_slots should return armor error code when armor slot mismatches");
    return ;
}

void    run_check_equipment_tests()
{
    test_check_equipment_accepts_valid_configuration();
    test_check_equipment_detects_two_handed_offhand();
    test_check_equipment_detects_mismatched_armor_slot();
    return ;
}
