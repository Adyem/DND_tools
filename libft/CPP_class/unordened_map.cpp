#include "unordened_map.hpp"
#include "../Errno/errno.hpp"
#include "../CMA/CMA.hpp"

unsigned long ft_unordened_map::hash_str(const char *string)
{
    unsigned long hash = 5381;
    int count;
    while ((count = (unsigned char)*string++))
        hash = ((hash << 5) + hash) + count;
    return (hash);
}

ft_unordened_map::ft_unordened_map(size_t initial_capacity, bool is_critical) 
    : _buckets(nullptr), _capacity(initial_capacity), _size(0), _critical(is_critical),
		_error(ER_SUCCESS)
{
    ft_errno = ER_SUCCESS;
    this->_buckets = (ft_map_node**)cma_calloc((int)initial_capacity, sizeof(ft_map_node*),
			this->_critical);
    if (!this->_buckets)
	{
        ft_errno = UNORD_MAP_MEMORY;
        this->_error = UNORD_MAP_MEMORY;
    }
	return ;
}

ft_unordened_map::~ft_unordened_map()
{
	clear();
	if (this->_buckets)
		cma_free(this->_buckets);
	return ;
}

bool ft_unordened_map::insert(const char *key, const char *value)
{
    if (!this->_buckets || !key || !value)
	{
        ft_errno = UNORD_MAP_UNKNOWN;
        this->_error = UNORD_MAP_UNKNOWN;
        return (false);
    }
    ft_errno = ER_SUCCESS;
    this->_error = ER_SUCCESS;
    unsigned long hash_value = hash_str(key);
    size_t index = hash_value % this->_capacity;
    ft_map_node *node = this->_buckets[index];
    while (node)
	{
        if (strcmp(node->_key, key) == 0)
		{
            char *new_value = cma_strdup(value, this->_critical);
            if (!new_value)
			{
                ft_errno = UNORD_MAP_MEMORY;
                this->_error = UNORD_MAP_MEMORY;
                return (false);
            }
            cma_free(node->_value);
            node->_value = new_value;
            return (true);
        }
        node = node->_next;
    }
    ft_map_node *new_node = (ft_map_node*)cma_calloc(1, sizeof(ft_map_node), this->_critical);
    if (!new_node)
	{
        ft_errno = UNORD_MAP_MEMORY;
        this->_error = UNORD_MAP_MEMORY;
        return (false);
    }
    new_node->_key = cma_strdup(key, this->_critical);
    if (!new_node->_key)
	{
        ft_errno = UNORD_MAP_MEMORY;
        this->_error = UNORD_MAP_MEMORY;
        cma_free(new_node);
        return (false);
    }
    new_node->_value = cma_strdup(value, this->_critical);
    if (!new_node->_value)
	{
        ft_errno = UNORD_MAP_MEMORY;
        this->_error = UNORD_MAP_MEMORY;
        cma_free(new_node->_key);
        cma_free(new_node);
        return (false);
    }
    new_node->_next = this->_buckets[index];
    this->_buckets[index] = new_node;
    this->_size++;
    return (true);
}

char* ft_unordened_map::find(const char *key, int num_bytes)
{
    if (!this->_buckets || !key || num_bytes <= 0)
    {
        ft_errno = UNORD_MAP_UNKNOWN;
        this->_error = UNORD_MAP_UNKNOWN;
		return (nullptr);
    }
	size_t index = 0;
	while (index < this->_capacity)
    {
        ft_map_node *node = this->_buckets[index];
        while (node)
        {
            size_t key_len = strlen(node->_key);
            size_t search_key_len = strlen(key);
            if (key_len < static_cast<size_t>(num_bytes) || search_key_len
					< static_cast<size_t>(num_bytes))
            {
                node = node->_next;
                continue ;
            }
            if (strncmp(node->_key, key, num_bytes) == 0)
                return (node->_value);
            node = node->_next;
        }
		index++;
    }
    ft_errno = UNORD_MAP_NOT_FOUND;
    this->_error = UNORD_MAP_NOT_FOUND;
    return (nullptr);
}

char* ft_unordened_map::find(const char *key)
{
    if (!this->_buckets || !key)
	{
        ft_errno = UNORD_MAP_UNKNOWN;
        _error = UNORD_MAP_UNKNOWN;
		return (nullptr);
    }
    ft_errno = ER_SUCCESS;
    this->_error = ER_SUCCESS;
    unsigned long hash_value = hash_str(key);
    size_t index = hash_value % this->_capacity;
    ft_map_node *node = this->_buckets[index];
    while (node)
	{
        if (strcmp(node->_key, key) == 0)
            return (node->_value);
        node = node->_next;
    }
    ft_errno = UNORD_MAP_UNKNOWN;
    this->_error = UNORD_MAP_UNKNOWN;
    return (nullptr);
}

bool ft_unordened_map::remove(const char *key)
{
    if (!this->_buckets || !key)
	{
        ft_errno = UNORD_MAP_UNKNOWN;
        this->_error = UNORD_MAP_UNKNOWN;
        return (false);
    }
    ft_errno = ER_SUCCESS;
    _error = ER_SUCCESS;
    unsigned long hash_value = hash_str(key);
    size_t index = hash_value % this->_capacity;
    ft_map_node *prev = nullptr;
    ft_map_node *node = this->_buckets[index];
    while (node)
	{
        if (strcmp(node->_key, key) == 0)
		{
            if (prev)
                prev->_next = node->_next;
            else
                this->_buckets[index] = node->_next;
            cma_free(node->_key);
            cma_free(node->_value);
            cma_free(node);
            this->_size--;
            return (true);
        }
        prev = node;
        node = node->_next;
    }
    ft_errno = UNORD_MAP_NOT_FOUND;
    this->_error = UNORD_MAP_NOT_FOUND;
    return (false);
}

void ft_unordened_map::clear()
{
    if (!this->_buckets) return;
    size_t index = 0;
	while (index < this->_capacity)
	{
        ft_map_node *node = this->_buckets[index];
        while (node)
		{
            ft_map_node *tmp = node->_next;
            cma_free(node->_key);
            cma_free(node->_value);
            cma_free(node);
            node = tmp;
        }
        this->_buckets[index] = nullptr;
		index++;
    }
    this->_size = 0;
    ft_errno = ER_SUCCESS;
    this->_error = ER_SUCCESS;
	return ;
}

size_t ft_unordened_map::get_size() const
{
    return (this->_size);
}

size_t ft_unordened_map::get_capacity() const
{
    return (this->_capacity);
}

bool ft_unordened_map::is_critical() const
{
    return (this->_critical);
}

int ft_unordened_map::get_error() const
{
    return (this->_error);
}

const char* ft_unordened_map::get_error_message() const
{
    return (ft_strerror(this->_error));
}
