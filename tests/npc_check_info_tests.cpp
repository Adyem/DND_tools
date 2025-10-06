#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include <string>

static void configure_valid_character(t_char &character)
{
    character.name = "Valid NPC";
    character.dstats.health = 40;
    character.stats.health = 30;
    character.stats.temp_hp = 5;
    character.stats.turn = 4;
    character.stats.phase = 2;
    character.initiative = 3;
    character.position.x = 10;
    character.position.y = 15;
    character.position.z = 1;
    character.spell_slots.level_1.total = 3;
    character.spell_slots.level_1.available = 3;
    character.spell_slots.level_1.level = 0;
    character.spell_slots.level_2.total = 0;
    character.spell_slots.level_2.available = 0;
    character.spell_slots.level_2.level = 0;
    character.spell_slots.level_3.total = 0;
    character.spell_slots.level_3.available = 0;
    character.spell_slots.level_3.level = 0;
    character.spell_slots.level_4.total = 0;
    character.spell_slots.level_4.available = 0;
    character.spell_slots.level_4.level = 0;
    character.spell_slots.level_5.total = 0;
    character.spell_slots.level_5.available = 0;
    character.spell_slots.level_5.level = 0;
    character.spell_slots.level_6.total = 0;
    character.spell_slots.level_6.available = 0;
    character.spell_slots.level_6.level = 0;
    character.spell_slots.level_7.total = 0;
    character.spell_slots.level_7.available = 0;
    character.spell_slots.level_7.level = 0;
    character.spell_slots.level_8.total = 0;
    character.spell_slots.level_8.available = 0;
    character.spell_slots.level_8.level = 0;
    character.spell_slots.level_9.total = 0;
    character.spell_slots.level_9.available = 0;
    character.spell_slots.level_9.level = 0;
    character.spell_slots.warlock.level = 3;
    character.spell_slots.warlock.total = 2;
    character.spell_slots.warlock.available = 2;
    character.spell_slots.warlock.replenishing_slot = 0;
    character.bufs.bless.duration = 5;
    character.bufs.bless.dice_amount_mod = 0;
    character.bufs.bless.dice_faces_mod = 0;
    character.bufs.bless.base_mod = 0;
    character.bufs.bless.caster_name.clear();
    character.bufs.protective_winds.duration = 0;
    character.bufs.lightning_strike.duration = 3;
    character.bufs.lightning_strike.amount = 4;
    character.bufs.lightning_strike.distance = 25;
    character.bufs.lightning_strike.dice_amount = 2;
    character.bufs.lightning_strike.dice_faces = 6;
    character.bufs.lightning_strike.extra_damage = 5;
    character.bufs.lightning_strikeV2.duration = 0;
    character.bufs.lightning_strikeV2.amount = 0;
    character.bufs.lightning_strikeV2.distance = 0;
    character.bufs.lightning_strikeV2.dice_amount = 0;
    character.bufs.lightning_strikeV2.dice_faces = 0;
    character.bufs.lightning_strikeV2.extra_damage = 0;
    character.bufs.flame_geyser.amount = 0;
    character.bufs.flame_geyser.duration = 0;
    character.bufs.flame_geyser.close_to_tower_d = 0;
    character.bufs.flame_geyser.tower_explode_d = 0;
    character.bufs.meteor_strike.duration = 0;
    character.bufs.meteor_strike.one_target_d = 0;
    character.bufs.meteor_strike.two_targets_d = 0;
    character.bufs.meteor_strike.three_targets_d = 0;
    character.bufs.meteor_strike.four_targets_d = 0;
    character.bufs.meteor_strike.five_targets_d = 0;
    character.bufs.meteor_strike.target_id = ft_nullptr;
    character.bufs.chaos_armor.duration = 0;
    character.bufs.arcane_pounce.active = 0;
    character.bufs.arcane_pounce.magic_damage = 0;
    character.bufs.arcane_pounce.erea_damage = 0;
    character.bufs.arcane_pounce.target_id = ft_nullptr;
    character.bufs.earth_pounce.active = 0;
    character.bufs.earth_pounce.base_damage = 0;
    character.bufs.earth_pounce.target_id = ft_nullptr;
    character.bufs.frost_breath.active = 0;
    character.bufs.frost_breath.damage = 0;
    character.bufs.frost_breath.target_id = ft_nullptr;
    character.bufs.shadow_illusion.active = 0;
    character.bufs.shadow_illusion.duration = 0;
    character.bufs.growth.stacks = 2;
    character.bufs.rejuvenation.duration = 0;
    character.bufs.rejuvenation.healing_dice_amount = 0;
    character.bufs.rejuvenation.healing_dice_faces = 0;
    character.bufs.rejuvenation.healing_extra = 0;
    character.debufs.hunters_mark.amount = 0;
    character.debufs.hunters_mark.caster_name.clear();
    character.debufs.blinded.duration = 0;
    character.debufs.magic_drain.caster.clear();
    character.debufs.magic_drain.amount = 0;
    character.debufs.magic_drain.damage_flat = 0;
    character.debufs.magic_drain.damage_dice_amount = 0;
    character.debufs.magic_drain.damage_dice_faces = 0;
    character.debufs.magic_drain.extra_damage_flat = 0;
    character.debufs.magic_drain.extra_dice_amount = 0;
    character.debufs.magic_drain.extra_dice_faces = 0;
    character.debufs.magic_drain.spell_slot_total_level_drain = 0;
    character.debufs.magic_drain.con_save = 0;
    character.debufs.fell_poison.duration = 0;
    character.debufs.shadow_touched.duration = 0;
    character.debufs.shadow_touched.stacks = 0;
    character.debufs.shadow_touched.armor_reduction_amount = 0;
    character.concentration.concentration = 0;
    character.concentration.spell_id = 0;
    character.concentration.dice_amount_mod = 0;
    character.concentration.dice_faces_mod = 0;
    character.concentration.base_mod = 0;
    character.concentration.duration = 0;
    character.concentration.targets = ft_nullptr;
    character.flags.prone = 0;
    character.flags.reaction_used = 0;
    character.flags.advantage = 0;
    character.flags.alreaddy_saved = 0;
    character.d_resistance = {};
    character.c_resistance = {};
    return ;
}

static void test_npc_check_info_accepts_valid_character()
{
    t_char character = {};
    configure_valid_character(character);
    int result;

    result = ft_npc_check_info(&character);
    test_assert_true(result == 0, "ft_npc_check_info should accept in-range character data");
    return ;
}

static void test_npc_check_info_detects_health_above_max()
{
    t_char character = {};
    int result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    configure_valid_character(character);
    character.stats.health = 41;
    file_path = "tests_output/npc_check_info_health.log";
    test_begin_output_capture(file_path);
    result = ft_npc_check_info(&character);
    test_end_output_capture();
    test_assert_true(result > 0, "ft_npc_check_info should report health values above maximum");
    error_output = test_read_file_to_string(file_path);
    expected_message = "Valid NPC: health value (41) out of bounds (0 to 40)\n"
        "Valid NPC: Error with the save file, please reinitialize it with the correct values\n";
    test_assert_true(error_output == expected_message,
        "ft_npc_check_info should log health overflow details");
    test_delete_file(file_path);
    return ;
}

static void test_npc_check_info_detects_spell_slot_overflow()
{
    t_char character = {};
    int result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    configure_valid_character(character);
    character.spell_slots.level_1.available = 4;
    file_path = "tests_output/npc_check_info_spell_slots.log";
    test_begin_output_capture(file_path);
    result = ft_npc_check_info(&character);
    test_end_output_capture();
    test_assert_true(result == 1, "ft_npc_check_info should flag spell slot availability above total");
    error_output = test_read_file_to_string(file_path);
    expected_message = "Valid NPC: Available slots (4) for level_1 are out of range (0 to 3)\n"
        "Valid NPC: Error with the save file, please reinitialize it with the correct values\n";
    test_assert_true(error_output == expected_message,
        "ft_npc_check_info should log spell slot overflow details");
    test_delete_file(file_path);
    return ;
}

static void test_npc_check_info_detects_warlock_level_mismatch()
{
    t_char character = {};
    int result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    configure_valid_character(character);
    character.spell_slots.warlock.level = 0;
    file_path = "tests_output/npc_check_info_warlock.log";
    test_begin_output_capture(file_path);
    result = ft_npc_check_info(&character);
    test_end_output_capture();
    test_assert_true(result == 1, "ft_npc_check_info should require warlock slot level when slots exist");
    error_output = test_read_file_to_string(file_path);
    expected_message = "Valid NPC: Warlock slot level is 0, but total (2) or available (2) slots are not 0\n"
        "Valid NPC: Error with the save file, please reinitialize it with the correct values\n";
    test_assert_true(error_output == expected_message,
        "ft_npc_check_info should log warlock slot validation errors");
    test_delete_file(file_path);
    return ;
}

static void test_npc_check_info_detects_resistance_out_of_bounds()
{
    t_char character = {};
    int result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    configure_valid_character(character);
    character.c_resistance.fire = 600;
    file_path = "tests_output/npc_check_info_resistance.log";
    test_begin_output_capture(file_path);
    result = ft_npc_check_info(&character);
    test_end_output_capture();
    test_assert_true(result == 1, "ft_npc_check_info should clamp resistances to allowed range");
    error_output = test_read_file_to_string(file_path);
    expected_message = "Valid NPC: fire resistance value (600) out of bounds (-500 to 500)\n"
        "Valid NPC: Error with the save file, please reinitialize it with the correct values\n";
    test_assert_true(error_output == expected_message,
        "ft_npc_check_info should log resistance range errors");
    test_delete_file(file_path);
    return ;
}

static void test_npc_check_info_detects_hunters_mark_mismatch()
{
    t_char character = {};
    int result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    configure_valid_character(character);
    character.debufs.hunters_mark.amount = 1;
    file_path = "tests_output/npc_check_info_hunters_mark.log";
    test_begin_output_capture(file_path);
    result = ft_npc_check_info(&character);
    test_end_output_capture();
    test_assert_true(result == 1, "ft_npc_check_info should validate hunters mark caster tracking");
    error_output = test_read_file_to_string(file_path);
    expected_message = "Valid NPC: hunters mark data is not correct\n"
        "Valid NPC: Error with the save file, please reinitialize it with the correct values\n";
    test_assert_true(error_output == expected_message,
        "ft_npc_check_info should log hunter's mark mismatches");
    test_delete_file(file_path);
    return ;
}

void    run_npc_check_info_tests()
{
    test_npc_check_info_accepts_valid_character();
    test_npc_check_info_detects_health_above_max();
    test_npc_check_info_detects_spell_slot_overflow();
    test_npc_check_info_detects_warlock_level_mismatch();
    test_npc_check_info_detects_resistance_out_of_bounds();
    test_npc_check_info_detects_hunters_mark_mismatch();
    return ;
}
