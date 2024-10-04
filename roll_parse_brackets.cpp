#include "libft/Printf/ft_printf.hpp"
#include "dnd_tools.hpp"

int ft_roll_parse_brackets(char *string)
{
    int x = 0;
    int y = 0;
    int bracket_found = 0;

    if (DEBUG == 1)
        ft_printf("Parsing brackets: %s\n", string);
    while (string[x])
    {
        if (string[x] == '(' && !bracket_found)
            bracket_found = 1;
        else if (string[x] == ')' && bracket_found)
            bracket_found = 0;
        else
            string[y++] = string[x];
        x++;
    }
    string[y] = '\0';
    if (DEBUG == 1)
        ft_printf("Modified string: %s\n", string);
    return (0);
}
