#ifndef READLINE_HPP
# define READLINE_HPP

#define MAX_HISTORY 100
#define INITIAL_BUFFER_SIZE 1024

extern char	*history[MAX_HISTORY];
extern int	history_count;

void	rl_clear_history();
char	*rl_readline(const char *prompt);

#endif
