#ifndef NULLPTR_HPP
# define NULLPTR_HPP

struct ft_nullptr_t
{
    template <typename T>
    operator T*() const { return 0; }

    template <typename C, typename T>
    operator T C::*() const { return 0; }

private:
    void operator&() const;
};

#define ft_nullptr (ft_nullptr_t{})

#endif
