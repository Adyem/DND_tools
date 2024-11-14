#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "../CMA/CMA.hpp"
#include "nullptr.hpp"
#include <cstddef>

template <typename Key, typename MappedType>
class Map
{
    private:
        Pair<Key, MappedType>* data;
        std::size_t             capacity;
        std::size_t             size_;
        bool                    critical;
        bool                    error;

    public:
        Map(std::size_t initialCapacity = 10, bool criticality = false);
        ~Map();

        void        insert(const Key& key, const MappedType& value);
        MappedType* find(const Key& key);
        void        remove(const Key& key);
        bool        empty() const;
        void        clear();
        std::size_t getSize() const;
        std::size_t getCapacity() const;
        bool        getError() const;

    private:
        void        resize(std::size_t newCapacity);
        std::size_t findIndex(const Key& key) const;
};

template <typename Key, typename MappedType>
Map<Key, MappedType>::Map(std::size_t initialCapacity, bool criticality)
    : capacity(initialCapacity), size_(0), critical(criticality), error(false)
{
    data = static_cast<Pair<Key, MappedType>*>(cma_malloc(sizeof(Pair<Key, MappedType>) * capacity, critical));
    if (!data)
        error = true;
    return;
}

template <typename Key, typename MappedType>
Map<Key, MappedType>::~Map()
{
    clear();
    cma_free(data);
    return;
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::insert(const Key& key, const MappedType& value)
{
    std::size_t index = findIndex(key);
    if (index != size_)
    {
        data[index].value = value;
        return;
    }

    if (size_ == capacity)
    {
        resize(capacity * 2);
        if (error)
            return;
    }
    data[size_++] = Pair<Key, MappedType>{key, value};
    return;
}

template <typename Key, typename MappedType>
MappedType* Map<Key, MappedType>::find(const Key& key)
{
    std::size_t i = 0;
    while (i < size_)
    {
        if (data[i].key == key)
            return (&data[i].value);
        i++;
    }
    return (ft_nullptr);
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::remove(const Key& key)
{
    std::size_t i = 0;
    while (i < size_)
    {
        if (data[i].key == key)
        {
            data[i] = data[size_ - 1];
            --size_;
            return;
        }
        i++;
    }
    return;
}

template <typename Key, typename MappedType>
bool Map<Key, MappedType>::empty() const
{
    return (size_ == 0);
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::clear()
{
    size_ = 0;
    return;
}

template <typename Key, typename MappedType>
std::size_t Map<Key, MappedType>::getSize() const
{
    return (size_);
}

template <typename Key, typename MappedType>
std::size_t Map<Key, MappedType>::getCapacity() const
{
    return (capacity);
}

template <typename Key, typename MappedType>
bool Map<Key, MappedType>::getError() const
{
    return (error);
}

template <typename Key, typename MappedType>
void Map<Key, MappedType>::resize(std::size_t newCapacity)
{
    Pair<Key, MappedType>* newData = static_cast<Pair<Key, MappedType>*>(cma_malloc(sizeof(Pair<Key, MappedType>) * newCapacity, critical));
    if (!newData)
    {
        error = true;
        return;
    }
    std::size_t i = 0;
    while (i < size_)
    {
        newData[i] = data[i];
        i++;
    }
    cma_free(data);
    data = newData;
    capacity = newCapacity;
    return;
}

template <typename Key, typename MappedType>
std::size_t Map<Key, MappedType>::findIndex(const Key& key) const
{
    std::size_t i = 0;
    while (i < size_)
    {
        if (data[i].key == key)
            return (i);
        i++;
    }
    return (size_);
}

#endif

