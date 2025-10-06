#ifndef TEST_SUPPORT_HPP
# define TEST_SUPPORT_HPP

# include <string>

void    test_assert_true(int condition, const char *message);
void    test_begin_error_capture(const char *file_path);
void    test_end_error_capture();
std::string  test_read_file_to_string(const char *file_path);
void    test_delete_file(const char *file_path);

#endif
