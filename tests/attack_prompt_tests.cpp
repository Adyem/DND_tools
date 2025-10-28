#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../character.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"
#include "../libft/Template/vector.hpp"

static void test_collect_known_spells_rejects_null_character()
{
    ft_vector<t_known_spell>    spells(1);
    int                         result;

    result = ft_collect_known_spells(ft_nullptr, spells);
    test_assert_true(result == -1,
        "ft_collect_known_spells should fail when the character pointer is null");
    test_assert_true(ft_errno == FT_ERR_INVALID_ARGUMENT,
        "ft_collect_known_spells should set ft_errno to FT_ERR_INVALID_ARGUMENT on null character");
    return ;
}

static void test_collect_known_spells_populates_divine_smite()
{
    t_char                      character = {};
    ft_vector<t_known_spell>    spells(2);
    int                         result;
    size_t                      count;
    const t_known_spell         *spell;

    character.spells.divine_smite.learned = 1;
    ft_errno = FT_ERR_IO;
    result = ft_collect_known_spells(&character, spells);
    test_assert_true(result == 0,
        "ft_collect_known_spells should populate spells when a valid character is provided");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_collect_known_spells should reset ft_errno to ER_SUCCESS after success");
    count = spells.size();
    test_assert_true(spells.get_error() == ER_SUCCESS,
        "ft_collect_known_spells should not leave the vector in an error state after size()");
    test_assert_true(count == 1,
        "ft_collect_known_spells should add exactly one spell entry for the current feature set");
    spell = &spells[0];
    test_assert_true(spells.get_error() == ER_SUCCESS,
        "ft_collect_known_spells should allow indexed access without triggering vector errors");
    test_assert_true(ft_strcmp(spell->cmd, "divine_smite") == 0,
        "ft_collect_known_spells should register divine_smite as the available spell");
    test_assert_true(spell->learned == &character.spells.divine_smite.learned,
        "ft_collect_known_spells should expose the learned flag from the character");
    test_assert_true(spell->cast_func == ft_cast_divine_smite,
        "ft_collect_known_spells should expose the divine smite cast function");
    return ;
}

static void test_collect_known_spells_clears_existing_entries()
{
    t_char                      character = {};
    ft_vector<t_known_spell>    spells(2);
    t_known_spell               placeholder;
    int                         result;
    size_t                      count;
    const t_known_spell         *spell;

    placeholder.cmd = "placeholder";
    placeholder.learned = ft_nullptr;
    placeholder.cast_func = ft_cast_divine_smite;
    spells.push_back(placeholder);
    test_assert_true(spells.get_error() == ER_SUCCESS,
        "The test setup should allow pushing a placeholder spell into the vector");
    spells.push_back(placeholder);
    test_assert_true(spells.get_error() == ER_SUCCESS,
        "The test setup should allow pushing a second placeholder spell into the vector");
    character.spells.divine_smite.learned = 0;
    result = ft_collect_known_spells(&character, spells);
    test_assert_true(result == 0,
        "ft_collect_known_spells should succeed even when the learned flag is not set");
    count = spells.size();
    test_assert_true(spells.get_error() == ER_SUCCESS,
        "ft_collect_known_spells should leave the vector usable after size()");
    test_assert_true(count == 1,
        "ft_collect_known_spells should clear previous entries before inserting the current spell list");
    spell = &spells[0];
    test_assert_true(spells.get_error() == ER_SUCCESS,
        "ft_collect_known_spells should provide indexed access after clearing old entries");
    test_assert_true(ft_strcmp(spell->cmd, "divine_smite") == 0,
        "ft_collect_known_spells should replace placeholder entries with the real spell metadata");
    return ;
}

static void test_attack_prompt_parse_rejects_null_arguments()
{
    int result;

    result = -1;
    ft_errno = ER_SUCCESS;
    test_assert_true(ft_attack_prompt_parse_response(ft_nullptr, &result) == FT_FAILURE,
        "ft_attack_prompt_parse_response should fail when the input is null");
    test_assert_true(ft_errno == FT_ERR_INVALID_ARGUMENT,
        "ft_attack_prompt_parse_response should set ft_errno to FT_ERR_INVALID_ARGUMENT when the input is null");
    ft_errno = ER_SUCCESS;
    test_assert_true(ft_attack_prompt_parse_response("hit", ft_nullptr) == FT_FAILURE,
        "ft_attack_prompt_parse_response should fail when the result pointer is null");
    test_assert_true(ft_errno == FT_ERR_INVALID_ARGUMENT,
        "ft_attack_prompt_parse_response should set ft_errno to FT_ERR_INVALID_ARGUMENT when the result pointer is null");
    return ;
}

static void test_attack_prompt_parse_accepts_hit_synonyms()
{
    int result;

    ft_errno = FT_ERR_IO;
    test_assert_true(ft_attack_prompt_parse_response("Yes", &result) == FT_SUCCESS,
        "ft_attack_prompt_parse_response should accept 'Yes' as a valid hit response");
    test_assert_true(result == 0,
        "ft_attack_prompt_parse_response should map affirmative responses to a hit result");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_attack_prompt_parse_response should reset ft_errno to ER_SUCCESS on success");
    ft_errno = FT_ERR_IO;
    test_assert_true(ft_attack_prompt_parse_response("HIT", &result) == FT_SUCCESS,
        "ft_attack_prompt_parse_response should accept uppercase hit responses");
    test_assert_true(result == 0,
        "ft_attack_prompt_parse_response should normalize uppercase hit responses");
    return ;
}

static void test_attack_prompt_parse_accepts_miss_and_exit()
{
    int result;

    ft_errno = FT_ERR_IO;
    test_assert_true(ft_attack_prompt_parse_response("No", &result) == FT_SUCCESS,
        "ft_attack_prompt_parse_response should accept 'No' as a miss response");
    test_assert_true(result == 1,
        "ft_attack_prompt_parse_response should map negative responses to a miss result");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_attack_prompt_parse_response should clear ft_errno after parsing a miss response");
    ft_errno = FT_ERR_IO;
    test_assert_true(ft_attack_prompt_parse_response("Quit", &result) == FT_SUCCESS,
        "ft_attack_prompt_parse_response should accept 'Quit' as an exit response");
    test_assert_true(result == 2,
        "ft_attack_prompt_parse_response should map exit synonyms to the exit outcome");
    return ;
}

static void test_attack_prompt_parse_rejects_unknown_responses()
{
    int result;

    result = -1;
    ft_errno = ER_SUCCESS;
    test_assert_true(ft_attack_prompt_parse_response("maybe", &result) == FT_FAILURE,
        "ft_attack_prompt_parse_response should reject unknown responses");
    test_assert_true(ft_errno == FT_ERR_INVALID_ARGUMENT,
        "ft_attack_prompt_parse_response should set ft_errno to FT_ERR_INVALID_ARGUMENT on unknown responses");
    test_assert_true(result == -1,
        "ft_attack_prompt_parse_response should not modify the result on failure");
    return ;
}

void    run_attack_prompt_tests()
{
    test_begin_suite("attack_prompt_tests");
    test_collect_known_spells_rejects_null_character();
    test_collect_known_spells_populates_divine_smite();
    test_collect_known_spells_clears_existing_entries();
    test_attack_prompt_parse_rejects_null_arguments();
    test_attack_prompt_parse_accepts_hit_synonyms();
    test_attack_prompt_parse_accepts_miss_and_exit();
    test_attack_prompt_parse_rejects_unknown_responses();
    test_end_suite_success();
    return ;
}
