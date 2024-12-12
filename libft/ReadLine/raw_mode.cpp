#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "readline_internal.hpp"

void rl_disable_raw_mode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
	return ;
}

int rl_enable_raw_mode()
{
    struct termios raw;
    if (tcgetattr(STDIN_FILENO, &raw) == -1)
        return (-1);
    raw.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1)
        return (-1);
    return (0);
}
