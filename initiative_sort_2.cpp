#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <iostream>

void ft_initiative_print(void)
{
    int i;
    int fd;
    char **content;

    fd = open("data/data--initiative", O_RDONLY);
    if (fd == -1)
    {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        return;
    }
    content = ft_read_file_dnd(fd);
    close(fd);

    if (!content)
    {
        std::cerr << "261-Error allocating memory" << std::endl;
        return;
    }
    std::cout << "\n\nInitiative rolls are:\n";
    i = 0;
    while (content[i])
    {
        std::cout << content[i] << std::endl;
        i++;
    }

    ft_free_double_char(content);
}

void ft_initiative_print_pc(t_pc *players)
{
    t_pc *temp = players;

    while (temp)
    {
        std::cout << temp->name << "=" << temp->initiative << std::endl;
        temp = temp->next;
    }
}

void ft_initiative_sort_2(t_pc *players)
{
    int turn = 0;
    int fd;
    t_pc *temp;
    t_pc *highest;

    fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        std::cerr << "262-Error opening file: " << strerror(errno) << std::endl;
        return;
    }
    while (1)
    {
        temp = players;
        highest = NULL;
        while (temp)
        {
            if ((highest == NULL || temp->initiative > highest->initiative) && temp->initiative != -1)
                highest = temp;
            temp = temp->next;
        }
        if (highest == NULL)
            break;
        if (turn == 0)
        {
            dprintf(fd, "--turn--%s=%i\n", highest->name, highest->initiative);
            turn = 1;
        }
        else
            dprintf(fd, "%s=%i\n", highest->name, highest->initiative);
        highest->initiative = -1;
    }
    close(fd);
}
