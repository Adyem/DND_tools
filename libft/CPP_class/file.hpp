#ifndef FILE_HPP
# define FILE_HPP

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

class ft_file
{
	private:
    	int _fd;
    	int _error_code;

		void		set_error(int error_code);

	public:
		ft_file() noexcept;
	    ft_file(const char* filename, int flags, mode_t mode) noexcept;
		ft_file(const char* filename, int flags) noexcept;
	    ft_file(int fd) noexcept;
	    ~ft_file() noexcept;

	    ft_file(const ft_file&) = delete;
    	ft_file &operator=(const ft_file&) = delete;
    	ft_file(ft_file&& other) noexcept;
    	ft_file& operator=(ft_file&& other) noexcept;

    	int			get_fd() const;
	    int			get_error_code() const noexcept;
    	const char	*get_error_message() const noexcept;

	    int			open(const char* filename, int flags, mode_t mode) noexcept;
		int			open(const char* filename, int flags) noexcept;
		int			write(const char *string) noexcept;
		void		close() noexcept;
		int			seek(off_t offset, int whence) noexcept;
		int			read(char *buffer, int count) noexcept;
		int			printf(const char *format, ...) const
						__attribute__((format(printf, 2, 3), hot));
};

#endif
