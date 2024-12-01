#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "../CMA/CMA.hpp"
#include "../Printf/ft_printf.hpp"
#include "readline_internal.hpp"
#include "readline.hpp"

void rl_add_suggestion(const char *word)
{
	for (int i = 0; i < suggestion_count; i++)
	{
        if (strcmp(suggestions[i], word) == 0)
            return ;
	}
	if (suggestion_count < MAX_SUGGESTIONS)
        suggestions[suggestion_count++] = cma_strdup(word, true);
	else
        pf_printf_fd(2, "Suggestion list full\n");
	return ;
}

void rl_clear_suggestions()
{
    for (int i = 0; i < suggestion_count; i++)
        cma_free(suggestions[i]);
    suggestion_count = 0;
	return ;
}
