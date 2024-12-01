#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "../CPP_class/nullptr.hpp"
#include "../Printf/ft_printf.hpp"
#include "readline_internal.hpp"
#include "readline.hpp"

struct termios orig_termios;
char *history[MAX_HISTORY];
int history_count = 0;
char *suggestions[MAX_SUGGESTIONS];
int suggestion_count = 0;

char *rl_readline(const char *prompt)
{
    readline_state_t state;

	if (rl_initialize_state(&state))
		return (ft_nullptr);
    rl_enable_raw_mode();
    pf_printf("%s", prompt);
    fflush(stdout);
    while (1)
    {
        int c = rl_read_key();
        if (c != '\t' && state.in_completion_mode)
        {
            state.in_completion_mode = 0;
            state.current_match_count = 0;
            state.current_match_index = 0;
        }
        if (c == '\r' || c == '\n')
        {
            pf_printf("\n");
            break;
        }
        else if (c == 127 || c == '\b')
            rl_handle_backspace(&state, prompt);
        else if (c == 27)
            rl_handle_escape_sequence(&state, prompt);
        else if (c == '\t')
            rl_handle_tab_completion(&state, prompt);
        else if (c >= 32 && c <= 126)
            rl_handle_printable_char(&state, c, prompt);
    }
    state.buffer[state.pos] = '\0';
    update_history(state.buffer);
    rl_disable_raw_mode();
    return (state.buffer);
}
