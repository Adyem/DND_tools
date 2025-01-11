#ifdef _WIN32

#include "file.hpp"
#include <windows.h>
#include <stdio.h>

static HANDLE g_handles[1024];

static int store_handle(HANDLE h)
{
    for (int i = 0; i < 1024; i++)
	{
        if (g_handles[i] == NULL)
		{
            g_handles[i] = h;
            return i;
        }
    }
    return -1;
}

static HANDLE retrieve_handle(int fd)
{
    if (fd < 0 || fd >= 1024) return INVALID_HANDLE_VALUE;
    return g_handles[fd];
}

static void clear_handle(int fd)
{
    if (fd < 0 || fd >= 1024) return;
    g_handles[fd] = NULL;
}

int ft_open(const char *pathname, int flags, int mode)
{
    DWORD desiredAccess = 0;
    DWORD creationDisposition = 0;
    DWORD fileAttributes = FILE_ATTRIBUTE_NORMAL;

	(void)mode;
	if ((flags & O_RDWR) == O_RDWR)
        desiredAccess = GENERIC_READ | GENERIC_WRITE;
	else if ((flags & O_WRONLY) == O_WRONLY)
        desiredAccess = GENERIC_WRITE;
	else
        desiredAccess = GENERIC_READ;
	if ((flags & O_CREAT) && (flags & O_EXCL))
        creationDisposition = CREATE_NEW;
	else if ((flags & O_CREAT) && (flags & O_TRUNC))
        creationDisposition = CREATE_ALWAYS;
	else if (flags & O_CREAT)
        creationDisposition = OPEN_ALWAYS;
	else if (flags & O_TRUNC)
        creationDisposition = TRUNCATE_EXISTING;
	else
        creationDisposition = OPEN_EXISTING;
	if (flags & O_APPEND)
        desiredAccess |= FILE_APPEND_DATA;
    HANDLE hFile = CreateFileA(pathname, desiredAccess, FILE_SHARE_READ
			| FILE_SHARE_WRITE, NULL, creationDisposition, fileAttributes, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return -1;
    int fd = store_handle(hFile);
	if (fd < 0)
	{
        CloseHandle(hFile);
        return -1;
    }
    return fd;
}

int ft_read(int fd, void *buf, unsigned int count)
{
    HANDLE hFile = retrieve_handle(fd);
    if (hFile == INVALID_HANDLE_VALUE) return -1;

    DWORD bytesRead = 0;
    BOOL ok = ReadFile(hFile, buf, count, &bytesRead, NULL);
    if (!ok) return -1;
    return (int)bytesRead;
}

int ft_write(int fd, const void *buf, unsigned int count)
{
    HANDLE hFile = retrieve_handle(fd);
    if (hFile == INVALID_HANDLE_VALUE) return -1;

    DWORD bytesWritten = 0;
    BOOL ok = WriteFile(hFile, buf, count, &bytesWritten, NULL);
    if (!ok) return -1;
    return (int)bytesWritten;
}

int ft_close(int fd)
{
    HANDLE hFile = retrieve_handle(fd);
    if (hFile == INVALID_HANDLE_VALUE) return -1;
    if (!CloseHandle(hFile)) return -1;

    clear_handle(fd);
    return 0;
}

#endif
