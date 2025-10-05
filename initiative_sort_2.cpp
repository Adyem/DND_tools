#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_file.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CPP_class/class_fd_istream.hpp"
#include "libft/Errno/errno.hpp"
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
    if (file.get_error())
    {
        pf_printf("Error opening file: %s\n", file.get_error_str());
        return ;
    }
    ft_fd_istream file_stream(file.get_fd());
    content = ft_read_file_lines(file_stream, 1024);
    if (!content)
    {
        if (ft_errno == ER_SUCCESS)
        {
            pf_printf("\n\nInitiative rolls are:\n");
            return ;
        }
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


static t_pc *ft_merge_lists(t_pc *a, t_pc *b)
{
    t_pc *result = ft_nullptr;

    if (!a)
        return (b);
    if (!b)
        return (a);
    if (a->initiative >= b->initiative)
    {
        result = a;
        result->next = ft_merge_lists(a->next, b);
    }
    else
    {
        result = b;
        result->next = ft_merge_lists(a, b->next);
    }
    return (result);
}

static void ft_split_list(t_pc *source, t_pc **front, t_pc **back)
{
    t_pc *slow;
    t_pc *fast;

    if (!source || !source->next)
    {
        *front = source;
        *back = ft_nullptr;
        return ;
    }
    slow = source;
    fast = source->next;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = ft_nullptr;
}

static void ft_merge_sort(t_pc **head)
{
    t_pc *h = *head;
    t_pc *a;
    t_pc *b;

    if (!h || !h->next)
        return ;
    ft_split_list(h, &a, &b);
    ft_merge_sort(&a);
    ft_merge_sort(&b);
    *head = ft_merge_lists(a, b);
}

void ft_initiative_sort_2(t_pc *players)
{
    int         turn = 0;
    t_pc        *temp;

    ft_merge_sort(&players);

    ft_file initiative_file("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (initiative_file.get_error())
    {
        pf_printf("262-Error opening file: %s\n", initiative_file.get_error_str());
        return ;
    }
    temp = players;
    while (temp)
    {
        if (turn == 0)
        {
            pf_printf_fd(initiative_file.get_fd(), "--turn--%s=%d\n", temp->name,
                    temp->initiative);
            turn = 1;
        }
        else
            pf_printf_fd(initiative_file.get_fd(), "%s=%d\n", temp->name,
                    temp->initiative);
        temp = temp->next;
    }
}
