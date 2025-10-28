#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Libft/libft.hpp"

static char **duplicate_lines(const char **lines)
{
    size_t  count;
    size_t  index;
    char    **copy;

    count = 0;
    while (lines[count])
        count++;
    copy = static_cast<char **>(cma_calloc(count + 1, sizeof(char *)));
    test_assert_true(copy != ft_nullptr,
        "duplicate_lines should allocate line array");
    index = 0;
    while (index < count)
    {
        copy[index] = cma_strdup(lines[index]);
        test_assert_true(copy[index] != ft_nullptr,
            "duplicate_lines should duplicate source line");
        index++;
    }
    copy[count] = ft_nullptr;
    return (copy);
}

static void free_lines(char **lines)
{
    if (!lines)
        return ;
    cma_free_double(lines);
    return ;
}

static void test_initiative_players_am_builds_list_from_entries()
{
    const char  *lines[] = {"--turn--Alice=18\n", "Bob=14\n", ft_nullptr};
    char        **content;
    t_pc        *players;
    t_pc        *second;

    content = duplicate_lines(lines);
    players = ft_initiative_players_am(content);
    test_assert_true(players != ft_nullptr,
        "ft_initiative_players_am should return a player list for valid input");
    test_assert_true(ft_strcmp(players->name, "--turn--Alice") == 0,
        "ft_initiative_players_am should keep player names from the input lines");
    test_assert_true(players->initiative == 18,
        "ft_initiative_players_am should parse initiative values");
    second = players->next;
    test_assert_true(second != ft_nullptr,
        "ft_initiative_players_am should link subsequent players");
    test_assert_true(ft_strcmp(second->name, "Bob") == 0,
        "ft_initiative_players_am should populate additional entries");
    test_assert_true(second->initiative == 14,
        "ft_initiative_players_am should parse later initiative values");
    ft_free_players(players);
    free_lines(content);
    return ;
}

static void test_initiative_players_am_reports_invalid_values()
{
    const char  *lines[] = {"Alice=not_a_number\n", ft_nullptr};
    char        **content;
    t_pc        *players;

    content = duplicate_lines(lines);
    players = ft_initiative_players_am(content);
    test_assert_true(players == ft_nullptr,
        "ft_initiative_players_am should fail when initiative is not numeric");
    free_lines(content);
    return ;
}

static void test_initiative_players_am_reports_missing_separator()
{
    const char  *lines[] = {"Alice 12\n", ft_nullptr};
    char        **content;
    t_pc        *players;

    content = duplicate_lines(lines);
    players = ft_initiative_players_am(content);
    test_assert_true(players == ft_nullptr,
        "ft_initiative_players_am should fail when input line lacks '='");
    free_lines(content);
    return ;
}

void    run_initiative_sort_tests()
{
    test_begin_suite("initiative_sort_tests");
    test_initiative_players_am_builds_list_from_entries();
    test_initiative_players_am_reports_invalid_values();
    test_initiative_players_am_reports_missing_separator();
    test_end_suite_success();
    return ;
}
