#ifndef TEMPORARYFILE_HPP
#define TEMPORARYFILE_HPP

#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cerrno>

class TemporaryFile
{
	public:
    	std::string original_filename;
    	std::string temp_filename;
    	int fd;

    	TemporaryFile(const std::string& filename);
    	~TemporaryFile();
    	TemporaryFile(const TemporaryFile&) = delete;
    	TemporaryFile& operator=(const TemporaryFile&) = delete;
    	TemporaryFile(TemporaryFile&& other) noexcept;
    	TemporaryFile& operator=(TemporaryFile&& other) noexcept;
    	void write_data(const void* data, size_t size);
    	void write_string(const std::string& str);
    	void finalize();
};

#endif
