#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "../CMA/CMA.hpp"
#include "readline_internal.hpp"

int rl_initialize_state(readline_state_t *state)
{
	state->bufsize = INITIAL_BUFFER_SIZE;
    state->buffer = (char *)cma_calloc(state->bufsize, sizeof(char), true);
    if (!state->buffer)
    {
        rl_disable_raw_mode();
        return (1);
    }
    state->pos = 0;
    state->prev_buffer_length = 0;
    state->history_index = history_count;
    state->in_completion_mode = 0;
    state->current_match_count = 0;
    state->current_match_index = 0;
    state->word_start = 0;
	return (0);
}
