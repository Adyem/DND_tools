#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

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

	private:
	    int 	_fd;
};
