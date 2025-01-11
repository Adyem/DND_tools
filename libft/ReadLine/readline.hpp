#ifndef READLINE_HPP
# define READLINE_HPP

void rl_clear_history();
void rl_add_suggestion(const char *word);
void rl_clear_suggestions();
char *rl_readline(const char *prompt) __attribute__((warn_unused_result));

#endif
