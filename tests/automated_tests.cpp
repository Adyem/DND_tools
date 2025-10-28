#include "test_groups.hpp"
#include "test_support.hpp"
#define TEST_MODULE "DND Tools"
#include "../libft/System_utils/test_runner.hpp"

#define REGISTER_SUITE(function_name, description) \
    FT_TEST(function_name##_suite, description) \
    { \
        return (test_run_suite(function_name)); \
    }

REGISTER_SUITE(run_string_prefix_tests, "string prefix tests");
REGISTER_SUITE(run_ordinal_suffix_tests, "ordinal suffix tests");
REGISTER_SUITE(run_roll_validation_tests, "roll validation tests");
REGISTER_SUITE(run_roll_command_argument_tests, "roll command argument tests");
REGISTER_SUITE(run_roll_command_expression_tests, "roll command expression tests");
REGISTER_SUITE(run_roll_command_error_tests, "roll command error tests");
REGISTER_SUITE(run_dice_roll_tests, "dice roll tests");
REGISTER_SUITE(run_create_data_folder_tests, "create data folder tests");
REGISTER_SUITE(run_add_element_tests, "add element tests");
REGISTER_SUITE(run_clean_tests, "clean tests");
REGISTER_SUITE(run_check_name_tests, "check name tests");
REGISTER_SUITE(run_check_equipment_tests, "check equipment tests");
REGISTER_SUITE(run_check_buff_tests, "check buff tests");
REGISTER_SUITE(run_attack_utils_tests, "attack utils tests");
REGISTER_SUITE(run_attack_prompt_tests, "attack prompt tests");
REGISTER_SUITE(run_set_debuf_tests, "set debuf tests");
REGISTER_SUITE(run_save_load_tests, "save load tests");
REGISTER_SUITE(run_resistance_tests, "resistance tests");
REGISTER_SUITE(run_calculate_damage_reduction_tests, "damage reduction tests");
REGISTER_SUITE(run_calculate_stats_tests, "calculate stats tests");
REGISTER_SUITE(run_calculate_skills_tests, "calculate skills tests");
REGISTER_SUITE(run_calculate_util_stats_tests, "calculate util stats tests");
REGISTER_SUITE(run_divine_smite_tests, "divine smite tests");
REGISTER_SUITE(run_spell_utils_tests, "spell utils tests");
REGISTER_SUITE(run_npc_check_info_tests, "npc check info tests");
REGISTER_SUITE(run_get_pc_list_tests, "get pc list tests");
REGISTER_SUITE(run_concentration_tests, "concentration tests");
REGISTER_SUITE(run_deal_damage_tests, "deal damage tests");
REGISTER_SUITE(run_initiative_sort_tests, "initiative sort tests");
REGISTER_SUITE(run_command_builtin_tests, "command builtin tests");
REGISTER_SUITE(run_npc_command_tests, "npc command tests");

int main(void)
{
    return (ft_run_registered_tests());
}
