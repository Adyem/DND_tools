#ifndef FT_STRING_HPP
#define FT_STRING_HPP

#include <cstring>

class ft_string
{
	private:
	    char* data;
	    std::size_t length;
	    std::size_t capacity;
	    bool errorFlag;
	    bool criticality;

	    void resize(std::size_t new_capacity) noexcept;

	public:
	    ft_string() noexcept;
	    ft_string(const char* init_str, bool crit = false) noexcept;
	    ft_string(const ft_string& other) noexcept;
	    ft_string& operator=(const ft_string& other) noexcept;
	    ~ft_string();

	    void append(char c) noexcept;
	    void clear() noexcept;
	    const char* at(std::size_t index) const noexcept;
	    const char* c_str() const noexcept;
	    char* print() noexcept;
	    std::size_t size() const noexcept;
	    bool empty() const noexcept;
	    bool hasError() const noexcept;
	    bool isCritical() const noexcept;
};

#endif

