#ifndef FT_STRING_HPP
#define FT_STRING_HPP

#include <cstddef>
#include <cstring>

class ft_string
{
    private:
        char*    _data;
        size_t   _length;
        size_t   _capacity;
        int      _errorCode;
        bool     _criticality;

        void    resize(size_t new_capacity) noexcept;
        void    setError(int errorCode) noexcept;

    public:
        ft_string() noexcept;
        ft_string(const char *init_str, bool crit = false) noexcept;
        ft_string(const ft_string& other) noexcept;
        ft_string(ft_string&& other) noexcept;
        ft_string &operator=(const ft_string& other) noexcept;
        ft_string &operator=(ft_string&& other) noexcept;
        ft_string &operator=(const char *&other) noexcept;
        ft_string& operator+=(const ft_string& other) noexcept;
        ft_string& operator+=(const char* cstr) noexcept;
        ft_string& operator+=(char c) noexcept;
        ~ft_string();

        void        append(char c) noexcept;
        void        append(const char *string) noexcept;
        void        append(const ft_string &string) noexcept;
        void        clear() noexcept;
        const char* at(size_t index) const noexcept;
        const char* c_str() const noexcept;
        char*       print() noexcept;
        size_t      size() const noexcept;
        bool        empty() const noexcept;
        int         getError() const noexcept;
        const char* errorStr() const noexcept;
        bool        isCritical() const noexcept;
        void        move(ft_string& other) noexcept;
        void        erase(size_t index, int count) noexcept;

		operator const char*() const noexcept;

        friend ft_string operator+(const ft_string &lhs, const ft_string &rhs) noexcept;
        friend ft_string operator+(const ft_string &lhs, const char *rhs) noexcept;
        friend ft_string operator+(const char *lhs, const ft_string &rhs) noexcept;
		friend ft_string operator+(const ft_string &lhs, char rhs) noexcept;
		friend ft_string operator+(char lhs, const ft_string &rhs) noexcept;
};

#endif
