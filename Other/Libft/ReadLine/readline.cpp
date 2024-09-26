#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "../CMA/CMA.hpp"
#include "../Libft/libft.hpp"
#include "../Printf/ft_printf.hpp"
#include "readline.hpp"

struct termios orig_termios;

void disable_raw_mode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void enable_raw_mode()
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int read_key()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1);
    return c;
}

char *resize_buffer(char *old_buffer, int current_size, int new_size)
{
    char *new_buffer = (char *)cma_malloc(new_size, true);
    if (!new_buffer) {
        ft_printf_fd(2, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    memcpy(new_buffer, old_buffer, current_size);
    cma_free(old_buffer);
    return new_buffer;
}

char *ft_readline(const char *prompt)
{
    enable_raw_mode();

    int bufsize = INITIAL_BUFFER_SIZE;
    char *buffer = (char *)cma_malloc(bufsize, true);
    if (!buffer) {
        ft_printf_fd(2, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    int pos = 0;
    int history_index = history_count;

    ft_printf("%s", prompt);
    fflush(stdout);

    while (1) {
        int c = read_key();

        if (c == '\r' || c == '\n') {
            ft_printf("\n");
            break;
        } else if (c == 127 || c == '\b') {
            if (pos > 0) {
                pos--;
                ft_printf("\b \b");
                fflush(stdout);
            }
        } else if (c == 27) {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) continue;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) continue;

            if (seq[0] == '[') {
                if (seq[1] == 'A') {
                    if (history_index > 0) {
                        while (pos > 0) {
                            printf("\b \b");
                            pos--;
                        }
                        history_index--;
                        strcpy(buffer, history[history_index]);
                        ft_printf("%s", buffer);
                        pos = ft_strlen(buffer);
                        fflush(stdout);
                    }
                } else if (seq[1] == 'B') {
                    if (history_index < history_count - 1) {
                        while (pos > 0) {
                            ft_printf("\b \b");
                            pos--;
                        }
                        history_index++;
                        strcpy(buffer, history[history_index]);
                        ft_printf("%s", buffer);
                        pos = ft_strlen(buffer);
                        fflush(stdout);
                    } else if (history_index == history_count - 1) {
                        while (pos > 0) {
                            ft_printf("\b \b");
                            pos--;
                        }
                        history_index++;
                        buffer[0] = '\0';
                        fflush(stdout);
                    }
                }
            }
        } else if (c >= 32 && c <= 126) {
            if (pos >= bufsize - 1) {
                int new_bufsize = bufsize * 2;
                buffer = resize_buffer(buffer, bufsize, new_bufsize);
                bufsize = new_bufsize;
            }
            buffer[pos++] = c;
            ft_printf("%c", c);
            fflush(stdout);
        }
    }

    buffer[pos] = '\0';

    if (history_count < MAX_HISTORY) {
        history[history_count++] = cma_strdup(buffer, true);
    } else {
        cma_free(history[0]);
        memmove(&history[0], &history[1], sizeof(char*) * (MAX_HISTORY - 1));
        history[MAX_HISTORY - 1] = cma_strdup(buffer, true);
    }

    disable_raw_mode();
    return buffer;
}
