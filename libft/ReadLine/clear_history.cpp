#include "readline.hpp"
#include "readline_internal.hpp"
#include "../CMA/CMA.hpp"

void rl_clear_history()
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
	return ;
}
