#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <sys/stat.h>
#include <cstring>
#include <cerrno>
#include <unistd.h>

int ft_create_data_dir()
{
    struct stat st;

    memset(&st, 0, sizeof(st));
    if (stat("data", &st) == -1)
    {
        if (errno == ENOENT)
        {
            if (mkdir("data", 0700) == -1)
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
        if (access("data", R_OK | W_OK) == -1)
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
