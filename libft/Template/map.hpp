#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "pair.hpp"
#include "constructor.hpp"
#include "../CMA/CMA.hpp"
#include "../Errno/errno.hpp"
#include "../CPP_class/nullptr.hpp"
#include <cstddef>

template <typename Key, typename MappedType>
class ft_map
{
private:
    Pair<Key, MappedType>*  _data;
    size_t                  _capacity;
    size_t                  _size;
    mutable int             _error;

    void    resize(size_t newCapacity);
    size_t  findIndex(const Key& key) const;
    void    setError(int error) const;

public:
    ft_map(size_t initialCapacity = 10);
    ft_map(const ft_map& other);
    ft_map& operator=(const ft_map& other);
    ft_map(ft_map&& other) noexcept;
    ft_map& operator=(ft_map&& other) noexcept;
    ~ft_map();

    void        insert(const Key& key, const MappedType& value);
    Pair<Key, MappedType> *find(const Key& key);
	void        remove(const Key& key);
    bool        empty() const;
    void        clear();
    size_t      getSize() const;
    size_t      getCapacity() const;
    int         getError() const;

    Pair<Key, MappedType>* end();
    MappedType &at(const Key& key);

	const Pair<Key, MappedType> *end() const;
	const MappedType &at(const Key& key) const;
	const Pair<Key, MappedType> *find(const Key& key) const;
};

template <typename Key, typename MappedType>
ft_map<Key, MappedType>::ft_map(size_t initialCapacity)
    : _capacity(initialCapacity), _size(0), _error(ER_SUCCESS)
{
    void* rawMemory = cma_malloc(sizeof(Pair<Key, MappedType>) * this->_capacity);
    if (!rawMemory)
    {
        this->setError(SHARED_PTR_ALLOCATION_FAILED);
        this->_data = ft_nullptr;
        return ;
    }
    this->_data = static_cast<Pair<Key, MappedType>*>(rawMemory);
}

template <typename Key, typename MappedType>
ft_map<Key, MappedType>::ft_map(const ft_map<Key, MappedType>& other)
    : _capacity(other._capacity), _size(other._size), _error(other._error)
{
    if (other._data != ft_nullptr && this->_size > 0)
    {
        void* rawMemory = cma_malloc(sizeof(Pair<Key, MappedType>) * this->_capacity);
        if (!rawMemory)
        {
            this->setError(SHARED_PTR_ALLOCATION_FAILED);
            this->_data = ft_nullptr;
            this->_size = 0;
            this->_capacity = 0;
            return ;
        }
        this->_data = static_cast<Pair<Key, MappedType>*>(rawMemory);
        size_t index = 0;
        while (index < this->_size)
        {
            construct_at(&this->_data[index], other._data[index]);
            index++;
        }
    }
    else
        this->_data = ft_nullptr;
    return ;
}

template <typename Key, typename MappedType>
ft_map<Key, MappedType>& ft_map<Key, MappedType>::operator=(const ft_map<Key, MappedType>& other)
{
    if (this != &other)
    {
        if (this->_data != ft_nullptr)
        {
            size_t index = 0;
            while (index < this->_size)
            {
                destroy_at(&this->_data[index]);
                index++;
            }
            cma_free(this->_data);
        }
        this->_capacity = other._capacity;
        this->_size = other._size;
        this->_error = other._error;
        if (other._data != ft_nullptr && other._size > 0)
        {
            void* rawMemory = cma_malloc(sizeof(Pair<Key, MappedType>) * other._capacity);
            if (!rawMemory)
            {
                this->setError(SHARED_PTR_ALLOCATION_FAILED);
                this->_data = ft_nullptr;
                this->_size = 0;
                this->_capacity = 0;
                return (*this);
            }
            this->_data = static_cast<Pair<Key, MappedType>*>(rawMemory);
            size_t index = 0;
            while (index < other._size)
            {
                construct_at(&this->_data[index], other._data[index]);
                index++;
            }
        }
        else
            this->_data = ft_nullptr;
    }
    return (*this);
}

template <typename Key, typename MappedType>
ft_map<Key, MappedType>::ft_map(ft_map<Key, MappedType>&& other) noexcept
    : _data(other._data), _capacity(other._capacity), _size(other._size),
      _error(other._error)
{
    other._data = ft_nullptr;
    other._capacity = 0;
    other._size = 0;
    other._error = ER_SUCCESS;
    return ;
}

template <typename Key, typename MappedType>
ft_map<Key, MappedType>& ft_map<Key, MappedType>::operator=(ft_map<Key, MappedType>&& other)
	noexcept
{
    if (this != &other)
    {
        if (this->_data != ft_nullptr)
        {
            size_t index = 0;
            while (index < this->_size)
            {
                destroy_at(&this->_data[index]);
                index++;
            }
            cma_free(this->_data);
        }
        this->_data = other._data;
        this->_capacity = other._capacity;
        this->_size = other._size;
        this->_error = other._error;
        other._data = ft_nullptr;
        other._capacity = 0;
        other._size = 0;
        other._error = ER_SUCCESS;
    }
    return *this;
}

template <typename Key, typename MappedType>
ft_map<Key, MappedType>::~ft_map()
{
    if (this->_data != ft_nullptr)
    {
        size_t index = 0;
        while (index < this->_size)
        {
            destroy_at(&this->_data[index]);
            index++;
        }
        cma_free(this->_data);
    }
}

template <typename Key, typename MappedType>
void ft_map<Key, MappedType>::insert(const Key& key, const MappedType& value)
{
    this->_error = ER_SUCCESS;
    size_t index = findIndex(key);
    if (index != this->_size)
    {
        this->_data[index].value = value;
        return ;
    }
    if (this->_size == this->_capacity)
    {
        resize(this->_capacity * 2);
        if (this->_error != ER_SUCCESS)
            return ;
    }
    construct_at(&this->_data[this->_size], Pair<Key, MappedType>(key, value));
    ++this->_size;
    return ;
}

template <typename Key, typename MappedType>
Pair<Key, MappedType> *ft_map<Key, MappedType>::find(const Key& key)
{
    size_t index = 0;
    while (index < this->_size)
    {
        if (this->_data[index].key == key)
            return (&this->_data[index]);
        index++;
    }
    return (ft_nullptr);
}

template <typename Key, typename MappedType>
const Pair<Key, MappedType> *ft_map<Key, MappedType>::find(const Key& key) const
{
    size_t index = 0;
    while (index < this->_size)
    {
        if (this->_data[index].key == key)
            return (&this->_data[index]);
        index++;
    }
    return (ft_nullptr);
}

template <typename Key, typename MappedType>
void ft_map<Key, MappedType>::remove(const Key& key)
{
    size_t index = 0;
    while (index < this->_size)
    {
        if (this->_data[index].key == key)
        {
            destroy_at(&this->_data[index]);
            if (index != this->_size - 1)
            {
                construct_at(&this->_data[index], std::move(this->_data[this->_size - 1]));
                destroy_at(&this->_data[this->_size - 1]);
            }
            --this->_size;
            return ;
        }
        index++;
    }
    return ;
}

template <typename Key, typename MappedType>
bool ft_map<Key, MappedType>::empty() const
{
    return (this->_size == 0);
}

template <typename Key, typename MappedType>
void ft_map<Key, MappedType>::clear()
{
    size_t index = 0;
    while (index < this->_size)
    {
        destroy_at(&this->_data[index]);
        index++;
    }
    this->_size = 0;
    return ;
}

template <typename Key, typename MappedType>
size_t ft_map<Key, MappedType>::getSize() const
{
    return (this->_size);
}

template <typename Key, typename MappedType>
size_t ft_map<Key, MappedType>::getCapacity() const
{
    return (this->_capacity);
}

template <typename Key, typename MappedType>
int ft_map<Key, MappedType>::getError() const
{
    return (this->_error);
}

template<typename Key, typename MappedType>
void ft_map<Key, MappedType>::setError(int error) const
{
    ft_errno = error;
    this->_error = error;
    return ;
}

template <typename Key, typename MappedType>
void ft_map<Key, MappedType>::resize(size_t newCapacity)
{
    this->_error = ER_SUCCESS;
    void* rawMemory = cma_malloc(sizeof(Pair<Key, MappedType>) * newCapacity);
    if (!rawMemory)
    {
        this->setError(SHARED_PTR_ALLOCATION_FAILED);
        return ;
    }
    Pair<Key, MappedType>* newData = static_cast<Pair<Key, MappedType>*>(rawMemory);
	size_t index = 0;
    while (index < this->_size)
    {
        construct_at(&newData[index], std::move(this->_data[index]));
        destroy_at(&this->_data[index]);
		index++;
    }
    cma_free(this->_data);
    this->_data = newData;
    this->_capacity = newCapacity;
    return ;
}

template <typename Key, typename MappedType>
size_t ft_map<Key, MappedType>::findIndex(const Key& key) const
{
    size_t index = 0;
    while  (index < this->_size)
    {
        if (this->_data[index].key == key)
            return (index);
        index++;
    }
    return (this->_size);
}

template <typename Key, typename MappedType>
Pair<Key, MappedType>* ft_map<Key, MappedType>::end()
{
    return (this->_data + this->_size);
}

template <typename Key, typename MappedType>
const Pair<Key, MappedType>* ft_map<Key, MappedType>::end() const
{
    return (this->_data + this->_size);
}

template <typename Key, typename MappedType>
MappedType& ft_map<Key, MappedType>::at(const Key& key)
{
    static MappedType errorMappedType = MappedType();
    size_t index = findIndex(key);
    if (this->_size == 0 || index == this->_size)
    {
        this->setError(UNORD_MAP_UNKNOWN);
        return errorMappedType;
    }
    return this->_data[index].value;
}

template <typename Key, typename MappedType>
const MappedType& ft_map<Key, MappedType>::at(const Key& key) const
{
    static MappedType errorMappedType = MappedType();
    size_t index = findIndex(key);
    if (this->_size == 0 || index == this->_size)
    {
        this->setError(UNORD_MAP_UNKNOWN);
        return errorMappedType;
    }
    return this->_data[index].value;
}

#endif
