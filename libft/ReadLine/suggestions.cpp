#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "../CMA/CMA.hpp"
#include "../Printf/printf.hpp"
#include "readline_internal.hpp"
#include "readline.hpp"

void rl_add_suggestion(const char *word)
{
    int index = 0;
    while (index < suggestion_count)
    {
        if (strcmp(suggestions[index], word) == 0)
            return ;
        index++;
    }
    if (suggestion_count < MAX_SUGGESTIONS)
        suggestions[suggestion_count++] = cma_strdup(word, true);
    else
        pf_printf_fd(2, "Suggestion list full\n");
    return ;
}

void rl_clear_suggestions()
{
    int index = 0;
    while (index < suggestion_count)
    {
        cma_free(suggestions[index]);
        index++;
    }
    suggestion_count = 0;
    return ;
}
