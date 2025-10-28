#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/Libft/libft.hpp"
#include "../libft/Errno/errno.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"

static int  g_attack_calls = 0;
static int  g_loot_calls = 0;

static void stub_weapon_attack(t_char * info, t_equipment_id *weapon, int offhand)
{
    (void)info;
    (void)weapon;
    (void)offhand;
    g_attack_calls = g_attack_calls + 1;
    return ;
}

static void stub_drop_loot(t_char * info)
{
    (void)info;
    g_loot_calls = g_loot_calls + 1;
    return ;
}

static void initialize_character(t_char *info)
{
    if (info == ft_nullptr)
        return ;
    ft_bzero(info, sizeof(t_char));
    info->name = "Test NPC";
    info->physical.speed = 30;
    return ;
}

static void test_npc_execute_command_runs_weapon_attack()
{
    const char  *input[] = {"npc", "attack", ft_nullptr};
    t_char      info;
    t_npc_command_status    status;

    initialize_character(&info);
    info.equipment.weapon.attack.function = &stub_weapon_attack;
    g_attack_calls = 0;
    status = ft_npc_execute_command(&info, input);
    test_assert_true(status == FT_NPC_COMMAND_HANDLED,
        "ft_npc_execute_command should handle weapon attack commands");
    test_assert_true(g_attack_calls == 1,
        "ft_npc_execute_command should call the assigned weapon attack handler");
    return ;
}

static void test_npc_execute_command_dispatches_loot()
{
    const char  *input[] = {"npc", "loot", ft_nullptr};
    t_char      info;
    t_npc_command_status    status;

    initialize_character(&info);
    info.drop_loot = &stub_drop_loot;
    g_loot_calls = 0;
    status = ft_npc_execute_command(&info, input);
    test_assert_true(status == FT_NPC_COMMAND_HANDLED,
        "ft_npc_execute_command should handle loot commands");
    test_assert_true(g_loot_calls == 1,
        "ft_npc_execute_command should call the configured loot handler");
    return ;
}

static void test_npc_execute_command_handles_skill_roll()
{
    const char  *input[] = {"npc", "athletics", ft_nullptr};
    t_char      info;
    t_npc_command_status    status;

    initialize_character(&info);
    status = ft_npc_execute_command(&info, input);
    test_assert_true(status == FT_NPC_COMMAND_HANDLED,
        "ft_npc_execute_command should route known skills through the skill map");
    return ;
}

static void test_npc_execute_command_reports_unknown_command()
{
    const char  *input[] = {"npc", "unknown", ft_nullptr};
    t_char      info;
    t_npc_command_status    status;

    initialize_character(&info);
    status = ft_npc_execute_command(&info, input);
    test_assert_true(status == FT_NPC_COMMAND_NOT_FOUND,
        "ft_npc_execute_command should report unknown commands");
    return ;
}

static void test_npc_execute_command_rejects_null_input()
{
    t_char  info;
    t_npc_command_status    status;

    initialize_character(&info);
    status = ft_npc_execute_command(&info, ft_nullptr);
    test_assert_true(status == FT_NPC_COMMAND_ERROR,
        "ft_npc_execute_command should reject null command arrays");
    test_assert_true(ft_errno == FT_ERR_INVALID_ARGUMENT,
        "ft_npc_execute_command should set errno for invalid arguments");
    return ;
}

void    run_npc_command_tests()
{
    test_begin_suite("npc_command_tests");
    test_npc_execute_command_runs_weapon_attack();
    test_npc_execute_command_dispatches_loot();
    test_npc_execute_command_handles_skill_roll();
    test_npc_execute_command_reports_unknown_command();
    test_npc_execute_command_rejects_null_input();
    test_end_suite_success();
    return ;
}
