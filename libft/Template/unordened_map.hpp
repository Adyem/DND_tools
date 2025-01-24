#ifndef FT_UNORD_MAP_HPP
#define FT_UNORD_MAP_HPP

#include "pair.hpp"
#include "constructor.hpp"
#include "../CMA/CMA.hpp"
#include "../Errno/errno.hpp"
#include "../CPP_class/nullptr.hpp"
#include <cstddef>
#include <functional>

template <typename Key, typename MappedType>
class ft_unord_map
{
	private:
    	Pair<Key, MappedType>*  _data;
    	bool*                   _occupied;
    	size_t                  _capacity;
    	size_t                  _size;
    	mutable int             _error;

    	void    resize(size_t newCapacity);
    	size_t  findIndex(const Key& key) const;
    	void    setError(int error) const;
    	size_t  hashKey(const Key& key) const;

	public:
    	ft_unord_map(size_t initialCapacity = 10);
    	ft_unord_map(const ft_unord_map& other);
    	ft_unord_map& operator=(const ft_unord_map& other);
    	ft_unord_map(ft_unord_map&& other) noexcept;
    	ft_unord_map& operator=(ft_unord_map&& other) noexcept;
    	~ft_unord_map();

    	void                  insert(const Key& key, const MappedType& value);
    	Pair<Key, MappedType>* find(const Key& key);
    	const Pair<Key, MappedType>* find(const Key& key) const;
    	void                  remove(const Key& key);
    	bool                  empty() const;
    	void                  clear();
    	size_t                getSize() const;
    	size_t                getCapacity() const;
    	int                   getError() const;
    	Pair<Key, MappedType>* end();
    	const Pair<Key, MappedType>* end() const;
    	MappedType&           at(const Key& key);
    	const MappedType&     at(const Key& key) const;
};

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::ft_unord_map(size_t initialCapacity)
    : _capacity(initialCapacity), _size(0), _error(ER_SUCCESS)
{
    void* rawData = cma_malloc(sizeof(Pair<Key, MappedType>) * this->_capacity);
    if (!rawData)
    {
        this->setError(SHARED_PTR_ALLOCATION_FAILED);
        this->_data = ft_nullptr;
        this->_occupied = ft_nullptr;
        return ;
    }
    this->_data = static_cast<Pair<Key, MappedType>*>(rawData);
    void* rawOccupied = cma_malloc(sizeof(bool) * this->_capacity);
    if (!rawOccupied)
    {
        this->setError(SHARED_PTR_ALLOCATION_FAILED);
        cma_free(this->_data);
        this->_data = ft_nullptr;
        this->_occupied = ft_nullptr;
        return ;
    }
    this->_occupied = static_cast<bool*>(rawOccupied);
    size_t i = 0;
    while (i < this->_capacity)
    {
        this->_occupied[i] = false;
        i++;
    }
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::ft_unord_map(const ft_unord_map<Key, MappedType>& other)
    : _capacity(other._capacity), _size(other._size), _error(other._error)
{
    if (other._data != ft_nullptr && this->_size > 0)
    {
        void* rawData = cma_malloc(sizeof(Pair<Key, MappedType>) * this->_capacity);
        if (!rawData)
        {
            this->setError(SHARED_PTR_ALLOCATION_FAILED);
            this->_data = ft_nullptr;
            this->_occupied = ft_nullptr;
            this->_size = 0;
            this->_capacity = 0;
            return ;
        }
        this->_data = static_cast<Pair<Key, MappedType>*>(rawData);
        void* rawOccupied = cma_malloc(sizeof(bool) * this->_capacity);
        if (!rawOccupied)
        {
            this->setError(SHARED_PTR_ALLOCATION_FAILED);
            cma_free(this->_data);
            this->_data = ft_nullptr;
            this->_occupied = ft_nullptr;
            this->_size = 0;
            this->_capacity = 0;
            return ;
        }
        this->_occupied = static_cast<bool*>(rawOccupied);
        size_t i = 0;
        while (i < this->_capacity)
        {
            this->_occupied[i] = false;
            i++;
        }
        size_t index = 0;
        size_t count = 0;
        while (count < other._size && index < other._capacity)
        {
            if (other._occupied[index])
            {
                construct_at(&this->_data[index], other._data[index]);
                this->_occupied[index] = true;
                count++;
            }
            index++;
        }
    }
    else
    {
        this->_data = ft_nullptr;
        this->_occupied = ft_nullptr;
    }
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>& ft_unord_map<Key, MappedType>::operator=(const ft_unord_map<Key, MappedType>& other)
{
    if (this != &other)
    {
        if (this->_data != ft_nullptr)
        {
            size_t i = 0;
            size_t count = 0;
            while (count < this->_size && i < this->_capacity)
            {
                if (this->_occupied[i])
                {
                    destroy_at(&this->_data[i]);
                    count++;
                }
                i++;
            }
            cma_free(this->_data);
            cma_free(this->_occupied);
        }
        this->_capacity = other._capacity;
        this->_size = other._size;
        this->_error = other._error;
        if (other._data != ft_nullptr && other._size > 0)
        {
            void* rawData = cma_malloc(sizeof(Pair<Key, MappedType>) * other._capacity);
            if (!rawData)
            {
                this->setError(SHARED_PTR_ALLOCATION_FAILED);
                this->_data = ft_nullptr;
                this->_occupied = ft_nullptr;
                this->_size = 0;
                this->_capacity = 0;
                return (*this);
            }
            this->_data = static_cast<Pair<Key, MappedType>*>(rawData);
            void* rawOccupied = cma_malloc(sizeof(bool) * other._capacity);
            if (!rawOccupied)
            {
                this->setError(SHARED_PTR_ALLOCATION_FAILED);
                cma_free(this->_data);
                this->_data = ft_nullptr;
                this->_occupied = ft_nullptr;
                this->_size = 0;
                this->_capacity = 0;
                return (*this);
            }
            this->_occupied = static_cast<bool*>(rawOccupied);
            size_t i = 0;
            while (i < this->_capacity)
            {
                this->_occupied[i] = false;
                i++;
            }
            size_t index = 0;
            size_t count = 0;
            while (count < other._size && index < other._capacity)
            {
                if (other._occupied[index])
                {
                    construct_at(&this->_data[index], other._data[index]);
                    this->_occupied[index] = true;
                    count++;
                }
                index++;
            }
        }
        else
        {
            this->_data = ft_nullptr;
            this->_occupied = ft_nullptr;
        }
    }
    return (*this);
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::ft_unord_map(ft_unord_map<Key, MappedType>&& other) noexcept
    : _data(other._data), _occupied(other._occupied), _capacity(other._capacity), _size(other._size),
      _error(other._error)
{
    other._data = ft_nullptr;
    other._occupied = ft_nullptr;
    other._capacity = 0;
    other._size = 0;
    other._error = ER_SUCCESS;
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>& ft_unord_map<Key, MappedType>::operator=(ft_unord_map<Key, MappedType>&& other) noexcept
{
    if (this != &other)
    {
        if (this->_data != ft_nullptr)
        {
            size_t i = 0;
            size_t count = 0;
            while (count < this->_size && i < this->_capacity)
            {
                if (this->_occupied[i])
                {
                    destroy_at(&this->_data[i]);
                    count++;
                }
                i++;
            }
            cma_free(this->_data);
            cma_free(this->_occupied);
        }
        this->_data = other._data;
        this->_occupied = other._occupied;
        this->_capacity = other._capacity;
        this->_size = other._size;
        this->_error = other._error;
        other._data = ft_nullptr;
        other._occupied = ft_nullptr;
        other._capacity = 0;
        other._size = 0;
        other._error = ER_SUCCESS;
    }
    return *this;
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::~ft_unord_map()
{
    if (this->_data != ft_nullptr)
    {
        size_t i = 0;
        size_t count = 0;
        while (count < this->_size && i < this->_capacity)
        {
            if (this->_occupied[i])
            {
                destroy_at(&this->_data[i]);
                count++;
            }
            i++;
        }
        cma_free(this->_data);
        cma_free(this->_occupied);
    }
}

template <typename Key, typename MappedType>
bool ft_unord_map<Key, MappedType>::empty() const
{
    return (this->_size == 0);
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::clear()
{
    size_t i = 0;
    size_t count = 0;
    while (count < this->_size && i < this->_capacity)
    {
        if (this->_occupied[i])
        {
            destroy_at(&this->_data[i]);
            this->_occupied[i] = false;
            count++;
        }
        i++;
    }
    this->_size = 0;
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::getSize() const
{
    return (this->_size);
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::getCapacity() const
{
    return (this->_capacity);
}

template <typename Key, typename MappedType>
int ft_unord_map<Key, MappedType>::getError() const
{
    return (this->_error);
}

template<typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::setError(int error) const
{
    ft_errno = error;
    this->_error = error;
}

template <typename Key, typename MappedType>
Pair<Key, MappedType>* ft_unord_map<Key, MappedType>::end()
{
    return (this->_data + this->_capacity);
}

template <typename Key, typename MappedType>
const Pair<Key, MappedType>* ft_unord_map<Key, MappedType>::end() const
{
    return (this->_data + this->_capacity);
}

template <typename Key, typename MappedType>
MappedType& ft_unord_map<Key, MappedType>::at(const Key& key)
{
    static MappedType errorMappedType = MappedType();
    size_t index = this->findIndex(key);
    if (index == this->_capacity)
    {
        this->setError(UNORD_MAP_UNKNOWN);
        return errorMappedType;
    }
    return this->_data[index].value;
}

template <typename Key, typename MappedType>
const MappedType& ft_unord_map<Key, MappedType>::at(const Key& key) const
{
    static MappedType errorMappedType = MappedType();
    size_t index = this->findIndex(key);
    if (index == this->_capacity)
    {
        this->setError(UNORD_MAP_UNKNOWN);
        return errorMappedType;
    }
    return this->_data[index].value;
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::insert(const Key& key, const MappedType& value)
{
    this->_error = ER_SUCCESS;
    size_t idx = this->findIndex(key);
    if (idx != this->_capacity)
    {
        this->_data[idx].value = value;
        return ;
    }
    if ((this->_size * 2) >= this->_capacity)
    {
        resize(this->_capacity * 2);
        if (this->_error != ER_SUCCESS)
            return ;
    }
    size_t start = hashKey(key);
    size_t i = start;
    while (true)
    {
        if (!this->_occupied[i])
        {
            construct_at(&this->_data[i], Pair<Key, MappedType>(key, value));
            this->_occupied[i] = true;
            ++this->_size;
            return ;
        }
        i = (i + 1) % this->_capacity;
        if (i == start)
            return ;
    }
}

template <typename Key, typename MappedType>
Pair<Key, MappedType>* ft_unord_map<Key, MappedType>::find(const Key& key)
{
    size_t idx = this->findIndex(key);
    if (idx == this->_capacity)
        return (ft_nullptr);
    return (&this->_data[idx]);
}

template <typename Key, typename MappedType>
const Pair<Key, MappedType>* ft_unord_map<Key, MappedType>::find(const Key& key) const
{
    size_t idx = this->findIndex(key);
    if (idx == this->_capacity)
        return (ft_nullptr);
    return (&this->_data[idx]);
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::remove(const Key& key)
{
    size_t idx = this->findIndex(key);
    if (idx == this->_capacity)
        return ;
    destroy_at(&this->_data[idx]);
    this->_occupied[idx] = false;
    --this->_size;
    size_t next = (idx + 1) % this->_capacity;
    while (this->_occupied[next])
    {
        size_t h = hashKey(this->_data[next].key);
        if ((next > idx && (h <= idx || h > next)) || (next < idx && (h <= idx && h > next)))
        {
            construct_at(&this->_data[idx], std::move(this->_data[next]));
            destroy_at(&this->_data[next]);
            this->_occupied[idx] = true;
            this->_occupied[next] = false;
            idx = next;
        }
        next = (next + 1) % this->_capacity;
    }
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::resize(size_t newCapacity)
{
    this->_error = ER_SUCCESS;
    void* rawData = cma_malloc(sizeof(Pair<Key, MappedType>) * newCapacity);
    if (!rawData)
    {
        this->setError(SHARED_PTR_ALLOCATION_FAILED);
        return ;
    }
    Pair<Key, MappedType>* newData = static_cast<Pair<Key, MappedType>*>(rawData);
    void* rawOccupied = cma_malloc(sizeof(bool) * newCapacity);
    if (!rawOccupied)
    {
        this->setError(SHARED_PTR_ALLOCATION_FAILED);
        cma_free(newData);
        return ;
    }
    bool* newOcc = static_cast<bool*>(rawOccupied);
    size_t i = 0;
    while (i < newCapacity)
    {
        newOcc[i] = false;
        i++;
    }
    size_t oldCap = this->_capacity;
    Pair<Key, MappedType>* oldData = this->_data;
    bool* oldOcc = this->_occupied;
    this->_data = newData;
    this->_occupied = newOcc;
    this->_capacity = newCapacity;
    size_t oldSize = this->_size;
    this->_size = 0;
    i = 0;
    size_t count = 0;
    while (count < oldSize && i < oldCap)
    {
        if (oldOcc[i])
        {
            insert(oldData[i].key, oldData[i].value);
            destroy_at(&oldData[i]);
            count++;
        }
        i++;
    }
    cma_free(oldData);
    cma_free(oldOcc);
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::hashKey(const Key& key) const
{
    static std::hash<Key> hf;
    return hf(key) % this->_capacity;
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::findIndex(const Key& key) const
{
    if (this->_size == 0)
        return (this->_capacity);
    size_t start = hashKey(key);
    size_t i = start;
    while (true)
    {
        if (!this->_occupied[i])
            return (this->_capacity);
        if (this->_data[i].key == key)
            return (i);
        i = (i + 1) % this->_capacity;
        if (i == start)
            return (this->_capacity);
    }
}

#endif
