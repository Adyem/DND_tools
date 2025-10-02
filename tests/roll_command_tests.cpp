#include "test_groups.hpp"

void    run_roll_command_argument_tests();
void    run_roll_command_expression_tests();
void    run_roll_command_error_tests();

void run_roll_command_tests()
{
    run_roll_command_argument_tests();
    run_roll_command_expression_tests();
    run_roll_command_error_tests();
    return ;
}
