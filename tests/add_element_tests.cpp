#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"

static void free_const_array(const char **array)
{
    void    *mutable_ptr;

    if (array == NULL)
        return ;
    mutable_ptr = const_cast<void *>(static_cast<const void *>(array));
    cma_free(mutable_ptr);
    return ;
}

static void test_add_element_allocates_array_for_first_entry()
{
    const char  **array;
    const char  *expected;

    array = NULL;
    ft_add_element(&array, "alpha");
    test_assert_true(array != NULL, "ft_add_element should allocate array for first element");
    expected = "alpha";
    test_assert_true(array[0] == expected, "ft_add_element should store first element at index 0");
    test_assert_true(array[1] == NULL, "ft_add_element should terminate array with null pointer");
    free_const_array(array);
    return ;
}

static void test_add_element_appends_unique_elements()
{
    const char  **array;
    const char  *expected_alpha;
    const char  *expected_beta;

    array = NULL;
    ft_add_element(&array, "alpha");
    ft_add_element(&array, "beta");
    test_assert_true(array != NULL, "ft_add_element should keep array allocated after appending");
    expected_alpha = "alpha";
    expected_beta = "beta";
    test_assert_true(array[0] == expected_alpha, "ft_add_element should keep original element when appending");
    test_assert_true(array[1] == expected_beta, "ft_add_element should append new element at next index");
    test_assert_true(array[2] == NULL, "ft_add_element should terminate array after appending");
    free_const_array(array);
    return ;
}

static void test_add_element_ignores_duplicates()
{
    const char  **array;
    const char  *expected;

    array = NULL;
    ft_add_element(&array, "alpha");
    ft_add_element(&array, "alpha");
    test_assert_true(array != NULL, "ft_add_element should leave array allocated when ignoring duplicates");
    expected = "alpha";
    test_assert_true(array[0] == expected, "ft_add_element should keep original element when duplicate is added");
    test_assert_true(array[1] == NULL, "ft_add_element should not append duplicate elements");
    free_const_array(array);
    return ;
}

static void test_add_element_handles_null_array_pointer()
{
    ft_add_element(NULL, "alpha");
    test_assert_true(1, "ft_add_element should handle null array pointer without crashing");
    return ;
}

static void test_add_element_handles_null_element()
{
    const char  **array;

    array = NULL;
    ft_add_element(&array, NULL);
    test_assert_true(array == NULL, "ft_add_element should leave array null when element is null");
    return ;
}

void    run_add_element_tests()
{
    test_add_element_allocates_array_for_first_entry();
    test_add_element_appends_unique_elements();
    test_add_element_ignores_duplicates();
    test_add_element_handles_null_array_pointer();
    test_add_element_handles_null_element();
    return ;
}
