#ifndef PAIR_HPP
# define PAIR_HPP

template <typename KeyType, typename ValueType>
struct Pair
{
    KeyType  key;
    ValueType value;

    Pair() = default;
	Pair(const KeyType &k, const ValueType &v);
};

template <typename KeyType, typename ValueType>
Pair<KeyType, ValueType>::Pair(const KeyType &k, const ValueType &v)
        : key(k), value(v)
{
	return ;
}

template <typename KeyType, typename ValueType>
Pair<KeyType, ValueType> ft_make_pair(KeyType key, ValueType value)
{
    return Pair<KeyType, ValueType>(key, value);
}

#endif
