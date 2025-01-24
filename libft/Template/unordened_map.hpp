#ifndef FT_UNORD_MAP_HPP
#define FT_UNORD_MAP_HPP

#include "../CMA/CMA.hpp"
#include "../Errno/errno.hpp"
#include "../CPP_class/nullptr.hpp"
#include "constructor.hpp"
#include <cstddef>
#include <functional>

template <typename Key, typename MappedType>
struct ft_pair
{
    Key         first;
    MappedType  second;
    ft_pair();
    ft_pair(const Key& k, const MappedType& m);
};

template <typename Key, typename MappedType>
class ft_unord_map
{
private:
    ft_pair<Key, MappedType>*  _data;
    bool*                      _occupied;
    size_t                     _capacity;
    size_t                     _size;
    mutable int                _error;

    void    resize(size_t newCapacity);
    size_t  findIndex(const Key& key) const;
    void    setError(int error) const;
    size_t  hashKey(const Key& key) const;

public:
    class iterator
    {
    private:
        ft_pair<Key, MappedType>* _data;
        bool*                     _occupied;
        size_t                    _index;
        size_t                    _capacity;
        void                      skipUnoccupied();
    public:
        iterator(ft_pair<Key, MappedType>* data, bool* occ, size_t idx, size_t cap);
        ft_pair<Key, MappedType>& operator*() const;
        ft_pair<Key, MappedType>* operator->() const;
        iterator& operator++();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    class const_iterator
    {
    private:
        const ft_pair<Key, MappedType>* _data;
        const bool*                     _occupied;
        size_t                          _index;
        size_t                          _capacity;
        void                            skipUnoccupied();
    public:
        const_iterator(const ft_pair<Key, MappedType>* data, const bool* occ, size_t idx, size_t cap);
        const ft_pair<Key, MappedType>& operator*() const;
        const ft_pair<Key, MappedType>* operator->() const;
        const_iterator& operator++();
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
    };

    ft_unord_map(size_t initialCapacity = 10);
    ft_unord_map(const ft_unord_map& other);
    ft_unord_map& operator=(const ft_unord_map& other);
    ft_unord_map(ft_unord_map&& other) noexcept;
    ft_unord_map& operator=(ft_unord_map&& other) noexcept;
    ~ft_unord_map();

    void           insert(const Key& key, const MappedType& value);
    iterator       find(const Key& key);
    const_iterator find(const Key& key) const;
    void           remove(const Key& key);
    bool           empty() const;
    void           clear();
    size_t         getSize() const;
    size_t         getCapacity() const;
    int            getError() const;
    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end() const;
    MappedType&    at(const Key& key);
    const MappedType& at(const Key& key) const;
    MappedType&    operator[](const Key& key);
};

template <typename Key, typename MappedType>
ft_pair<Key, MappedType>::ft_pair() : first(), second()
{
	return ;
}

template <typename Key, typename MappedType>
ft_pair<Key, MappedType>::ft_pair(const Key& k, const MappedType& m) : first(k), second(m)
{
	return ;
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::iterator::iterator(ft_pair<Key, MappedType>* data, bool* occ, size_t idx, size_t cap)
    : _data(data), _occupied(occ), _index(idx), _capacity(cap)
{
    skipUnoccupied();
	return ;
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::iterator::skipUnoccupied()
{
    while (_index < _capacity && !_occupied[_index])
        ++_index;
	return ;
}

template <typename Key, typename MappedType>
ft_pair<Key, MappedType>& ft_unord_map<Key, MappedType>::iterator::operator*() const
{
    return (_data[_index]);
}

template <typename Key, typename MappedType>
ft_pair<Key, MappedType>* ft_unord_map<Key, MappedType>::iterator::operator->() const
{
    return (&_data[_index]);
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::iterator& ft_unord_map<Key, MappedType>::iterator::operator++()
{
    ++_index;
    skipUnoccupied();
    return (*this);
}

template <typename Key, typename MappedType>
bool ft_unord_map<Key, MappedType>::iterator::operator==(const iterator& other) const
{
    return (_data == other._data && _index == other._index);
}

template <typename Key, typename MappedType>
bool ft_unord_map<Key, MappedType>::iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::const_iterator::const_iterator(const ft_pair<Key, MappedType>* data, const bool* occ, size_t idx, size_t cap)
    : _data(data), _occupied(occ), _index(idx), _capacity(cap)
{
    skipUnoccupied();
	return ;
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::const_iterator::skipUnoccupied()
{
    while (_index < _capacity && !_occupied[_index])
        ++_index;
	return ;
}

template <typename Key, typename MappedType>
const ft_pair<Key, MappedType>& ft_unord_map<Key, MappedType>::const_iterator::operator*() const
{
    return (_data[_index]);
}

template <typename Key, typename MappedType>
const ft_pair<Key, MappedType>* ft_unord_map<Key, MappedType>::const_iterator::operator->() const
{
    return &_data[_index];
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::const_iterator& ft_unord_map<Key, MappedType>::const_iterator::operator++()
{
    ++_index;
    skipUnoccupied();
    return *this;
}

template <typename Key, typename MappedType>
bool ft_unord_map<Key, MappedType>::const_iterator::operator==(const const_iterator& other) const
{
    return (_data == other._data && _index == other._index);
}

template <typename Key, typename MappedType>
bool ft_unord_map<Key, MappedType>::const_iterator::operator!=(const const_iterator& other) const
{
    return !(*this == other);
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::ft_unord_map(size_t initialCapacity)
    : _capacity(initialCapacity), _size(0), _error(ER_SUCCESS)
{
    void* rawData = cma_malloc(sizeof(ft_pair<Key, MappedType>) * _capacity);
    if (!rawData)
    {
        setError(UNORD_MAP_MEMORY);
        _data = ft_nullptr;
        _occupied = ft_nullptr;
        return;
    }
    _data = static_cast<ft_pair<Key, MappedType>*>(rawData);
    void* rawOccupied = cma_malloc(sizeof(bool) * _capacity);
    if (!rawOccupied)
    {
        setError(UNORD_MAP_MEMORY);
        cma_free(_data);
        _data = ft_nullptr;
        _occupied = ft_nullptr;
        return;
    }
    _occupied = static_cast<bool*>(rawOccupied);
    size_t i = 0;
    while (i < _capacity)
    {
        _occupied[i] = false;
        i++;
    }
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::ft_unord_map(const ft_unord_map<Key, MappedType>& other)
    : _capacity(other._capacity), _size(other._size), _error(other._error)
{
    if (other._data != ft_nullptr && _size > 0)
    {
        void* rawData = cma_malloc(sizeof(ft_pair<Key, MappedType>) * _capacity);
        if (!rawData)
        {
            setError(UNORD_MAP_MEMORY);
            _data = ft_nullptr;
            _occupied = ft_nullptr;
            _size = 0;
            _capacity = 0;
            return;
        }
        _data = static_cast<ft_pair<Key, MappedType>*>(rawData);
        void* rawOccupied = cma_malloc(sizeof(bool) * _capacity);
        if (!rawOccupied)
        {
            setError(UNORD_MAP_MEMORY);
            cma_free(_data);
            _data = ft_nullptr;
            _occupied = ft_nullptr;
            _size = 0;
            _capacity = 0;
            return;
        }
        _occupied = static_cast<bool*>(rawOccupied);
        size_t i = 0;
        while (i < _capacity)
        {
            _occupied[i] = false;
            i++;
        }
        size_t index = 0;
        size_t count = 0;
        while (count < other._size && index < other._capacity)
        {
            if (other._occupied[index])
            {
                construct_at(&_data[index], other._data[index]);
                _occupied[index] = true;
                count++;
            }
            index++;
        }
    }
    else
    {
        _data = ft_nullptr;
        _occupied = ft_nullptr;
    }
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>& ft_unord_map<Key, MappedType>::operator=(const ft_unord_map<Key, MappedType>& other)
{
    if (this != &other)
    {
        if (_data != ft_nullptr)
        {
            size_t i = 0;
            size_t count = 0;
            while (count < _size && i < _capacity)
            {
                if (_occupied[i])
                {
                    destroy_at(&_data[i]);
                    count++;
                }
                i++;
            }
            cma_free(_data);
            cma_free(_occupied);
        }
        _capacity = other._capacity;
        _size = other._size;
        _error = other._error;
        if (other._data != ft_nullptr && other._size > 0)
        {
            void* rawData = cma_malloc(sizeof(ft_pair<Key, MappedType>) * other._capacity);
            if (!rawData)
            {
                setError(UNORD_MAP_MEMORY);
                _data = ft_nullptr;
                _occupied = ft_nullptr;
                _size = 0;
                _capacity = 0;
                return *this;
            }
            _data = static_cast<ft_pair<Key, MappedType>*>(rawData);
            void* rawOccupied = cma_malloc(sizeof(bool) * other._capacity);
            if (!rawOccupied)
            {
                setError(UNORD_MAP_MEMORY);
                cma_free(_data);
                _data = ft_nullptr;
                _occupied = ft_nullptr;
                _size = 0;
                _capacity = 0;
                return *this;
            }
            _occupied = static_cast<bool*>(rawOccupied);
            size_t i = 0;
            while (i < _capacity)
            {
                _occupied[i] = false;
                i++;
            }
            size_t index = 0;
            size_t count = 0;
            while (count < other._size && index < other._capacity)
            {
                if (other._occupied[index])
                {
                    construct_at(&_data[index], other._data[index]);
                    _occupied[index] = true;
                    count++;
                }
                index++;
            }
        }
        else
        {
            _data = ft_nullptr;
            _occupied = ft_nullptr;
        }
    }
    return *this;
}

template <typename Key, typename MappedType>
ft_unord_map<Key, MappedType>::ft_unord_map(ft_unord_map<Key, MappedType>&& other) noexcept
    : _data(other._data), _occupied(other._occupied), _capacity(other._capacity), _size(other._size), _error(other._error)
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
        if (_data != ft_nullptr)
        {
            size_t i = 0;
            size_t count = 0;
            while (count < _size && i < _capacity)
            {
                if (_occupied[i])
                {
                    destroy_at(&_data[i]);
                    count++;
                }
                i++;
            }
            cma_free(_data);
            cma_free(_occupied);
        }
        _data = other._data;
        _occupied = other._occupied;
        _capacity = other._capacity;
        _size = other._size;
        _error = other._error;
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
    if (_data != ft_nullptr)
    {
        size_t i = 0;
        size_t count = 0;
        while (count < _size && i < _capacity)
        {
            if (_occupied[i])
            {
                destroy_at(&_data[i]);
                count++;
            }
            i++;
        }
        cma_free(_data);
        cma_free(_occupied);
    }
}

template<typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::setError(int error) const
{
    ft_errno = error;
    _error = error;
	return ;
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::hashKey(const Key& key) const
{
    static std::hash<Key> hf;
    return (hf(key) % _capacity);
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::findIndex(const Key& key) const
{
    if (_size == 0)
        return _capacity;
    size_t start = hashKey(key);
    size_t i = start;
    while (true)
    {
        if (!_occupied[i])
            return _capacity;
        if (_data[i].first == key)
            return i;
        i = (i + 1) % _capacity;
        if (i == start)
            return (_capacity);
    }
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::resize(size_t newCapacity)
{
    _error = ER_SUCCESS;
    void* rawData = cma_malloc(sizeof(ft_pair<Key, MappedType>) * newCapacity);
    if (!rawData)
    {
        setError(UNORD_MAP_MEMORY);
        return;
    }
    ft_pair<Key, MappedType>* newData = static_cast<ft_pair<Key, MappedType>*>(rawData);
    void* rawOccupied = cma_malloc(sizeof(bool) * newCapacity);
    if (!rawOccupied)
    {
        setError(UNORD_MAP_MEMORY);
        cma_free(newData);
        return;
    }
    bool* newOcc = static_cast<bool*>(rawOccupied);
    size_t i = 0;
    while (i < newCapacity)
    {
        newOcc[i] = false;
        i++;
    }
    size_t oldCap = _capacity;
    ft_pair<Key, MappedType>* oldData = _data;
    bool* oldOcc = _occupied;
    _data = newData;
    _occupied = newOcc;
    _capacity = newCapacity;
    size_t oldSize = _size;
    _size = 0;
    i = 0;
    size_t count = 0;
    while (count < oldSize && i < oldCap)
    {
        if (oldOcc[i])
        {
            insert(oldData[i].first, oldData[i].second);
            destroy_at(&oldData[i]);
            count++;
        }
        i++;
    }
    cma_free(oldData);
    cma_free(oldOcc);
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::insert(const Key& key, const MappedType& value)
{
    _error = ER_SUCCESS;
    size_t idx = findIndex(key);
    if (idx != _capacity)
    {
        _data[idx].second = value;
        return;
    }
    if ((_size * 2) >= _capacity)
    {
        resize(_capacity * 2);
        if (_error != ER_SUCCESS)
            return;
    }
    size_t start = hashKey(key);
    size_t i = start;
    while (true)
    {
        if (!_occupied[i])
        {
            construct_at(&_data[i], ft_pair<Key, MappedType>(key, value));
            _occupied[i] = true;
            ++_size;
            return;
        }
        i = (i + 1) % _capacity;
        if (i == start)
            return;
    }
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::iterator ft_unord_map<Key, MappedType>::find(const Key& key)
{
    size_t idx = findIndex(key);
    if (idx == _capacity)
        return end();
    return iterator(_data, _occupied, idx, _capacity);
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::const_iterator ft_unord_map<Key, MappedType>::find(const Key& key) const
{
    size_t idx = findIndex(key);
    if (idx == _capacity)
        return end();
    return const_iterator(_data, _occupied, idx, _capacity);
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::remove(const Key& key)
{
    size_t idx = findIndex(key);
    if (idx == _capacity)
        return;
    destroy_at(&_data[idx]);
    _occupied[idx] = false;
    --_size;
    size_t next = (idx + 1) % _capacity;
    while (_occupied[next])
    {
        size_t h = hashKey(_data[next].first);
        if ((next > idx && (h <= idx || h > next)) || (next < idx && (h <= idx && h > next)))
        {
            construct_at(&_data[idx], std::move(_data[next]));
            destroy_at(&_data[next]);
            _occupied[idx] = true;
            _occupied[next] = false;
            idx = next;
        }
        next = (next + 1) % _capacity;
    }
}

template <typename Key, typename MappedType>
bool ft_unord_map<Key, MappedType>::empty() const
{
    return (_size == 0);
}

template <typename Key, typename MappedType>
void ft_unord_map<Key, MappedType>::clear()
{
    size_t i = 0;
    size_t count = 0;
    while (count < _size && i < _capacity)
    {
        if (_occupied[i])
        {
            destroy_at(&_data[i]);
            _occupied[i] = false;
            count++;
        }
        i++;
    }
    _size = 0;
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::getSize() const
{
    return _size;
}

template <typename Key, typename MappedType>
size_t ft_unord_map<Key, MappedType>::getCapacity() const
{
    return _capacity;
}

template <typename Key, typename MappedType>
int ft_unord_map<Key, MappedType>::getError() const
{
    return _error;
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::iterator ft_unord_map<Key, MappedType>::begin()
{
    return iterator(_data, _occupied, 0, _capacity);
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::iterator ft_unord_map<Key, MappedType>::end()
{
    return iterator(_data, _occupied, _capacity, _capacity);
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::const_iterator ft_unord_map<Key, MappedType>::begin() const
{
    return const_iterator(_data, _occupied, 0, _capacity);
}

template <typename Key, typename MappedType>
typename ft_unord_map<Key, MappedType>::const_iterator ft_unord_map<Key, MappedType>::end() const
{
    return const_iterator(_data, _occupied, _capacity, _capacity);
}

template <typename Key, typename MappedType>
MappedType& ft_unord_map<Key, MappedType>::at(const Key& key)
{
    static MappedType errorMappedType = MappedType();
    size_t idx = findIndex(key);
    if (idx == _capacity)
    {
        setError(UNORD_MAP_UNKNOWN);
        return errorMappedType;
    }
    return _data[idx].second;
}

template <typename Key, typename MappedType>
const MappedType& ft_unord_map<Key, MappedType>::at(const Key& key) const
{
    static MappedType errorMappedType = MappedType();
    size_t idx = findIndex(key);
    if (idx == _capacity)
    {
        setError(UNORD_MAP_UNKNOWN);
        return errorMappedType;
    }
    return _data[idx].second;
}

template <typename Key, typename MappedType>
MappedType& ft_unord_map<Key, MappedType>::operator[](const Key& key)
{
    _error = ER_SUCCESS;
    size_t idx = findIndex(key);
    if (idx != _capacity)
        return _data[idx].second;
    if ((_size * 2) >= _capacity)
    {
        resize(_capacity * 2);
        if (_error != ER_SUCCESS)
        {
            static MappedType errorVal = MappedType();
            return errorVal;
        }
    }
    size_t start = hashKey(key);
    size_t i = start;
    while (true)
    {
        if (!_occupied[i])
        {
            construct_at(&_data[i], ft_pair<Key, MappedType>(key, MappedType()));
            _occupied[i] = true;
            ++_size;
            return _data[i].second;
        }
        i = (i + 1) % _capacity;
        if (i == start)
            break;
    }
    static MappedType errorVal = MappedType();
    setError(UNORD_MAP_UNKNOWN);
    return errorVal;
}

#endif
