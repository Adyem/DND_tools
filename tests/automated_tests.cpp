#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include <cstdio>

int main()
{
    run_string_prefix_tests();
    run_ordinal_suffix_tests();
    run_roll_validation_tests();
    run_roll_command_argument_tests();
    run_roll_command_expression_tests();
    run_roll_command_error_tests();
    run_dice_roll_tests();
    run_create_data_folder_tests();
    run_add_element_tests();
    run_clean_tests();
    run_check_name_tests();
    run_check_equipment_tests();
    run_check_buff_tests();
    run_attack_utils_tests();
    run_set_debuf_tests();
    run_save_load_tests();
    run_resistance_tests();
    run_calculate_damage_reduction_tests();
    run_calculate_stats_tests();
    run_calculate_skills_tests();
    run_calculate_util_stats_tests();
    run_divine_smite_tests();
    run_spell_utils_tests();
    run_npc_check_info_tests();
    run_get_pc_list_tests();
    run_concentration_tests();
    run_deal_damage_tests();
    return (0);
}
