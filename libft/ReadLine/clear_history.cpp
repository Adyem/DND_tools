#include "readline.hpp"
#include "../CMA/CMA.hpp"

void clear_history()
{
	int	i;

	i = 0;
    while (i < history_count)
	{
        cma_free(history[i]);
		history[i] = NULL;
		i++;
    }
    history_count = 0;
}
