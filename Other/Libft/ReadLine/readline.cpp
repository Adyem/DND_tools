#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_HISTORY 100
#define INITIAL_BUFFER_SIZE 1024

static char *history[MAX_HISTORY];
static int history_count = 0;

struct termios orig_termios;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void enable_raw_mode() {
    struct termios raw;

    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // Turn off echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int read_key() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1);
    return c;
}

char *ft_readline(const char *prompt) {
    enable_raw_mode();

    int bufsize = INITIAL_BUFFER_SIZE;
    char *buffer = malloc(bufsize);
    if (!buffer) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    int pos = 0;
    int history_index = history_count;

    printf("%s", prompt);
    fflush(stdout);

    while (1) {
        int c = read_key();

        if (c == '\r' || c == '\n') {
            printf("\n");
            break;
        } else if (c == 127 || c == '\b') { // Backspace
            if (pos > 0) {
                pos--;
                printf("\b \b");
                fflush(stdout);
            }
        } else if (c == 27) { // Escape sequence
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) continue;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) continue;

            if (seq[0] == '[') {
                if (seq[1] == 'A') { // Up arrow
                    if (history_index > 0) {
                        // Clear current line
                        while (pos > 0) {
                            printf("\b \b");
                            pos--;
                        }
                        history_index--;
                        strcpy(buffer, history[history_index]);
                        printf("%s", buffer);
                        pos = strlen(buffer);
                        fflush(stdout);
                    }
                } else if (seq[1] == 'B') { // Down arrow
                    if (history_index < history_count - 1) {
                        // Clear current line
                        while (pos > 0) {
                            printf("\b \b");
                            pos--;
                        }
                        history_index++;
                        strcpy(buffer, history[history_index]);
                        printf("%s", buffer);
                        pos = strlen(buffer);
                        fflush(stdout);
                    } else if (history_index == history_count - 1) {
                        // Clear current line
                        while (pos > 0) {
                            printf("\b \b");
                            pos--;
                        }
                        history_index++;
                        buffer[0] = '\0';
                        fflush(stdout);
                    }
                }
            }
        } else if (c >= 32 && c <= 126) { // Printable characters
            if (pos >= bufsize - 1) {
                // Need to resize buffer
                bufsize *= 2;
                char *new_buffer = realloc(buffer, bufsize);
                if (!new_buffer) {
                    free(buffer);
                    fprintf(stderr, "Allocation error\n");
                    exit(EXIT_FAILURE);
                }
                buffer = new_buffer;
            }
            buffer[pos++] = c;
            printf("%c", c);
            fflush(stdout);
        }
    }

    buffer[pos] = '\0';

    // Add to history
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(buffer);
    } else {
        free(history[0]);
        memmove(&history[0], &history[1], sizeof(char*) * (MAX_HISTORY - 1));
        history[MAX_HISTORY - 1] = strdup(buffer);
    }

    disable_raw_mode();
    return buffer;
}
