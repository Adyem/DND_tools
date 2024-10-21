#include <cstring>
#include "CMA.hpp"

class ft_string {
private:
    char* data;
    std::size_t length;
    std::size_t capacity;
    bool errorFlag;
    bool criticality;

    void resize(std::size_t new_capacity) noexcept {
        if (new_capacity <= capacity) return;
        char* new_data = static_cast<char*>(cma_malloc(new_capacity, criticality));
        if (!new_data) {
            errorFlag = true;
            return;
        }
        if (data) {
            std::memcpy(new_data, data, length);
            cma_free(data);
        }
        data = new_data;
        capacity = new_capacity;
    }

public:
    ft_string() noexcept 
        : data(nullptr), length(0), capacity(0), errorFlag(false), criticality(false) {}

    ft_string(const char* init_str, bool crit = false) noexcept 
        : data(nullptr), length(0), capacity(0), errorFlag(false), criticality(crit) {
        if (init_str) {
            length = std::strlen(init_str);
            capacity = length + 1;
            data = static_cast<char*>(cma_malloc(capacity, criticality));
            if (!data) {
                errorFlag = true;
                return;
            }
            std::memcpy(data, init_str, length + 1);
        }
    }

    ft_string(const ft_string& other) noexcept 
        : data(nullptr), length(other.length), capacity(other.capacity), 
          errorFlag(other.errorFlag), criticality(other.criticality) {
        if (other.data) {
            data = static_cast<char*>(cma_malloc(capacity, criticality));
            if (!data) {
                errorFlag = true;
                return;
            }
            std::memcpy(data, other.data, length + 1);
        }
    }

    ft_string& operator=(const ft_string& other) noexcept {
        if (this == &other) {
            return *this;
        }

        cma_free(data);
        data = nullptr;
        length = other.length;
        capacity = other.capacity;
        errorFlag = other.errorFlag;
        criticality = other.criticality;

        if (other.data) {
            data = static_cast<char*>(cma_malloc(capacity, criticality));
            if (!data) {
                errorFlag = true;
                return *this;
            }
            std::memcpy(data, other.data, length + 1);
        }

        return *this;
    }

    ~ft_string() {
        cma_free(data);
    }

    void append(char c) noexcept {
        if (length + 1 >= capacity) {
            resize(capacity == 0 ? 16 : capacity * 2);
            if (errorFlag) return;
        }
        data[length++] = c;
        data[length] = '\0';
    }

    void clear() noexcept {
        length = 0;
        if (data) {
            data[0] = '\0';
        }
        errorFlag = false;
    }

    const char* at(std::size_t index) const noexcept {
        if (index >= length) {
            return nullptr;
        }
        return &data[index];
    }

    const char* c_str() const noexcept {
        return data ? data : "";
    }

    char* print() noexcept {
        return data ? data : const_cast<char*>("");
    }

    std::size_t size() const noexcept {
        return length;
    }

    bool empty() const noexcept {
        return length == 0;
    }

    bool hasError() const noexcept {
        return errorFlag;
    }

    bool isCritical() const noexcept {
        return criticality;
    }
};
