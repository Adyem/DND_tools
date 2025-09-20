#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"

static void set_resistance_sequence(t_char &character, int t_resistance::*field)
{
    (character.equipment.weapon.resistance.*field) = 1;
    (character.equipment.offhand_weapon.resistance.*field) = 2;
    (character.equipment.ranged_weapon.resistance.*field) = 3;
    (character.equipment.armor.resistance.*field) = 4;
    (character.equipment.helmet.resistance.*field) = 5;
    (character.equipment.shield.resistance.*field) = 6;
    (character.equipment.boots.resistance.*field) = 7;
    (character.equipment.gloves.resistance.*field) = 8;
    (character.equipment.amulet.resistance.*field) = 9;
    (character.equipment.ring_01.resistance.*field) = 10;
    (character.equipment.ring_02.resistance.*field) = 11;
    (character.equipment.belt.resistance.*field) = 12;
    return ;
}

static void set_flat_dr_sequence(t_char &character, int t_resistance::*field)
{
    (character.equipment.weapon.flat_dr.*field) = 1;
    (character.equipment.offhand_weapon.flat_dr.*field) = 2;
    (character.equipment.ranged_weapon.flat_dr.*field) = 3;
    (character.equipment.armor.flat_dr.*field) = 4;
    (character.equipment.helmet.flat_dr.*field) = 5;
    (character.equipment.shield.flat_dr.*field) = 6;
    (character.equipment.boots.flat_dr.*field) = 7;
    (character.equipment.gloves.flat_dr.*field) = 8;
    (character.equipment.amulet.flat_dr.*field) = 9;
    (character.equipment.ring_01.flat_dr.*field) = 10;
    (character.equipment.ring_02.flat_dr.*field) = 11;
    (character.equipment.belt.flat_dr.*field) = 12;
    return ;
}

static void test_calculate_resistance_includes_character_base()
{
    t_char  character = {};
    int     result;

    set_resistance_sequence(character, &t_resistance::acid);
    character.c_resistance.acid = 5;
    result = ft_calculate_acid_resistance(&character);
    test_assert_true(result == 83, "ft_calculate_acid_resistance should include character base and equipment");
    return ;
}

static void test_calculate_resistance_defaults_to_zero()
{
    t_char  character = {};
    int     acid_result;
    int     thunder_result;

    acid_result = ft_calculate_acid_resistance(&character);
    thunder_result = ft_calculate_thunder_resistance(&character);
    test_assert_true(acid_result == 0, "ft_calculate_acid_resistance should be zero with no bonuses");
    test_assert_true(thunder_result == 0, "ft_calculate_thunder_resistance should be zero with no bonuses");
    return ;
}

static void test_calculate_resistance_separates_types()
{
    t_char  character = {};
    int     acid_result;
    int     fire_result;

    character.c_resistance.acid = 3;
    character.c_resistance.fire = 9;
    character.equipment.weapon.resistance.acid = 4;
    character.equipment.weapon.resistance.fire = 11;
    character.equipment.shield.resistance.fire = 5;
    character.equipment.boots.resistance.acid = 6;
    acid_result = ft_calculate_acid_resistance(&character);
    fire_result = ft_calculate_fire_resistance(&character);
    test_assert_true(acid_result == 13, "ft_calculate_acid_resistance should only total acid values");
    test_assert_true(fire_result == 25, "ft_calculate_fire_resistance should only total fire values");
    return ;
}

static void test_calculate_lightning_resistance_totals_equipment()
{
    t_char  character = {};
    int     result;

    character.c_resistance.lightning = 4;
    character.equipment.weapon.resistance.lightning = 5;
    character.equipment.offhand_weapon.resistance.lightning = 6;
    character.equipment.ranged_weapon.resistance.lightning = 7;
    character.equipment.armor.resistance.lightning = 8;
    character.equipment.helmet.resistance.lightning = 9;
    character.equipment.shield.resistance.lightning = 10;
    character.equipment.boots.resistance.lightning = 11;
    character.equipment.gloves.resistance.lightning = 12;
    character.equipment.amulet.resistance.lightning = 13;
    character.equipment.ring_01.resistance.lightning = 14;
    character.equipment.ring_02.resistance.lightning = 15;
    character.equipment.belt.resistance.lightning = 16;
    result = ft_calculate_lightning_resistance(&character);
    test_assert_true(result == 130, "ft_calculate_lightning_resistance should include base and every equipment slot");
    return ;
}

static void test_calculate_resistance_handles_negative_modifiers()
{
    t_char  character = {};
    int     poison_result;

    character.c_resistance.poison = 5;
    character.equipment.weapon.resistance.poison = -3;
    character.equipment.boots.resistance.poison = 1;
    poison_result = ft_calculate_poison_resistance(&character);
    test_assert_true(poison_result == 3, "ft_calculate_poison_resistance should include negative equipment modifiers");
    return ;
}

static void test_calculate_poison_resistance_handles_negative_base()
{
    t_char  character = {};
    int     result;

    character.c_resistance.poison = -3;
    character.equipment.boots.resistance.poison = 5;
    result = ft_calculate_poison_resistance(&character);
    test_assert_true(result == 2, "ft_calculate_poison_resistance should add equipment to negative base values");
    return ;
}

static void test_calculate_damage_reduction_sums_equipment_slots()
{
    t_char  character = {};
    int     result;

    set_flat_dr_sequence(character, &t_resistance::acid);
    result = ft_calculate_acid_dr(&character);
    test_assert_true(result == 78, "ft_calculate_acid_dr should sum acid flat damage reduction across equipment");
    return ;
}

static void test_calculate_damage_reduction_ignores_character_resistance()
{
    t_char  character = {};
    int     result;

    character.c_resistance.acid = 123;
    result = ft_calculate_acid_dr(&character);
    test_assert_true(result == 0, "ft_calculate_acid_dr should not use character resistances");
    return ;
}

static void test_calculate_damage_reduction_handles_negative_values()
{
    t_char  character = {};
    int     result;

    character.equipment.weapon.flat_dr.fire = -2;
    character.equipment.shield.flat_dr.fire = 5;
    result = ft_calculate_fire_dr(&character);
    test_assert_true(result == 3, "ft_calculate_fire_dr should total negative and positive values");
    return ;
}

static void test_calculate_damage_reduction_defaults_to_zero()
{
    t_char  character = {};
    int     result;

    result = ft_calculate_psychic_dr(&character);
    test_assert_true(result == 0, "ft_calculate_psychic_dr should be zero when equipment provides no reduction");
    return ;
}

static void test_calculate_psychic_resistance_ignores_flat_damage_reduction()
{
    t_char  character = {};
    int     result;

    character.c_resistance.psychic = 7;
    character.equipment.weapon.flat_dr.psychic = 100;
    character.equipment.helmet.flat_dr.psychic = -50;
    result = ft_calculate_psychic_resistance(&character);
    test_assert_true(result == 7, "ft_calculate_psychic_resistance should ignore flat damage reduction values");
    return ;
}

static void test_calculate_force_resistance_includes_jewelry()
{
    t_char  character = {};
    int     result;

    character.c_resistance.force = 4;
    character.equipment.amulet.resistance.force = 5;
    character.equipment.ring_01.resistance.force = 6;
    character.equipment.ring_02.resistance.force = 7;
    character.equipment.belt.resistance.force = 8;
    result = ft_calculate_force_resistance(&character);
    test_assert_true(result == 30, "ft_calculate_force_resistance should include jewelry contributions");
    return ;
}

static void test_calculate_bludgeoning_resistance_totals_equipment()
{
    t_char  character = {};
    int     result;

    set_resistance_sequence(character, &t_resistance::bludgeoning);
    character.c_resistance.bludgeoning = 4;
    result = ft_calculate_bludgeoning_resistance(&character);
    test_assert_true(result == 82, "ft_calculate_bludgeoning_resistance should include base and every equipment slot");
    return ;
}

static void test_calculate_slashing_resistance_handles_negative_equipment()
{
    t_char  character = {};
    int     result;

    character.c_resistance.slashing = 6;
    character.equipment.weapon.resistance.slashing = -2;
    character.equipment.shield.resistance.slashing = 5;
    character.equipment.boots.resistance.slashing = -1;
    result = ft_calculate_slashing_resistance(&character);
    test_assert_true(result == 8, "ft_calculate_slashing_resistance should apply negative and positive modifiers");
    return ;
}

static void test_calculate_piercing_resistance_isolates_other_types()
{
    t_char  character = {};
    int     result;

    character.c_resistance.piercing = 3;
    set_resistance_sequence(character, &t_resistance::piercing);
    character.equipment.weapon.resistance.slashing = 100;
    character.equipment.shield.resistance.fire = 200;
    character.equipment.ring_01.resistance.acid = 300;
    result = ft_calculate_piercing_resistance(&character);
    test_assert_true(result == 81, "ft_calculate_piercing_resistance should ignore other resistance types");
    return ;
}

static void test_calculate_cold_resistance_defaults_to_zero()
{
    t_char  character = {};
    int     result;

    result = ft_calculate_cold_resistance(&character);
    test_assert_true(result == 0, "ft_calculate_cold_resistance should be zero when no bonuses are provided");
    return ;
}

static void test_calculate_lightning_dr_totals_equipment()
{
    t_char  character = {};
    int     result;

    set_flat_dr_sequence(character, &t_resistance::lightning);
    result = ft_calculate_lightning_dr(&character);
    test_assert_true(result == 78, "ft_calculate_lightning_dr should include every equipment slot");
    return ;
}

static void test_calculate_bludgeoning_dr_handles_negative_values()
{
    t_char  character = {};
    int     result;

    character.equipment.weapon.flat_dr.bludgeoning = -4;
    character.equipment.armor.flat_dr.bludgeoning = 7;
    character.equipment.belt.flat_dr.bludgeoning = 2;
    result = ft_calculate_bludgeoning_dr(&character);
    test_assert_true(result == 5, "ft_calculate_bludgeoning_dr should include positive and negative modifiers");
    return ;
}

static void test_calculate_piercing_dr_defaults_to_zero()
{
    t_char  character = {};
    int     result;

    result = ft_calculate_piercing_dr(&character);
    test_assert_true(result == 0, "ft_calculate_piercing_dr should be zero with no equipment bonuses");
    return ;
}

static void test_calculate_necrotic_resistance_handles_negative_equipment()
{
    t_char  character = {};
    int     result;

    character.c_resistance.necrotic = 12;
    character.equipment.weapon.resistance.necrotic = -3;
    character.equipment.offhand_weapon.resistance.necrotic = -2;
    character.equipment.boots.resistance.necrotic = 1;
    result = ft_calculate_necrotic_resistance(&character);
    test_assert_true(result == 8, "ft_calculate_necrotic_resistance should add negative and positive equipment bonuses");
    return ;
}

static void test_calculate_radiant_dr_sums_equipment()
{
    t_char  character = {};
    int     result;

    character.equipment.weapon.flat_dr.radiant = 1;
    character.equipment.offhand_weapon.flat_dr.radiant = 2;
    character.equipment.ranged_weapon.flat_dr.radiant = 3;
    character.equipment.armor.flat_dr.radiant = 4;
    character.equipment.helmet.flat_dr.radiant = 5;
    character.equipment.shield.flat_dr.radiant = 6;
    character.equipment.boots.flat_dr.radiant = 7;
    character.equipment.gloves.flat_dr.radiant = 8;
    character.equipment.amulet.flat_dr.radiant = 9;
    character.equipment.ring_01.flat_dr.radiant = 10;
    character.equipment.ring_02.flat_dr.radiant = 11;
    character.equipment.belt.flat_dr.radiant = 12;
    result = ft_calculate_radiant_dr(&character);
    test_assert_true(result == 78, "ft_calculate_radiant_dr should total all equipment slots");
    return ;
}

static void test_calculate_thunder_dr_handles_mixed_values()
{
    t_char  character = {};
    int     result;

    character.equipment.weapon.flat_dr.thunder = 2;
    character.equipment.shield.flat_dr.thunder = -5;
    character.equipment.boots.flat_dr.thunder = 3;
    character.equipment.ring_02.flat_dr.thunder = 1;
    result = ft_calculate_thunder_dr(&character);
    test_assert_true(result == 1, "ft_calculate_thunder_dr should include positive and negative equipment modifiers");
    return ;
}

static void test_calculate_cold_dr_totals_equipment()
{
    t_char  character = {};
    int     result;

    set_flat_dr_sequence(character, &t_resistance::cold);
    result = ft_calculate_cold_dr(&character);
    test_assert_true(result == 78, "ft_calculate_cold_dr should include every equipment slot");
    return ;
}

static void test_calculate_force_dr_includes_jewelry()
{
    t_char  character = {};
    int     result;

    character.equipment.amulet.flat_dr.force = 4;
    character.equipment.ring_01.flat_dr.force = 5;
    character.equipment.ring_02.flat_dr.force = 6;
    character.equipment.belt.flat_dr.force = 7;
    result = ft_calculate_force_dr(&character);
    test_assert_true(result == 22, "ft_calculate_force_dr should total jewelry contributions");
    return ;
}

static void test_calculate_necrotic_dr_handles_negative_modifiers()
{
    t_char  character = {};
    int     result;

    character.equipment.weapon.flat_dr.necrotic = -3;
    character.equipment.helmet.flat_dr.necrotic = 5;
    character.equipment.boots.flat_dr.necrotic = 1;
    result = ft_calculate_necrotic_dr(&character);
    test_assert_true(result == 3, "ft_calculate_necrotic_dr should apply negative and positive bonuses");
    return ;
}

static void test_calculate_poison_dr_totals_equipment()
{
    t_char  character = {};
    int     result;

    set_flat_dr_sequence(character, &t_resistance::poison);
    result = ft_calculate_poison_dr(&character);
    test_assert_true(result == 78, "ft_calculate_poison_dr should include bonuses from every slot");
    return ;
}

static void test_calculate_psychic_dr_handles_mixed_values()
{
    t_char  character = {};
    int     result;

    character.equipment.weapon.flat_dr.psychic = 5;
    character.equipment.amulet.flat_dr.psychic = -2;
    character.equipment.boots.flat_dr.psychic = 1;
    result = ft_calculate_psychic_dr(&character);
    test_assert_true(result == 4, "ft_calculate_psychic_dr should include positive and negative modifiers");
    return ;
}

void run_resistance_tests()
{
    test_calculate_resistance_includes_character_base();
    test_calculate_resistance_defaults_to_zero();
    test_calculate_resistance_separates_types();
    test_calculate_lightning_resistance_totals_equipment();
    test_calculate_resistance_handles_negative_modifiers();
    test_calculate_poison_resistance_handles_negative_base();
    test_calculate_damage_reduction_sums_equipment_slots();
    test_calculate_damage_reduction_ignores_character_resistance();
    test_calculate_damage_reduction_handles_negative_values();
    test_calculate_damage_reduction_defaults_to_zero();
    test_calculate_psychic_resistance_ignores_flat_damage_reduction();
    test_calculate_force_resistance_includes_jewelry();
    test_calculate_necrotic_resistance_handles_negative_equipment();
    test_calculate_radiant_dr_sums_equipment();
    test_calculate_thunder_dr_handles_mixed_values();
    test_calculate_bludgeoning_resistance_totals_equipment();
    test_calculate_slashing_resistance_handles_negative_equipment();
    test_calculate_piercing_resistance_isolates_other_types();
    test_calculate_cold_resistance_defaults_to_zero();
    test_calculate_lightning_dr_totals_equipment();
    test_calculate_bludgeoning_dr_handles_negative_values();
    test_calculate_piercing_dr_defaults_to_zero();
    test_calculate_cold_dr_totals_equipment();
    test_calculate_force_dr_includes_jewelry();
    test_calculate_necrotic_dr_handles_negative_modifiers();
    test_calculate_poison_dr_totals_equipment();
    test_calculate_psychic_dr_handles_mixed_values();
    return ;
}
