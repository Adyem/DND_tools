#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "../CPP_class/nullptr.hpp"
#include "../Printf/printf.hpp"
#include "../CMA/CMA.hpp"
#include "readline_internal.hpp"
#include "readline.hpp"

termios orig_termios;
char *history[MAX_HISTORY];
int history_count = 0;
char *suggestions[MAX_SUGGESTIONS];
int suggestion_count = 0;

static void rl_cleanup_state(readline_state_t *state)
{
    if (state->buffer)
	{
        cma_free(state->buffer);
        state->buffer = NULL;
    }
	return ;
}

char *rl_readline(const char *prompt)
{
    readline_state_t state;

    if (rl_initialize_state(&state))
        return (ft_nullptr);
    if (rl_enable_raw_mode() == -1)
	{
		rl_cleanup_state(&state);
		return (ft_nullptr);
	}
    pf_printf("%s", prompt);
    fflush(stdout);

    while (1)
    {
        int character = rl_read_key();

        if (character != '\t' && state.in_completion_mode)
        {
            state.in_completion_mode = 0;
            state.current_match_count = 0;
            state.current_match_index = 0;
        }
        if (character == '\r' || character == '\n')
        {
            pf_printf("\n");
            break;
        }
        else if (character == 127 || character == '\b')
            rl_handle_backspace(&state, prompt);
        else if (character == 27)
        {
            if (rl_handle_escape_sequence(&state, prompt) == -1)
            {
                rl_cleanup_state(&state);
                rl_disable_raw_mode();
                return (ft_nullptr);
            }
        }
        else if (character == '\t')
		{
            if (rl_handle_tab_completion(&state, prompt) == -1)
            {
                rl_cleanup_state(&state);
                rl_disable_raw_mode();
                return (ft_nullptr);
            }
		}
        else if (character >= 32 && character <= 126)
		{
			if (rl_handle_printable_char(&state, character, prompt) == -1)
            {
                rl_cleanup_state(&state);
                rl_disable_raw_mode();
                return (ft_nullptr);
            }
		}
    }
    state.buffer[state.pos] = '\0';
    update_history(state.buffer);
    rl_disable_raw_mode();
    return (state.buffer);
}
