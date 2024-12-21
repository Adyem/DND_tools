#include "unordened_map.hpp"
#include "../Errno/errno.hpp"

unsigned long ft_unordened_map::hash_str(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

ft_unordened_map::ft_unordened_map(size_t initial_capacity, bool is_critical) 
    : buckets(nullptr), capacity(initial_capacity), size(0), critical(is_critical),
		_error(ER_SUCCESS) {
    ft_errno = ER_SUCCESS;
    buckets = (ft_map_node**)cma_calloc((int)initial_capacity, sizeof(ft_map_node*), critical);
    if (!buckets) {
        ft_errno = FT_ERR_MEMORY;
        _error = FT_ERR_MEMORY;
    }
}

ft_unordened_map::~ft_unordened_map() {
    clear();
    if (buckets) {
        cma_free(buckets);
    }
}

bool ft_unordened_map::insert(const char *key, const char *value, bool key_value_critical) {
    if (!buckets || !key || !value) {
        ft_errno = FT_ERR_UNKNOWN;
        _error = FT_ERR_UNKNOWN;
        return false;
    }

    ft_errno = FT_ERR_NONE;
    _error = FT_ERR_NONE;
    unsigned long h = hash_str(key);
    size_t index = h % capacity;

    ft_map_node *node = buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            // Update existing value
            char *new_value = cma_strdup(value, key_value_critical);
            if (!new_value) {
                ft_errno = FT_ERR_MEMORY;
                _error = FT_ERR_MEMORY;
                return false;
            }
            cma_free(node->value);
            node->value = new_value;
            return true;
        }
        node = node->next;
    }

    // Insert a new node
    ft_map_node *new_node = (ft_map_node*)cma_calloc(1, sizeof(ft_map_node), critical);
    if (!new_node) {
        ft_errno = FT_ERR_MEMORY;
        _error = FT_ERR_MEMORY;
        return false;
    }

    new_node->key = cma_strdup(key, key_value_critical);
    if (!new_node->key) {
        ft_errno = FT_ERR_MEMORY;
        _error = FT_ERR_MEMORY;
        cma_free(new_node);
        return false;
    }

    new_node->value = cma_strdup(value, key_value_critical);
    if (!new_node->value) {
        ft_errno = FT_ERR_MEMORY;
        _error = FT_ERR_MEMORY;
        cma_free(new_node->key);
        cma_free(new_node);
        return false;
    }

    new_node->next = buckets[index];
    buckets[index] = new_node;
    size++;
    return true;
}

char* ft_unordened_map::find(const char *key) {
    if (!buckets || !key) {
        ft_errno = FT_ERR_UNKNOWN;
        _error = FT_ERR_UNKNOWN;
        return nullptr;
    }

    ft_errno = FT_ERR_NONE;
    _error = FT_ERR_NONE;
    unsigned long h = hash_str(key);
    size_t index = h % capacity;

    ft_map_node *node = buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    ft_errno = FT_ERR_NOT_FOUND;
    _error = FT_ERR_NOT_FOUND;
    return nullptr;
}

bool ft_unordened_map::remove(const char *key) {
    if (!buckets || !key) {
        ft_errno = FT_ERR_UNKNOWN;
        _error = FT_ERR_UNKNOWN;
        return false;
    }

    ft_errno = FT_ERR_NONE;
    _error = FT_ERR_NONE;
    unsigned long h = hash_str(key);
    size_t index = h % capacity;

    ft_map_node *prev = nullptr;
    ft_map_node *node = buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev)
                prev->next = node->next;
            else
                buckets[index] = node->next;

            cma_free(node->key);
            cma_free(node->value);
            cma_free(node);
            size--;
            return true;
        }
        prev = node;
        node = node->next;
    }

    ft_errno = FT_ERR_NOT_FOUND;
    _error = FT_ERR_NOT_FOUND;
    return false;
}

void ft_unordened_map::clear() {
    if (!buckets) return;

    for (size_t i = 0; i < capacity; i++) {
        ft_map_node *node = buckets[i];
        while (node) {
            ft_map_node *tmp = node->next;
            cma_free(node->key);
            cma_free(node->value);
            cma_free(node);
            node = tmp;
        }
        buckets[i] = nullptr;
    }
    size = 0;
    ft_errno = FT_ERR_NONE;
    _error = FT_ERR_NONE;
}

size_t ft_unordened_map::get_size() const {
    return size;
}

size_t ft_unordened_map::get_capacity() const {
    return capacity;
}

bool ft_unordened_map::is_critical() const {
    return critical;
}

int ft_unordened_map::get_error() const {
    return _error;
}

const char* ft_unordened_map::get_error_message() const {
    return ft_strerror(_error);
}
