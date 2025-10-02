#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../treeNode.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_file.hpp"
#include "../libft/JSon/document.hpp"
#include <filesystem>
#include <system_error>
#include <cstring>
#include <cstdlib>
#include <string>
#include <fcntl.h>

static void ensure_tests_output_directory()
{
    std::error_code error_code;
    std::filesystem::create_directories("tests_output", error_code);
    test_assert_true(error_code.value() == 0, "Failed to create tests_output directory");
    return ;
}

static char *duplicate_line(const char *value)
{
    size_t length;
    char *copy;

    if (!value)
        return (ft_nullptr);
    length = std::strlen(value);
    copy = static_cast<char *>(std::malloc(length + 1));
    if (!copy)
        return (ft_nullptr);
    std::memcpy(copy, value, length + 1);
    return (copy);
}

static char **load_json_lines_from_file(const std::string &file_path)
{
    json_document document;
    json_group *lines_group;
    json_item *item;
    size_t count;
    char **content;
    size_t index;

    if (document.read_from_file(file_path.c_str()) != 0)
        return (ft_nullptr);
    lines_group = document.find_group("lines");
    if (!lines_group)
        return (ft_nullptr);
    count = 0;
    item = lines_group->items;
    while (item)
    {
        count++;
        item = item->next;
    }
    content = static_cast<char **>(std::malloc(sizeof(char *) * (count + 1)));
    if (!content)
        return (ft_nullptr);
    index = 0;
    item = lines_group->items;
    while (item)
    {
        content[index] = duplicate_line(item->value);
        if (!content[index])
        {
            content[index] = ft_nullptr;
            size_t cleanup_index = 0;
            while (content[cleanup_index])
            {
                std::free(content[cleanup_index]);
                cleanup_index++;
            }
            std::free(content);
            return (ft_nullptr);
        }
        index++;
        item = item->next;
    }
    content[index] = ft_nullptr;
    return (content);
}

static void free_json_lines(char **content)
{
    size_t index;

    if (!content)
        return ;
    index = 0;
    while (content[index])
    {
        std::free(content[index]);
        index++;
    }
    std::free(content);
    return ;
}

static bool lines_contains_line(char **content, const char *expected)
{
    size_t index;

    if (!content || !expected)
        return (false);
    index = 0;
    while (content[index])
    {
        if (std::strcmp(content[index], expected) == 0)
            return (true);
        index++;
    }
    return (false);
}

static void cleanup_loaded_npc(t_char &npc)
{
    npc.bufs.bless.caster_name.clear();
    npc.debufs.hunters_mark.caster_name.clear();
    npc.debufs.magic_drain.caster.clear();
    cma_free_double(npc.concentration.targets);
    npc.concentration.targets = ft_nullptr;
    cma_free(npc.bufs.meteor_strike.target_id);
    npc.bufs.meteor_strike.target_id = ft_nullptr;
    cma_free(npc.bufs.frost_breath.target_id);
    npc.bufs.frost_breath.target_id = ft_nullptr;
    cma_free(npc.bufs.arcane_pounce.target_id);
    npc.bufs.arcane_pounce.target_id = ft_nullptr;
    cma_free(npc.bufs.earth_pounce.target_id);
    npc.bufs.earth_pounce.target_id = ft_nullptr;
    cma_free(npc.loot.equipment);
    npc.loot.equipment = ft_nullptr;
    cma_free(npc.loot.items);
    npc.loot.items = ft_nullptr;
    cma_free(npc.spells.magic_drain.target);
    npc.spells.magic_drain.target = ft_nullptr;
    cma_free(npc.save_file);
    npc.save_file = ft_nullptr;
    return ;
}

static void test_npc_set_stats_player_entry_failure_sets_error()
{
    t_char npc = {};
    char *content[2];
    int parse_error;

    npc.name = const_cast<char *>("Test NPC");
    content[0] = const_cast<char *>("SPELL_MAGIC_DRAIN=INVALID_PLAYER_ENTRY");
    content[1] = ft_nullptr;
    parse_error = ft_set_stats(&npc, content);
    test_assert_true(parse_error == 1, "ft_set_stats did not report failure when player entry validation failed");
    test_assert_true(npc.flags.error == 1, "ft_set_stats did not set the NPC error flag when player entry validation failed");
    if (npc.spells.magic_drain.target)
    {
        cma_free(npc.spells.magic_drain.target);
        npc.spells.magic_drain.target = ft_nullptr;
    }
    ft_cleanup_treeNode();
    return ;
}

static void test_npc_json_save_writes_lines()
{
    ensure_tests_output_directory();
    std::string file_path = "tests_output/npc_json_save_fixture.json";
    t_char npc = {};
    t_stats stats = {};
    t_resistance resistances = {};
    ft_file file(file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    char **content;

    npc.name = const_cast<char *>("Test NPC");
    stats.health = 42;
    npc.dstats.health = 50;
    npc.initiative = 9;
    npc.position.x = 4;
    npc.position.y = 5;
    npc.position.z = 6;
    resistances.acid = 3;
    npc.concentration.concentration = 1;
    npc.concentration.duration = 2;
    npc.debufs.hunters_mark.amount = 7;
    npc.bufs.bless.duration = 8;

    test_assert_true(file.get_error() == 0, "Failed to open NPC save file for writing");
    ft_npc_write_file(&npc, &stats, &resistances, file);
    file.close();
    test_assert_true(npc.flags.alreaddy_saved == 1, "NPC save did not mark character as saved");

    content = load_json_lines_from_file(file_path);
    test_assert_true(content != ft_nullptr, "Failed to read JSON lines from NPC save");
    test_assert_true(lines_contains_line(content, "HEALTH=42"), "NPC save JSON missing health line");
    test_assert_true(lines_contains_line(content, "MAX_HEALTH=50"), "NPC save JSON missing max health line");
    test_assert_true(lines_contains_line(content, "INITIATIVE=9"), "NPC save JSON missing initiative line");
    test_assert_true(lines_contains_line(content, "POSITION_X=4"), "NPC save JSON missing position X line");
    test_assert_true(lines_contains_line(content, "POSITION_Y=5"), "NPC save JSON missing position Y line");
    test_assert_true(lines_contains_line(content, "POSITION_Z=6"), "NPC save JSON missing position Z line");
    test_assert_true(lines_contains_line(content, "ACID_RESISTANCE=3"), "NPC save JSON missing acid resistance line");
    test_assert_true(lines_contains_line(content, "CONCENTRATION=1"), "NPC save JSON missing concentration line");
    test_assert_true(lines_contains_line(content, "CONC_DURATION=2"), "NPC save JSON missing concentration duration line");
    test_assert_true(lines_contains_line(content, "HUNTERS_MARK_AMOUNT=7"), "NPC save JSON missing hunter's mark line");
    test_assert_true(lines_contains_line(content, "BUFF_BLESS_DURATION=8"), "NPC save JSON missing bless duration line");

    free_json_lines(content);
    std::filesystem::remove(file_path);
    cleanup_loaded_npc(npc);
    return ;
}

static void test_npc_json_load_populates_fields()
{
    ensure_tests_output_directory();
    std::string file_path = "tests_output/npc_json_load_fixture.json";
    json_document document;
    json_group *group;
    t_char loaded = {};
    int write_error;

    group = document.create_group("lines");
    test_assert_true(group != ft_nullptr, "Failed to allocate JSON group for NPC load test");
    document.append_group(group);
    json_item *line_item;

    line_item = document.create_item("0", "HEALTH=42");
    test_assert_true(line_item != ft_nullptr, "Failed to build health line for NPC load test");
    document.add_item(group, line_item);
    line_item = document.create_item("1", "MAX_HEALTH=50");
    test_assert_true(line_item != ft_nullptr, "Failed to build max health line for NPC load test");
    document.add_item(group, line_item);
    line_item = document.create_item("2", "INITIATIVE=9");
    test_assert_true(line_item != ft_nullptr, "Failed to build initiative line for NPC load test");
    document.add_item(group, line_item);
    line_item = document.create_item("3", "POSITION_X=4");
    test_assert_true(line_item != ft_nullptr, "Failed to build position X line for NPC load test");
    document.add_item(group, line_item);
    line_item = document.create_item("4", "POSITION_Y=5");
    test_assert_true(line_item != ft_nullptr, "Failed to build position Y line for NPC load test");
    document.add_item(group, line_item);
    line_item = document.create_item("5", "POSITION_Z=6");
    test_assert_true(line_item != ft_nullptr, "Failed to build position Z line for NPC load test");
    document.add_item(group, line_item);

    write_error = document.write_to_file(file_path.c_str());
    test_assert_true(write_error == 0, "Failed to write NPC load test JSON fixture");

    loaded.name = const_cast<char *>("Test NPC");
    loaded.save_file = cma_strdup(file_path.c_str());
    test_assert_true(loaded.save_file != ft_nullptr, "Failed to duplicate NPC load file path");
    int open_error = ft_npc_open_file(&loaded);
    test_assert_true(open_error == 0, "Failed to load NPC from JSON fixture");
    test_assert_true(loaded.stats.health == 42, "NPC load did not restore health from JSON file");
    test_assert_true(loaded.dstats.health == 50, "NPC load did not restore max health from JSON file");
    test_assert_true(loaded.initiative == 9, "NPC load did not restore initiative from JSON file");
    test_assert_true(loaded.position.x == 4, "NPC load did not restore position X from JSON file");
    test_assert_true(loaded.position.y == 5, "NPC load did not restore position Y from JSON file");
    test_assert_true(loaded.position.z == 6, "NPC load did not restore position Z from JSON file");

    cleanup_loaded_npc(loaded);
    ft_cleanup_treeNode();
    std::filesystem::remove(file_path);
    return ;
}

static void test_player_json_save_and_load()
{
    ensure_tests_output_directory();
    std::string file_path = "tests_output/player_json_round_trip.json";
    t_pc player = {};
    ft_file file(file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    int write_error;
    char **content;
    t_pc parsed = {};
    int parse_error;

    player.name = const_cast<char *>("Player One");
    player.initiative = 15;
    player.position.x = 7;
    player.position.y = 3;
    player.position.z = 11;

    write_error = file.get_error();
    test_assert_true(write_error == 0, "Failed to open player save file for writing");
    ft_save_pc(&player, file);
    file.close();

    content = load_json_lines_from_file(file_path);
    test_assert_true(content != ft_nullptr, "Failed to read JSON lines from player save");

    parse_error = ft_check_stat_pc(&parsed, content, const_cast<char *>("PC--Player One"));
    test_assert_true(parse_error == 0, "Failed to parse player data from JSON save");
    test_assert_true(parsed.name != ft_nullptr, "Player name was not restored from JSON save");
    if (parsed.name)
        test_assert_true(std::strcmp(parsed.name, "Player One") == 0, "Player name did not round-trip through JSON save");
    test_assert_true(parsed.initiative == player.initiative, "Player initiative did not round-trip through JSON save");
    test_assert_true(parsed.position.x == player.position.x, "Player position X did not round-trip through JSON save");
    test_assert_true(parsed.position.y == player.position.y, "Player position Y did not round-trip through JSON save");
    test_assert_true(parsed.position.z == player.position.z, "Player position Z did not round-trip through JSON save");

    if (parsed.name)
    {
        cma_free(parsed.name);
        parsed.name = ft_nullptr;
    }
    free_json_lines(content);
    std::filesystem::remove(file_path);
    return ;
}

void run_save_load_tests()
{
    test_npc_set_stats_player_entry_failure_sets_error();
    test_npc_json_save_writes_lines();
    test_npc_json_load_populates_fields();
    test_player_json_save_and_load();
    return ;
}
