#include "libft/Modules/Printf/printf.hpp"
#include "libft/Modules/Errno/errno.hpp"
#include "libft/Modules/File/file_utils.hpp"
#include "libft/Modules/File/open_dir.hpp"
#include "libft/Modules/System_utils/system_utils.hpp"
#include "dnd_tools.hpp"

int ft_create_data_dir()
{
    int directory_status;
    file_dir *directory_stream;
    su_file *write_probe;
    const char *probe_path;

    directory_status = file_dir_exists("data");
    if (directory_status == -1)
    {
        pf_printf_fd(2, "002-Error failed to query 'data' directory: %s\n",
            ft_strerror(FT_ERR_SUCCESS));
        return (1);
    }
    if (directory_status == 0)
    {
        if (file_exists("data") == 1)
        {
            pf_printf_fd(2, "004-Error path exists but is not a directory\n");
            return (1);
        }
        if (file_create_directory("data", 0700) == -1)
        {
            pf_printf_fd(2, "001-Error failed to create 'data' directory: %s\n",
                ft_strerror(FT_ERR_SUCCESS));
            return (1);
        }
        if (DEBUG == 1)
            pf_printf("Data folder created successfully\n");
        return (0);
    }
    directory_stream = file_opendir("data");
    if (!directory_stream)
    {
        pf_printf_fd(2, "003-Error no read/write access to 'data' directory: %s\n",
            ft_strerror(FT_ERR_SUCCESS));
        return (1);
    }
    if (file_closedir(directory_stream) == -1)
    {
        pf_printf_fd(2, "003-Error no read/write access to 'data' directory: %s\n",
            ft_strerror(FT_ERR_SUCCESS));
        return (1);
    }
    probe_path = "data/.dnd_tools_access.tmp";
    write_probe = su_fopen(probe_path, O_CREAT | O_RDWR, 0600);
    if (!write_probe)
    {
        pf_printf_fd(2, "003-Error no read/write access to 'data' directory: %s\n",
            ft_strerror(FT_ERR_SUCCESS));
        return (1);
    }
    if (su_fclose(write_probe) == -1)
    {
        pf_printf_fd(2, "003-Error no read/write access to 'data' directory: %s\n",
            ft_strerror(FT_ERR_SUCCESS));
        file_delete(probe_path);
        return (1);
    }
    if (file_delete(probe_path) == -1)
    {
        pf_printf_fd(2, "003-Error no read/write access to 'data' directory: %s\n",
            ft_strerror(FT_ERR_SUCCESS));
        return (1);
    }
    if (DEBUG == 1)
        pf_printf("Data folder already exists with proper access rights\n");
    return (0);
}
