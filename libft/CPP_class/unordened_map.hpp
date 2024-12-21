#ifndef UNORDENED_MAP_HPP
# define UNORDENED_MAP_HPP

#include <cstdio>
#include <cstring>
#include <cerrno>

class ft_unordened_map
{
	private:
    	struct ft_map_node
		{
    	    char 		*_key;
    	    char 		*_value;
    	    ft_map_node *_next;
    	};
    	ft_map_node		**_buckets;
    	size_t 			_capacity;
    	size_t 			_size;
    	bool 			_critical;
		int 			_error;

    	static unsigned long hash_str(const char *string);

	public:
    	ft_unordened_map(size_t initial_capacity, bool criticality = false);
    	~ft_unordened_map();

    	bool insert(const char *key, const char *value);
    	char* find(const char *key);
    	bool remove(const char *key);
    	void clear();

    	size_t get_size() const;
    	size_t get_capacity() const;
    	bool is_critical() const;

    	int get_error() const;
    	const char* get_error_message() const;
};

#endif
