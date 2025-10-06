#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"

static void initialize_flat_dr_slots(t_char &character, int t_resistance::*field,
    int start_value, int step)
{
    t_equipment_id    *slots[12];
    int                index;
    int                current_value;

    slots[0] = &character.equipment.weapon;
    slots[1] = &character.equipment.offhand_weapon;
    slots[2] = &character.equipment.ranged_weapon;
    slots[3] = &character.equipment.armor;
    slots[4] = &character.equipment.helmet;
    slots[5] = &character.equipment.shield;
    slots[6] = &character.equipment.boots;
    slots[7] = &character.equipment.gloves;
    slots[8] = &character.equipment.amulet;
    slots[9] = &character.equipment.ring_01;
    slots[10] = &character.equipment.ring_02;
    slots[11] = &character.equipment.belt;
    index = 0;
    current_value = start_value;
    while (index < 12)
    {
        ((slots[index]->flat_dr).*field) = current_value;
        current_value = current_value + step;
        index = index + 1;
    }
    return ;
}

static void test_calculate_damage_reduction_counts_each_slot_once()
{
    t_char  character = {};
    int     result;

    initialize_flat_dr_slots(character, &t_resistance::slashing, 1, 1);
    result = ft_calculate_slashing_dr(&character);
    test_assert_true(result == 78,
        "ft_calculate_slashing_dr should sum every equipment slot exactly once");
    return ;
}

static void test_calculate_damage_reduction_ignores_other_types()
{
    t_char  character = {};
    int     acid_result;
    int     fire_result;

    initialize_flat_dr_slots(character, &t_resistance::acid, 2, 2);
    initialize_flat_dr_slots(character, &t_resistance::fire, 5, 3);
    acid_result = ft_calculate_acid_dr(&character);
    fire_result = ft_calculate_fire_dr(&character);
    test_assert_true(acid_result == 156,
        "ft_calculate_acid_dr should only use acid damage reduction values");
    test_assert_true(fire_result == 258,
        "ft_calculate_fire_dr should only use fire damage reduction values");
    return ;
}

static void test_calculate_damage_reduction_handles_sparse_values()
{
    t_char  character = {};
    int     result;

    character.equipment.weapon.flat_dr.force = 9;
    character.equipment.gloves.flat_dr.force = -3;
    character.equipment.ring_01.flat_dr.force = 4;
    character.equipment.belt.flat_dr.force = 7;
    result = ft_calculate_force_dr(&character);
    test_assert_true(result == 17,
        "ft_calculate_force_dr should add only populated equipment slots");
    return ;
}

void    run_calculate_damage_reduction_tests()
{
    test_begin_suite("calculate_damage_reduction_tests");
    test_calculate_damage_reduction_counts_each_slot_once();
    test_calculate_damage_reduction_ignores_other_types();
    test_calculate_damage_reduction_handles_sparse_values();
    test_end_suite_success();
    return ;
}
