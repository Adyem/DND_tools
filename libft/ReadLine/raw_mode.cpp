#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "readline_internal.hpp"

void rl_disable_raw_mode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
	return ;
}

void rl_enable_raw_mode()
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(rl_disable_raw_mode);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	return ;
}
