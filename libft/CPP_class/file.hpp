#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

class ft_file
{
public:
    ft_file(const char* filename, int flags, mode_t mode = 0) noexcept;
    ft_file(int fd) noexcept;

    ~ft_file() noexcept;

    ft_file(const ft_file&) = delete;
    ft_file &operator=(const ft_file&) = delete;

    ft_file(ft_file&& other) noexcept;
    ft_file& operator=(ft_file&& other) noexcept;

    int get_fd() const;

    bool has_error() const noexcept;
    int get_error_code() const noexcept;
    const char *get_error_message() const noexcept;

private:
    int _fd;
    int _error_code;
};