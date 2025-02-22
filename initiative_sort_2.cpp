#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "dnd_tools.hpp"
#include "player_character.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>


void ft_initiative_print(void)
{
    int index;
    char **content;

    ft_file file("data/data--initiative", O_RDONLY);
    if (file.get_error_code())
    {
        pf_printf("Error opening file: %s\n", file.get_error_message());
        return ;
    }
    content = ft_read_file_lines(file);
    if (!content)
    {
        pf_printf("261-Error allocating memory\n");
        return ;
    }
    pf_printf("\n\nInitiative rolls are:\n");
    index = 0;
    while (content[index])
    {
        pf_printf("%s", content[index]);
        index++;
    }
    cma_free_double(content);
}

void ft_initiative_sort_2(t_pc *players)
{
    int		turn = 0;
    t_pc	*temp;
    t_pc	*highest;

	ft_file initiative_file("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (initiative_file.get_error_code())
    {
        pf_printf("262-Error opening file: %s\n", initiative_file.get_error_message());
        return ;
    }
    while (1)
    {
        temp = players;
        highest = ft_nullptr;
        while (temp)
        {
            if ((highest == ft_nullptr || temp->initiative > highest->initiative)
					&& temp->initiative != -1)
                highest = temp;
            temp = temp->next;
        }
        if (highest == ft_nullptr)
            break ;

        if (turn == 0)
        {
            pf_printf_fd(initiative_file.get_fd(), "--turn--%s=%d\n", highest->name,
					highest->initiative);
            turn = 1;
        }
        else
            pf_printf_fd(initiative_file.get_fd(), "%s=%d\n", highest->name, highest->initiative);

        highest->initiative = -1;
    }
}
