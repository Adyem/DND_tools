#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_file.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/vector.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "read_file_lines.hpp"

typedef struct s_initiative_entry
{
    ft_string   name;
    int         initiative;
}   t_initiative_entry;

static void ft_trim_newline(ft_string &line)
{
    size_t  newline_index;

    newline_index = line.find("\n");
    if (line.get_error() != ER_SUCCESS)
        return ;
    if (newline_index != ft_string::npos)
    {
        size_t  total_length;

        total_length = line.size();
        if (line.get_error() != ER_SUCCESS)
            return ;
        if (total_length >= newline_index)
            line.erase(newline_index, total_length - newline_index);
    }
    return ;
}

static int ft_append_initiative_entry(ft_vector<t_initiative_entry> &entries,
        const char *line_content)
{
    ft_string           line(line_content);
    size_t              equals_index;
    ft_string           name_part;
    ft_string           value_part;
    const char          *value_string;
    t_initiative_entry  entry;

    if (line.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (1);
    }
    ft_trim_newline(line);
    if (line.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (1);
    }
    equals_index = line.find("=");
    if (line.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (1);
    }
    if (equals_index == ft_string::npos)
    {
        pf_printf("Error did not find = sign\n");
        return (1);
    }
    name_part = line.substr(0, equals_index);
    if (name_part.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (1);
    }
    value_part = line.substr(equals_index + 1);
    if (value_part.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (1);
    }
    value_string = value_part.c_str();
    if (ft_validate_int(value_string))
    {
        pf_printf("There is an error on the line: %s\n", value_string);
        return (1);
    }
    entry.initiative = ft_atoi(value_string);
    entry.name = name_part;
    if (entry.name.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (1);
    }
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (1);
    }
    if (DEBUG == 1)
        pf_printf("The initiative from %s = %d\n", entry.name.c_str(), entry.initiative);
    return (0);
}

static int ft_collect_initiative_entries(char **content,
        ft_vector<t_initiative_entry> &entries)
{
    size_t  index;

    if (!content)
        return (0);
    index = 0;
    while (content[index])
    {
        if (ft_append_initiative_entry(entries, content[index]))
            return (1);
        index++;
    }
    return (0);
}

static t_pc  *ft_build_players_from_entries(ft_vector<t_initiative_entry> &entries)
{
    size_t  index;
    size_t  total;
    t_pc    *head;
    t_pc    *tail;
    t_pc    *current;

    total = entries.size();
    if (entries.get_error() != ER_SUCCESS)
    {
        pf_printf("257 Error allocating memory\n");
        return (ft_nullptr);
    }
    if (total == 0)
        return (ft_nullptr);
    head = ft_nullptr;
    tail = ft_nullptr;
    index = 0;
    while (index < total)
    {
        const t_initiative_entry &entry = entries[index];

        if (entries.get_error() != ER_SUCCESS)
        {
            pf_printf("257 Error allocating memory\n");
            ft_free_players(head);
            return (ft_nullptr);
        }
        current = static_cast<t_pc *>(cma_malloc(sizeof(t_pc)));
        if (!current)
        {
            pf_printf("Error allocating memory: players\n");
            ft_free_players(head);
            return (ft_nullptr);
        }
        current->name = cma_strdup(entry.name.c_str());
        if (!current->name)
        {
            pf_printf("257 Error allocating memory\n");
            cma_free(current);
            ft_free_players(head);
            return (ft_nullptr);
        }
        current->initiative = entry.initiative;
        current->position.x = 0;
        current->position.y = 0;
        current->position.z = 0;
        current->next = ft_nullptr;
        if (!head)
            head = current;
        else
            tail->next = current;
        tail = current;
        index++;
    }
    return (head);
}

t_pc    *ft_initiative_players_am(char **content)
{
    ft_vector<t_initiative_entry>    entries(4);

    if (!content || !content[0])
        return (ft_nullptr);
    if (ft_collect_initiative_entries(content, entries))
        return (ft_nullptr);
    return (ft_build_players_from_entries(entries));
}

void    ft_initiative_sort(ft_file &file)
{
    t_pc    *players;
    char    **content;

    content = ft_read_file_lines_fd(file.get_fd(), 1024);
    if (!content)
        return ;
    players = ft_initiative_players_am(content);
    cma_free_double(content);
    if (!players)
        return ;
    ft_initiative_sort_2(players);
    ft_free_players(players);
    ft_initiative_print();
    return ;
}
