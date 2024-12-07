#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../CPP_class/nullptr.hpp"
#include "../CMA/CMA.hpp"
#include "../Printf/printf.hpp"
#include "../Libft/libft.hpp"
#include "readline_internal.hpp"

char *rl_resize_buffer(char *old_buffer, int current_size, int new_size)
{
    char *new_buffer = (char *)cma_malloc(new_size, true);

    if (!new_buffer)
    {
        pf_printf_fd(2, "Allocation error\n");
        return (ft_nullptr);
    }
    memcpy(new_buffer, old_buffer, current_size);
    cma_free(old_buffer);
    return (new_buffer);
}

int rl_get_terminal_width()
{
    struct terminal_dimensions terminalSize;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize) == -1) {
        return -1;
    }
    return terminalSize.cols;
}

int rl_clear_line(const char *prompt, const char *buffer)
{
    int total_length = ft_strlen(prompt) + ft_strlen(buffer);
    pf_printf("\r");
    int term_width = rl_get_terminal_width();
	if (term_width == -1)
		return (-1);
    int line_count = (total_length / term_width) + 1;
    for (int i = 0; i < line_count; i++)
    {
        pf_printf("\033[2K");
        if (i < line_count - 1)
            pf_printf("\033[A");
    }
    pf_printf("\r");
	return (0);
}

int rl_read_key()
{
    int nread;
    char c;

    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
        ;
    return (c);
}

void rl_update_history(const char *buffer)
{
    if (history_count < MAX_HISTORY)
        history[history_count++] = cma_strdup(buffer, true);
    else
    {
        cma_free(history[0]);
        memmove(&history[0], &history[1], sizeof(char *) * (MAX_HISTORY - 1));
        history[MAX_HISTORY - 1] = cma_strdup(buffer, true);
    }
	return ;
}
