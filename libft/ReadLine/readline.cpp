#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "../CMA/CMA.hpp"
#include "../Printf/ft_printf.hpp"
#include "readline.hpp"

struct termios	orig_termios;
char			*history[MAX_HISTORY];
int				history_count = 0;

static void rl_disable_raw_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

static void rl_enable_raw_mode()
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(rl_disable_raw_mode);
	raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

static int rl_read_key()
{
	int nread;
	char c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
		;
	return c;
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

static void rl_clear_line(int pos)
{
	while (pos > 0)
	{
		ft_printf("\b \b");
		pos--;
	}
}

char *rl_readline(const char *prompt)
{
	int	bufsize = INITIAL_BUFFER_SIZE;
	char *buffer = (char *)cma_malloc(bufsize, true);
	int	pos = 0;
	int	history_index;
	int	c;

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
				ft_printf("\b \b");
				fflush(stdout);
			}
		}
		else if (c == 27)
		{
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
						rl_clear_line(pos);
						pos = 0;
						strncpy(buffer, history[history_index], bufsize - 1);
						buffer[bufsize - 1] = '\0';
						ft_printf("%s", buffer);
						pos = strlen(buffer);
						fflush(stdout);
					}
				}
				else if (seq[1] == 'B')
				{
					if (history_index < history_count - 1)
					{
						history_index++;
						rl_clear_line(pos);
						pos = 0;
						strncpy(buffer, history[history_index], bufsize - 1);
						buffer[bufsize - 1] = '\0';
						ft_printf("%s", buffer);
						pos = strlen(buffer);
						fflush(stdout);
					}
					else if (history_index == history_count - 1)
					{
						history_index++;
						rl_clear_line(pos);
						pos = 0;
						buffer[0] = '\0';
						fflush(stdout);
					}
				}
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
			ft_printf("%c", c);
			fflush(stdout);
		}
	}
	buffer[pos] = '\0';
	if (history_count < MAX_HISTORY)
		history[history_count++] = cma_strdup(buffer, true);
	else
	{
		cma_free(history[0]);
		memmove(&history[0], &history[1], sizeof(char*) * (MAX_HISTORY - 1));
		history[MAX_HISTORY - 1] = cma_strdup(buffer, true);
	}

	rl_disable_raw_mode();
	return buffer;
}
