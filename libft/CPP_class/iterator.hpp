#ifndef ITERATOR_HPP
# define ITERATOR_HPP

template <typename ValueType>
class Iterator
{
	public:
	    Iterator(ValueType* ptr);
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
