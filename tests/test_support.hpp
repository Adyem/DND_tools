#ifndef TEST_SUPPORT_HPP
# define TEST_SUPPORT_HPP

# include "../libft/CPP_class/class_string_class.hpp"

void    test_assert_true(int condition, const char *message);
void    test_begin_suite(const char *suite_name);
void    test_end_suite_success();
void    test_begin_error_capture(const char *file_path);
void    test_end_error_capture();
void    test_begin_output_capture(const char *file_path);
void    test_end_output_capture();
ft_string    test_read_file_to_string(const char *file_path);
void    test_delete_file(const char *file_path);
void    test_create_directory(const char *directory_path);
void    test_remove_directory(const char *directory_path);
void    test_remove_path(const char *path);
int     test_path_exists(const char *path);

#endif
