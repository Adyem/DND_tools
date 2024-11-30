#ifndef ITERATOR_HPP
# define ITERATOR_HPP

template <typename ValueType>
class Iterator
{
    public:
        Iterator(ValueType* ptr);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        Iterator(Iterator&& other) noexcept;
        Iterator& operator=(Iterator&& other) noexcept;
        ~Iterator() = default;
        Iterator operator++();
        bool operator!=(const Iterator& other) const;
        ValueType& operator*() const;

    private:
        ValueType* m_ptr;
};

template <typename ValueType>
Iterator<ValueType>::Iterator(ValueType* ptr) : m_ptr(ptr)
{
	return ;
}

template <typename ValueType>
Iterator<ValueType>::Iterator(const Iterator& other) : m_ptr(other.m_ptr)
{
	return ;
}

template <typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::operator=(const Iterator& other)
{
    if (this != &other)
        m_ptr = other.m_ptr;
    return (*this);
}

template <typename ValueType>
Iterator<ValueType>::Iterator(Iterator&& other) noexcept : m_ptr(other.m_ptr)
{
    other.m_ptr = nullptr;
	return ;
}

template <typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::operator=(Iterator&& other) noexcept
{
    if (this != &other)
    {
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }
    return (*this);
}

template <typename ValueType>
Iterator<ValueType> Iterator<ValueType>::operator++()
{
    ++m_ptr;
    return (*this);
}

template <typename ValueType>
bool Iterator<ValueType>::operator!=(const Iterator& other) const
{
    return (m_ptr != other.m_ptr);
}

template <typename ValueType>
ValueType& Iterator<ValueType>::operator*() const
{
    return (*m_ptr);
}

#endif
