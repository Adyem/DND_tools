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

FT_DIR* ft_opendir(const char* directoryPath)
{
    int fileDescriptor = ft_open(directoryPath, O_DIRECTORY | O_RDONLY);
    if (fileDescriptor < 0)
        return (ft_nullptr);
    FT_DIR* directoryStream = reinterpret_cast<FT_DIR*>(cma_malloc(sizeof(FT_DIR)));
    if (!directoryStream)
    {
        ft_close(fileDescriptor);
        return (ft_nullptr);
    }
    memset(directoryStream, 0, sizeof(FT_DIR));
    directoryStream->fd = fileDescriptor;
    directoryStream->buffer_size = 4096;
    directoryStream->buffer = reinterpret_cast<char*>(cma_malloc(directoryStream->buffer_size));
    if (!directoryStream->buffer)
    {
        cma_free(directoryStream);
        ft_close(fileDescriptor);
        return (ft_nullptr);
    }
    directoryStream->buffer_used   = 0;
    directoryStream->buffer_offset = 0;
    return (directoryStream);
}

ft_dirent* ft_readdir(FT_DIR* directoryStream)
{
    if (!directoryStream)
        return (ft_nullptr);
    if (directoryStream->buffer_offset >= static_cast<size_t>(directoryStream->buffer_used))
    {
        directoryStream->buffer_offset = 0;
        long bytesRead = syscall(SYS_getdents64, directoryStream->fd,
                reinterpret_cast<linux_dirent64*>(directoryStream->buffer),
				directoryStream->buffer_size);
        if (bytesRead <= 0)
            return (ft_nullptr);
        directoryStream->buffer_used = bytesRead;
    }
    linux_dirent64* rawDirent = reinterpret_cast<linux_dirent64*>
		(directoryStream->buffer + directoryStream->buffer_offset);
    if (rawDirent->d_reclen == 0)
        return (ft_nullptr);
    static ft_dirent currentEntry;
    memset(&currentEntry, 0, sizeof(currentEntry));
    currentEntry.d_ino = rawDirent->d_ino;
    currentEntry.d_type = rawDirent->d_type;
    strncpy(currentEntry.d_name, rawDirent->d_name, sizeof(currentEntry.d_name) - 1);
    directoryStream->buffer_offset += rawDirent->d_reclen;
    return (&currentEntry);
}

int ft_closedir(FT_DIR* directoryStream)
{
    if (!directoryStream)
        return (-1);
    ft_close(directoryStream->fd);
    cma_free(directoryStream->buffer);
    cma_free(directoryStream);
    return (0);
}
