#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void ft_print_content(char **content)
{
    if (DEBUG != 1)
        return ;   
    int index = 0;
    if (content)
    {
        while (content[index])
        {
            pf_printf("%s", content[index]);
            index++;
        }
    }
    pf_printf("\n");
    return ;
}
