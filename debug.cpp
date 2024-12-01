#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void ft_print_content(char **content)
{
    int i;

    if (DEBUG != 1)
        return ;
    
    i = 0;
    if (content)
    {
        while (content[i])
        {
            pf_printf("%s", content[i]);
            i++;
        }
    }
    pf_printf("\n");
    return ;
}
