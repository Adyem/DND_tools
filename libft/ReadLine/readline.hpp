#ifndef READLINE_HPP
# define READLINE_HPP

#define MAX_HISTORY 100
#define INITIAL_BUFFER_SIZE 1024

static char *history[MAX_HISTORY];
static int history_count = 0;

void	clear_history();
char	*ft_readline(const char *prompt);

#endif
