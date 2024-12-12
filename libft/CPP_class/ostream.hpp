#ifndef FT_OSTREAM_HPP
#define FT_OSTREAM_HPP

#include <stddef.h>

class ft_ostream
{
	private:
		char*  buffer;
		size_t capacity;
		size_t size;
		bool   error_flag;

	public:
		ft_ostream();
		~ft_ostream();
	
		ft_ostream& operator<<(const char* str);
		ft_ostream& operator<<(int val);
		ft_ostream& operator<<(char c);

		int write(const char* data, size_t len);
		char* str();
		bool bad() const;
		void clear();
};

#endif 
