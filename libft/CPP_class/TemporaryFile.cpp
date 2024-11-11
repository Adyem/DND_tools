#include "TemporaryFile.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <vector>

TemporaryFile::TemporaryFile(const std::string& filename) : original_filename(filename), fd(-1)
{
    temp_filename = filename + ".tmpXXXXXX";
    std::vector<char> temp_path(temp_filename.begin(), temp_filename.end());
    temp_path.push_back('\0');
    fd = mkstemp(temp_path.data());
    if (fd == -1)
    {
        throw std::runtime_error("Failed to create temporary file for " +
            filename + ": " + strerror(errno));
    }
    temp_filename = std::string(temp_path.data());
	return ;
}

TemporaryFile::~TemporaryFile()
{
    if (fd != -1)
	{
        close(fd);
        unlink(temp_filename.c_str());
    }
	return ;
}

TemporaryFile::TemporaryFile(TemporaryFile&& other) noexcept
    : original_filename(std::move(other.original_filename)),
      temp_filename(std::move(other.temp_filename)),
      fd(other.fd)
{
    other.fd = -1;
	return ;
}

TemporaryFile& TemporaryFile::operator=(TemporaryFile&& other) noexcept
{
    if (this != &other)
	{
        if (fd != -1)
		{
            close(fd);
            unlink(temp_filename.c_str());
        }
        original_filename = std::move(other.original_filename);
        temp_filename = std::move(other.temp_filename);
        fd = other.fd;
        other.fd = -1;
    }
    return (*this);
}

void TemporaryFile::write_data(const void* data, size_t size)
{
    ssize_t bytes_written = write(fd, data, size);
    if (bytes_written == -1 || static_cast<size_t>(bytes_written) != size)
	{
        throw std::runtime_error("Failed to write to temporary file " +
            temp_filename + ": " + strerror(errno));
    }
	return ;
}

void TemporaryFile::write_string(const std::string& str)
{
    write_data(str.c_str(), str.size());
	return ;
}

void TemporaryFile::finalize()
{
    if (rename(temp_filename.c_str(), original_filename.c_str()) == -1)
	{
        throw std::runtime_error("Failed to rename temporary file " +
            temp_filename + " to " + original_filename + ": " + strerror(errno));
    }
    fd = -1;
	return ;
}
