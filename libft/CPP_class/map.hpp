#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "../CMA/CMA.hpp"
#include "../Errno/errno.hpp"
#include "nullptr.hpp"
#include <cstddef>

template <typename Key, typename MappedType>
class Map
{
    private:
        Pair<Key, MappedType>*   _data;
        std::size_t              _capacity;
        std::size_t              _size;
        bool                     _critical;
        int                      _error;

        void        resize(std::size_t newCapacity);
        std::size_t findIndex(const Key& key) const;

    public:
        Map(std::size_t initialCapacity = 10, bool criticality = false);
        Map(const Map& other);
        Map& operator=(const Map& other);
        Map(Map&& other) noexcept;
        Map& operator=(Map&& other) noexcept;
        ~Map();

        void        insert(const Key& key, const MappedType& value);
        MappedType* find(const Key& key);
        void        remove(const Key& key);
        bool        empty() const;
        void        clear();
        void        setError(int error);
        std::size_t getSize() const;
        std::size_t getCapacity() const;
        int         getError() const;
};

template <typename Key, typename MappedType>
Map<Key, MappedType>::Map(std::size_t initialCapacity, bool criticality)
    : _capacity(initialCapacity), _size(0), _critical(criticality), _error(ER_SUCCESS)
{
    this->_data = static_cast<Pair<Key, MappedType>*>(cma_malloc(sizeof(Pair<Key, MappedType>)
				* this->_capacity, this->_critical));
	if (!this->_data)
        this->setError(SHARED_PTR_ALLOCATION_FAILED);
	return ;
}

template <typename Key, typename MappedType>
Map<Key, MappedType>::Map(const Map<Key, MappedType>& other)
    : _capacity(other._capacity), _size(other._size), _critical(other._critical),
	_error(other._error)
{
	if (other._data != ft_nullptr && this->_size > 0)
	{
        this->_data = static_cast<Pair<Key, MappedType>*>(cma_malloc(sizeof(Pair<Key, MappedType>)
					* this->_capacity, this->_critical));
        if (!this->_data)
        {
            this->setError(SHARED_PTR_ALLOCATION_FAILED);
            this->_size = 0;
            this->_capacity = 0;
            return;
        }
        for (std::size_t i = 0; i < this->_size; ++i)
            this->_data[i] = other._data[i];
	}
	else
        this->_data = ft_nullptr;
	return ;
}

template <typename Key, typename MappedType>
Map<Key, MappedType>& Map<Key, MappedType>::operator=(const Map<Key, MappedType>& other)
{
    if (this != &other)
    {
        Pair<Key, MappedType>* newData = ft_nullptr;
        if (other._data != ft_nullptr && other._size > 0)
        {
            newData = static_cast<Pair<Key, MappedType>*>(cma_malloc(sizeof(Pair<Key, MappedType>)
						* other._capacity, other._critical));
            if (!newData)
            {
                this->setError(SHARED_PTR_ALLOCATION_FAILED);
                return *this;
            }
            for (std::size_t i = 0; i < other._size; ++i)
            {
                newData[i] = other._data[i];
            }
        }
        cma_free(this->_data);
        this->_data = newData;
        this->_capacity = other._capacity;
        this->_size = other._size;
        this->_critical = other._critical;
        this->_error = other._error;
    }
    return (*this);
}

template <typename Key, typename MappedType>
Map<Key, MappedType>::Map(Map<Key, MappedType>&& other) noexcept
    : _data(other._data), _capacity(other._capacity), _size(other._size), _critical(other._critical), _error(other._error)
{
    other._data = ft_nullptr;
    other._capacity = 0;
    other._size = 0;
    other._critical = false;
    other._error = ER_SUCCESS;
	return ;
}

template <typename Key, typename MappedType>
Map<Key, MappedType>& Map<Key, MappedType>::operator=(Map<Key, MappedType>&& other) noexcept
{
    if (this != &other)
    {
        cma_free(this->_data);

        this->_data = other._data;
        this->_capacity = other._capacity;
        this->_size = other._size;
        this->_critical = other._critical;
        this->_error = other._error;

        other._data = ft_nullptr;
        other._capacity = 0;
        other._size = 0;
        other._critical = false;
        other._error = ER_SUCCESS;
    }
    return (*this);
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::insert(const Key& key, const MappedType& value)
{
    this->_error = ER_SUCCESS;
    std::size_t index = findIndex(key);
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
    this->_data[this->_size++] = Pair<Key, MappedType>{key, value};
	return ;
}

template <typename Key, typename MappedType>
MappedType* Map<Key, MappedType>::find(const Key& key)
{
    std::size_t i = 0;
    while (i < this->_size)
    {
        if (this->_data[i].key == key)
            return (&this->_data[i].value);
        i++;
    }
    return (ft_nullptr);
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::remove(const Key& key)
{
    std::size_t i = 0;
    while (i < this->_size)
    {
        if (this->_data[i].key == key)
        {
            this->_data[i] = this->_data[this->_size - 1];
            --this->_size;
            return ;
        }
        i++;
    }
    return ;
}

template <typename Key, typename MappedType>
bool Map<Key, MappedType>::empty() const
{
    return (this->_size == 0);
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::clear()
{
    this->_size = 0;
    return;
}

template <typename Key, typename MappedType>
std::size_t Map<Key, MappedType>::getSize() const
{
    return (this->_size);
}

template <typename Key, typename MappedType>
std::size_t Map<Key, MappedType>::getCapacity() const
{
    return (this->_capacity);
}

template <typename Key, typename MappedType>
int Map<Key, MappedType>::getError() const
{
    return (this->_error);
}

template<typename key, typename MappedType>
void Map<key, MappedType>::setError(int error)
{
	ft_errno = error;
	this->_error = error;
	return ;
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::resize(std::size_t newCapacity)
{
    this->_error = ER_SUCCESS;
    Pair<Key, MappedType>* newData = static_cast<Pair<Key,
		MappedType>*>(cma_malloc(sizeof(Pair<Key, MappedType>) * newCapacity, this->_critical));
    if (!newData)
    {
		this->setError(SHARED_PTR_ALLOCATION_FAILED);
        return ;
    }
    std::size_t i = 0;
    while (i < this->_size)
    {
        newData[i] = this->_data[i];
        i++;
    }
    cma_free(this->_data);
    this->_data = newData;
    this->_capacity = newCapacity;
	return ;
}

template <typename Key, typename MappedType>
std::size_t Map<Key, MappedType>::findIndex(const Key& key) const
{
    std::size_t i = 0;
    while (i < this->_size)
    {
        if (this->_data[i].key == key)
            return (i);
        i++;
    }
    return (this->_size);
}

#endif
