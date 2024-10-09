#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "../CMA/CMA.hpp"
#include "../Printf/ft_printf.hpp"
#include "../Libft/libft.hpp"
#include "readline.hpp"

struct termios orig_termios;
char *history[MAX_HISTORY];
int history_count = 0;

char *suggestions[MAX_SUGGESTIONS];
int suggestion_count = 0;

static void rl_disable_raw_mode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    return;
}

static void rl_enable_raw_mode()
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(rl_disable_raw_mode);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    return;
}

static int rl_read_key()
{
    int nread;
    char c;

    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
        ;
    return (c);
}

static char *rl_resize_buffer(char *old_buffer, int current_size, int new_size)
{
    char *new_buffer = (char *)cma_malloc(new_size, true);

    if (!new_buffer)
    {
        ft_printf_fd(2, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    memcpy(new_buffer, old_buffer, current_size);
    cma_free(old_buffer);
    return new_buffer;
}

static void rl_clear_line(const char *prompt, int buffer_length)
{
    ft_printf("\r");
    int line_length = buffer_length + ft_strlen(prompt);
    for (int i = 0; i < line_length; i++)
    {
        ft_printf(" ");
    }
    ft_printf("\r");
    return;
}

void rl_add_suggestion(const char *word)
{
    for (int i = 0; i < suggestion_count; i++)
    {
        if (strcmp(suggestions[i], word) == 0)
            return;
    }
    if (suggestion_count < MAX_SUGGESTIONS)
        suggestions[suggestion_count++] = cma_strdup(word, true);
    else
        ft_printf_fd(2, "Suggestion list full\n");
    return;
}

void rl_clear_suggestions()
{
    for (int i = 0; i < suggestion_count; i++)
        cma_free(suggestions[i]);
    suggestion_count = 0;
    return;
}

char *rl_readline(const char *prompt)
{
    int bufsize = INITIAL_BUFFER_SIZE;
    char *buffer = (char *)cma_malloc(bufsize, true);
    int pos = 0;
    int history_index;
    int c;
    char *current_matches[MAX_SUGGESTIONS];
    int current_match_count = 0;
    int current_match_index = 0;
    int in_completion_mode = 0;
    int word_start = 0;
    int prev_buffer_length = 0;

    if (!buffer)
    {
        ft_printf_fd(2, "Allocation error\n");
        rl_disable_raw_mode();
        return NULL;
    }
    rl_enable_raw_mode();
    history_index = history_count;
    ft_printf("%s", prompt);
    fflush(stdout);
    while (1)
    {
        c = rl_read_key();
        if (c != '\t' && in_completion_mode)
        {
            in_completion_mode = 0;
            current_match_count = 0;
            current_match_index = 0;
        }
        if (c == '\r' || c == '\n')
        {
            ft_printf("\n");
            break;
        }
        else if (c == 127 || c == '\b')
        {
            if (pos > 0)
            {
                pos--;
                memmove(&buffer[pos], &buffer[pos + 1], ft_strlen(buffer) - pos + 1);
                rl_clear_line(prompt, prev_buffer_length);
                ft_printf("%s%s", prompt, buffer);
                prev_buffer_length = ft_strlen(buffer);
                fflush(stdout);
            }
        }
        else if (c == 27)
        {
            if (in_completion_mode)
            {
                in_completion_mode = 0;
                current_match_count = 0;
                current_match_index = 0;
            }
            char seq[2];

            if (read(STDIN_FILENO, &seq[0], 1) != 1)
                continue;
            if (read(STDIN_FILENO, &seq[1], 1) != 1)
                continue;
            if (seq[0] == '[')
            {
                if (seq[1] == 'A')
                {
                    if (history_index > 0)
                    {
                        history_index--;
                        rl_clear_line(prompt, prev_buffer_length);
                        pos = 0;
                        strncpy(buffer, history[history_index], bufsize - 1);
                        buffer[bufsize - 1] = '\0';
                        ft_printf("%s%s", prompt, buffer);
                        pos = ft_strlen(buffer);
                        prev_buffer_length = pos;
                        fflush(stdout);
                    }
                }
                else if (seq[1] == 'B')
                {
                    if (history_index < history_count - 1)
                    {
                        history_index++;
                        rl_clear_line(prompt, prev_buffer_length);
                        pos = 0;
                        strncpy(buffer, history[history_index], bufsize - 1);
                        buffer[bufsize - 1] = '\0';
                        ft_printf("%s%s", prompt, buffer);
                        pos = ft_strlen(buffer);
                        prev_buffer_length = pos;
                        fflush(stdout);
                    }
                    else if (history_index == history_count - 1)
                    {
                        history_index++;
                        rl_clear_line(prompt, prev_buffer_length);
                        pos = 0;
                        buffer[0] = '\0';
                        ft_printf("%s", prompt);
                        prev_buffer_length = 0;
                        fflush(stdout);
                    }
                }
            }
        }
        else if (c == '\t')
        {
            if (!in_completion_mode)
            {
                word_start = pos - 1;
                while (word_start >= 0 && buffer[word_start] != ' ')
                    word_start--;
                word_start++;
                int prefix_len = pos - word_start;
                if (prefix_len == 0)
                    continue;
                char prefix[INITIAL_BUFFER_SIZE];
                ft_memcpy(prefix, &buffer[word_start], prefix_len);
                prefix[prefix_len] = '\0';
                current_match_count = 0;
                for (int i = 0; i < suggestion_count; i++)
                {
                    if (ft_strncmp(suggestions[i], prefix, prefix_len) == 0)
                        current_matches[current_match_count++] = suggestions[i];
                }
                if (current_match_count == 0)
                {
                    ft_printf("\a");
                    fflush(stdout);
                }
                else
                {
                    in_completion_mode = 1;
                    current_match_index = 0;
                }
            }

            if (in_completion_mode && current_match_count > 0)
            {
                const char *completion = current_matches[current_match_index];
                int completion_len = ft_strlen(completion);
                pos = word_start;
                buffer[pos] = '\0';

                if (pos + completion_len >= bufsize)
                {
                    int new_bufsize = bufsize;
                    while (pos + completion_len >= new_bufsize)
                        new_bufsize *= 2;
                    buffer = rl_resize_buffer(buffer, bufsize, new_bufsize);
                    bufsize = new_bufsize;
                }
                strcpy(&buffer[pos], completion);
                pos += completion_len;
                buffer[pos] = '\0';
                // Clear line and redraw
                rl_clear_line(prompt, prev_buffer_length);
                ft_printf("%s%s", prompt, buffer);
                prev_buffer_length = ft_strlen(buffer);
                fflush(stdout);
                current_match_index = (current_match_index + 1) % current_match_count;
            }
        }
        else if (c >= 32 && c <= 126)
        {
            if (pos >= bufsize - 1)
            {
                int new_bufsize = bufsize * 2;
                buffer = rl_resize_buffer(buffer, bufsize, new_bufsize);
                bufsize = new_bufsize;
            }
            buffer[pos++] = c;
            buffer[pos] = '\0';
            ft_printf("%c", c);
            prev_buffer_length = ft_strlen(buffer);
            fflush(stdout);
        }
    }
    buffer[pos] = '\0';
    if (history_count < MAX_HISTORY)
        history[history_count++] = cma_strdup(buffer, true);
    else
    {
        cma_free(history[0]);
        memmove(&history[0], &history[1], sizeof(char *) * (MAX_HISTORY - 1));
        history[MAX_HISTORY - 1] = cma_strdup(buffer, true);
    }
    rl_disable_raw_mode();
    return (buffer);
}

