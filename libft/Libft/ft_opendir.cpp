#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include "libft.hpp"
#include "../CMA/CMA.hpp"
#include "../Linux/linux_file.hpp"
#include "../CPP_class/nullptr.hpp"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

FT_DIR* ft_opendir(const char* path)
{
    int fd = ft_open(path, O_DIRECTORY | O_RDONLY);
    if (fd < 0)
        return (ft_nullptr);

    FT_DIR* dirp = reinterpret_cast<FT_DIR*>(cma_malloc(sizeof(FT_DIR)));
    if (!dirp)
	{
        ::close(fd);
        return (ft_nullptr);
    }
    memset(dirp, 0, sizeof(FT_DIR));
    dirp->fd = fd;
    dirp->buffer_size = 4096;
    dirp->buffer = reinterpret_cast<char*>(cma_malloc(dirp->buffer_size));
    if (!dirp->buffer)
	{
        cma_free(dirp);
        ::close(fd);
        return (ft_nullptr);
    }
    dirp->buffer_used   = 0;
    dirp->buffer_offset = 0;
    return (dirp);
}

ft_dirent* ft_readdir(FT_DIR* dirp)
{
    if (!dirp)
        return (ft_nullptr);
    if (dirp->buffer_offset >= static_cast<size_t>(dirp->buffer_used))
	{
        dirp->buffer_offset = 0;
        long nread = syscall(SYS_getdents64, dirp->fd,
				reinterpret_cast<linux_dirent64*>(dirp->buffer), dirp->buffer_size);
        if (nread <= 0)
            return (ft_nullptr);
        dirp->buffer_used = nread;
    }
    linux_dirent64* d = reinterpret_cast<linux_dirent64*>(dirp->buffer + dirp->buffer_offset);
    if (d->d_reclen == 0)
        return (ft_nullptr);
    static ft_dirent entry;
    memset(&entry, 0, sizeof(entry));
    entry.d_ino = d->d_ino;
    entry.d_type = d->d_type;
    strncpy(entry.d_name, d->d_name, sizeof(entry.d_name) - 1);
    dirp->buffer_offset += d->d_reclen;
    return (&entry);
}

int ft_closedir(FT_DIR* dirp)
{
    if (!dirp)
        return (-1);
    ::close(dirp->fd);
    cma_free(dirp->buffer);
    cma_free(dirp);
    return (0);
}
