#ifndef TEMPORARYFILE_HPP
#define TEMPORARYFILE_HPP

#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <vector>

class TemporaryFile {
public:
    std::string original_filename;
    std::string temp_filename;
    int fd;

    TemporaryFile(const std::string& filename);
    ~TemporaryFile();

    // Disable copy semantics
    TemporaryFile(const TemporaryFile&) = delete;
    TemporaryFile& operator=(const TemporaryFile&) = delete;

    // Enable move semantics
    TemporaryFile(TemporaryFile&& other) noexcept;
    TemporaryFile& operator=(TemporaryFile&& other) noexcept;

    // Function to write data to the temporary file
    void write_data(const void* data, size_t size);

    // Function to write a null-terminated string to the temporary file
    void write_string(const std::string& str);

    // Function to finalize and replace the original file with the temporary file
    void finalize();
};

#endif // TEMPORARYFILE_HPP
