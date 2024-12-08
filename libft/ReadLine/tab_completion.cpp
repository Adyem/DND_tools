#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "../Printf/printf.hpp"
#include "../Libft/libft.hpp"
#include "readline_internal.hpp"

static void rl_find_word_start_and_prefix(readline_state_t *state, char *prefix, int *prefix_len)
{
    state->word_start = state->pos - 1;
    while (state->word_start >= 0 && state->buffer[state->word_start] != ' ')
        state->word_start--;
    state->word_start++;
    *prefix_len = state->pos - state->word_start;
    if (*prefix_len == 0)
        return ;
    ft_memcpy(prefix, &state->buffer[state->word_start], *prefix_len);
    prefix[*prefix_len] = '\0';
	return ;
}

static void rl_gather_matching_suggestions(readline_state_t *state, const char *prefix, int prefix_len)
{
    state->current_match_count = 0;
    for (int i = 0; i < suggestion_count; i++)
	{
        if (ft_strncmp(suggestions[i], prefix, prefix_len) == 0)
            state->current_matches[state->current_match_count++] = suggestions[i];
    }
	return ;
}

static int rl_resize_buffer_if_needed(readline_state_t *state, int required_size)
{
    if (required_size >= state->bufsize)
	{
        int new_bufsize = state->bufsize;
        while (required_size >= new_bufsize)
            new_bufsize *= 2;
        state->buffer = rl_resize_buffer(state->buffer, state->bufsize, new_bufsize);
		if (!state->buffer)
			return (-1);
        state->bufsize = new_bufsize;
    }
	return (0);
}

static int rl_apply_completion(readline_state_t *state, const char *completion)
{
    int completion_len = ft_strlen(completion);
    state->pos = state->word_start;
    state->buffer[state->pos] = '\0';
    int required_size = state->pos + completion_len;
    if (rl_resize_buffer_if_needed(state, required_size) == -1)
		return (-1);
    strcpy(&state->buffer[state->pos], completion);
    state->pos += completion_len;
    state->buffer[state->pos] = '\0';
	return (0);
}

static void rl_update_display(const char *prompt, readline_state_t *state)
{
    rl_clear_line(prompt, state->buffer);
    pf_printf("%s%s", prompt, state->buffer);
    state->prev_buffer_length = ft_strlen(state->buffer);
    fflush(stdout);
	return ;
}

int rl_handle_tab_completion(readline_state_t *state, const char *prompt)
{
    if (!state->in_completion_mode)
	{
        char prefix[INITIAL_BUFFER_SIZE];
        int prefix_len;
        rl_find_word_start_and_prefix(state, prefix, &prefix_len);
        if (prefix_len == 0)
            return (0);
        rl_gather_matching_suggestions(state, prefix, prefix_len);
		if (state->current_match_count == 0)
		{
            pf_printf("\a");
            fflush(stdout);
        }
		else
		{
            state->in_completion_mode = 1;
            state->current_match_index = 0;
        }
    }
    if (state->in_completion_mode && state->current_match_count > 0)
	{
        const char *completion = state->current_matches[state->current_match_index];
        if (rl_apply_completion(state, completion))
			return (-1);
        rl_update_display(prompt, state);
        state->current_match_index = (state->current_match_index + 1) % state->current_match_count;
    }
	return (0);
}
