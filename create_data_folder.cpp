#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <sys/stat.h>
#include <cstring>
#include <cerrno>
#if defined(_WIN32)
# include <direct.h>
# include <io.h>
# ifndef R_OK
#  define R_OK 4
# endif
# ifndef W_OK
#  define W_OK 2
# endif
#else
# include <unistd.h>
#endif

#if defined(_WIN32)
# define FT_MKDIR(path, mode) _mkdir(path)
# define FT_ACCESS(path, mode) _access(path, mode)
#else
# define FT_MKDIR(path, mode) mkdir(path, mode)
# define FT_ACCESS(path, mode) access(path, mode)
#endif

int ft_create_data_dir()
{
    struct stat st;

    memset(&st, 0, sizeof(st));
    if (stat("data", &st) == -1)
    {
        if (errno == ENOENT)
        {
            if (FT_MKDIR("data", 0700) == -1)
            {
                pf_printf_fd(2, "001-Error failed to create directory: %s\n", strerror(errno));
                return (1);
            }
            else if (DEBUG == 1)
                pf_printf("Data folder created successfully\n");
        }
        else
        {
            pf_printf_fd(2, "002-Error failed to stat directory: %s\n", strerror(errno));
            return (1);
        }
    }
    else if (S_ISDIR(st.st_mode))
    {
        if (FT_ACCESS("data", R_OK | W_OK) == -1)
        {
            pf_printf_fd(2, "003-Error no read/write access to 'data' directory: %s\n",
					strerror(errno));
            return (1);
        }
        if (DEBUG == 1)
            pf_printf("Data folder already exists with proper access rights\n");
    }
    else
    {
        pf_printf_fd(2, "004-Error path exists but is not a directory\n");
        return (1);
    }
    return (0);
}
