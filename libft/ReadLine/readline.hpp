#ifndef READLINE_HPP
# define READLINE_HPP

#define MAX_HISTORY 100
#define INITIAL_BUFFER_SIZE 1024
#define MAX_SUGGESTIONS 1000

extern char *history[MAX_HISTORY];
extern int history_count;

extern char *suggestions[MAX_SUGGESTIONS];
extern int suggestion_count;

void rl_clear_history();
void rl_add_suggestion(const char *word);
void rl_clear_suggestions();
char *rl_readline(const char *prompt);

#endif
