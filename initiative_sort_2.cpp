#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>


void ft_initiative_print(void)
{
    int i;
    int fd;
    char **content;

    fd = open("data/data--initiative", O_RDONLY);
    if (fd == -1)
    {
        ft_printf("Error opening file: %s\n", strerror(errno));
        return ;
    }
    content = ft_read_file_dnd(fd);
    close(fd);
    if (!content)
    {
        ft_printf("261-Error allocating memory\n");
        return ;
    }
    ft_printf("\n\nInitiative rolls are:\n");
    i = 0;
    while (content[i])
    {
        ft_printf("%s", content[i]);
        i++;
    }
    cma_free_double(content);
}

void ft_initiative_print_pc(t_pc *players)
{
    t_pc *temp;

	temp = players;
    while (temp)
    {
        ft_printf("%s=%d\n", temp->name, temp->initiative);
        temp = temp->next;
    }
}

void ft_initiative_sort_2(t_pc *players)
{
    int turn = 0;
    t_pc *temp;
    t_pc *highest;
    int fd;

	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_printf("262-Error opening file: %s\n", strerror(errno));
        return ;
    }
    while (1)
    {
        temp = players;
        highest = nullptr;
        while (temp)
        {
            if ((highest == nullptr || temp->initiative > highest->initiative) && temp->initiative != -1)
                highest = temp;
            temp = temp->next;
        }
        if (highest == ft_nullptr)
            break;

        if (turn == 0)
        {
            ft_printf_fd(fd, "--turn--%s=%d\n", highest->name, highest->initiative);
            turn = 1;
        }
        else
            ft_printf_fd(fd, "%s=%d\n", highest->name, highest->initiative);

        highest->initiative = -1;
    }
    close(fd);
}
