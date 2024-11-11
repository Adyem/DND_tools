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

    TemporaryFile(const std::string& filename) : original_filename(filename), fd(-1) {
        // Create a unique temporary filename
        temp_filename = filename + ".tmpXXXXXX";

        // Use std::vector<char> to create a mutable character array
        std::vector<char> temp_path(temp_filename.begin(), temp_filename.end());
        temp_path.push_back('\0'); // Null-terminate the string

        // mkstemp replaces 'XXXXXX' with a unique suffix and opens the file
        fd = mkstemp(temp_path.data());
        if (fd == -1) {
            throw std::runtime_error("Failed to create temporary file for " +
					filename + ": " + strerror(errno));
        }

        // Update temp_filename with the actual name returned by mkstemp
        temp_filename = std::string(temp_path.data());
    }

    ~TemporaryFile() {
        if (fd != -1) {
            close(fd);
            // Remove the temporary file if it still exists
            unlink(temp_filename.c_str());
        }
    }

    // Disable copy semantics
    TemporaryFile(const TemporaryFile&) = delete;
    TemporaryFile& operator=(const TemporaryFile&) = delete;

    // Enable move semantics
    TemporaryFile(TemporaryFile&& other) noexcept
        : original_filename(std::move(other.original_filename)),
          temp_filename(std::move(other.temp_filename)),
          fd(other.fd) {
        other.fd = -1;
    }

    TemporaryFile& operator=(TemporaryFile&& other) noexcept {
        if (this != &other) {
            if (fd != -1) {
                close(fd);
                unlink(temp_filename.c_str());
            }
            original_filename = std::move(other.original_filename);
            temp_filename = std::move(other.temp_filename);
            fd = other.fd;
            other.fd = -1;
        }
        return *this;
    }

    // Function to write data to the temporary file
    void write_data(const void* data, size_t size) {
        ssize_t bytes_written = write(fd, data, size);
        if (bytes_written == -1 || static_cast<size_t>(bytes_written) != size) {
            throw std::runtime_error("Failed to write to temporary file " +
					temp_filename + ": " + strerror(errno));
        }
    }

    // Function to write a null-terminated string to the temporary file
    void write_string(const std::string& str) {
        write_data(str.c_str(), str.size());
    }

    // Function to finalize and replace the original file with the temporary file
    void finalize() {
        if (rename(temp_filename.c_str(), original_filename.c_str()) == -1) {
            throw std::runtime_error("Failed to rename temporary file " +
					temp_filename + " to " + original_filename + ": " + strerror(errno));
        }
        fd = -1; // Ownership transferred to the OS
    }
};

#endif // TEMPORARYFILE_HPP

