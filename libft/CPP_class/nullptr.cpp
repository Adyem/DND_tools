#include "nullptr.hpp"

namespace ft
{
	const nullptr_t ft_nullptr_instance [[maybe_unused]] = nullptr_t{};

	void nullptr_t::operator&() const [[maybe_unused]] {}

}
