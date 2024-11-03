#ifndef MAP_HPP
#define MAP_HPP

# include "pair.hpp"
# include "../CMA/CMA.hpp"
# include <cstddef>

template <typename KeyType, typename ValueType>
class Map
{
	private:
    	Pair<KeyType, ValueType>	*data;
    	std::size_t					capacity;
    	std::size_t					size;
    	bool						critical;
    	bool						error;

	public:
    	Map(std::size_t initialCapacity = 10, bool criticality = false);
    	~Map();

    	void		insert(const KeyType& key, const ValueType& value);
    	ValueType	*find(const KeyType& key);
    	void		remove(const KeyType& key);
    	bool		empty() const;
    	void		clear();
    	std::size_t	getSize() const;
    	std::size_t	getCapacity() const;
		bool		getError() const;

	private:
	    void resize(std::size_t newCapacity);
    	std::size_t findIndex(const KeyType& key) const;
};

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(std::size_t initialCapacity, bool criticality)
    : capacity(initialCapacity), size(0), critical(criticality), error(false)
{
    data = static_cast<Pair<KeyType, ValueType>*>(cma_malloc(sizeof(Pair<KeyType, ValueType>)
				* capacity, critical));
	if (!data)
		error = true;
	return ;
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::~Map()
{
    clear();
    cma_free(data);
	return ;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    std::size_t index = findIndex(key);
    if (index != size)
    {
        data[index].value = value;
        return ;
    }

    if (size == capacity)
    {
        resize(capacity * 2);
        if (error)
            return ;
    }
    data[size++] = Pair<KeyType, ValueType>{key, value};
	return ;
}

template <typename KeyType, typename ValueType>
ValueType* Map<KeyType, ValueType>::find(const KeyType& key)
{
	std::size_t i = 0;
	while (i < size)
    {
        if (data[i].key == key)
            return (&data[i].value);
		i++;
    }
    return (nullptr);
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType& key)
{
	std::size_t i = 0;
    while (i < size)
    {
        if (data[i].key == key)
        {
            data[i] = data[size - 1];
            --size;
            return ;
        }
		i++;
    }
	return ;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::empty() const
{
    return (size == 0);
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::clear()
{
    size = 0;
	return ;
}

template <typename KeyType, typename ValueType>
std::size_t Map<KeyType, ValueType>::getSize() const
{
    return (size);
}

template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::getError() const
{
    return (error);
}

template <typename KeyType, typename ValueType>
std::size_t Map<KeyType, ValueType>::getCapacity() const
{
    return (capacity);
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::resize(std::size_t newCapacity)
{
    Pair<KeyType, ValueType>* newData = static_cast<Pair<KeyType,
		ValueType>*>(cma_malloc(sizeof(Pair<KeyType, ValueType>) * newCapacity, critical));
    if (!newData)
    {
        error = true;
        return ;
    }
	std::size_t i = 0;
    while (i < size)
	{
        newData[i] = data[i];
		i++;
	}
    cma_free(data);
    data = newData;
    capacity = newCapacity;
	return ;
}

template <typename KeyType, typename ValueType>
std::size_t Map<KeyType, ValueType>::findIndex(const KeyType& key) const
{
	std::size_t i = 0;
    while (i < size)
    {
        if (data[i].key == key)
            return (i);
		i++;
    }
    return (size);
}

#endif
