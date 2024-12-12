#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "../CMA/CMA.hpp"
#include "readline_internal.hpp"

void rl_open_log_file(readline_state_t *state)
{
	static int file_reset;

	if (file_reset == 0)
	{
		state->error_file.open("data/data--log", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		file_reset = 1;
	}
	else	
    	state->error_file.open("data/data--log", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (state->error_file != -1)
		state->error_file.printf("printing to log file\n");
	return ;
}

int rl_initialize_state(readline_state_t *state)
{
	if (rl_enable_raw_mode() == -1)
		return (1);
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
	rl_open_log_file(state);
	return (0);
}
