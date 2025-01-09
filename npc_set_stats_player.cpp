#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "assert.h"
#include <cstddef>

int	ft_set_stat_player(size_t key_len, const char **field, const char *content)
{
	size_t		content_len;

	content_len = ft_strlen(content);
	assert(content_len >= key_len && "Content is shorter than key!");
	*field = cma_strdup(&content[key_len]);
	if (!*field || ft_check_player_entry(*field))
		return (-1);
	return (0);
}
