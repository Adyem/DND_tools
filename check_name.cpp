#include "dnd_tools.hpp"
#include "libft/File/open_dir.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/Template/vector.hpp"
#include "identification.hpp"

static char ft_char_to_lower(unsigned char value)
{
    char buffer[2];

    buffer[0] = static_cast<char>(value);
    buffer[1] = '\0';
    ft_to_lower(buffer);
    return (buffer[0]);
}

static int has_prefix_case_insensitive(const char *value, const char *prefix)
{
    size_t  index;

    if (!value || !prefix)
        return (0);
    index = 0;
    while (prefix[index] != '\0')
    {
        if (value[index] == '\0')
            return (0);
        if (ft_char_to_lower(static_cast<unsigned char>(value[index]))
            != ft_char_to_lower(static_cast<unsigned char>(prefix[index])))
            return (0);
        index++;
    }
    return (1);
}

static int append_entry_variants(ft_vector<ft_string> &entries, const char *entry_name)
{
    ft_string   full_name(entry_name);

    if (full_name.get_error() != ER_SUCCESS)
        return (-1);
    entries.push_back(full_name);
    if (entries.get_error() != ER_SUCCESS)
        return (-1);
    if (has_prefix_case_insensitive(entry_name, EXCLUDE_PREFIX) == 1)
    {
        ft_string   trimmed(entry_name);
        size_t      prefix_length;

        if (trimmed.get_error() != ER_SUCCESS)
            return (-1);
        prefix_length = ft_strlen(EXCLUDE_PREFIX);
        trimmed.erase(0, prefix_length);
        entries.push_back(trimmed);
        if (entries.get_error() != ER_SUCCESS)
            return (-1);
    }
    return (0);
}

static int collect_directory_entries(ft_vector<ft_string> &entries,
        const char *required_prefix, const char *skip_prefix)
{
    file_dir    *directory;
    file_dirent *directory_entry;

    directory = file_opendir(DATA_FOLDER);
    if (directory == ft_nullptr)
        return (-2);
    directory_entry = file_readdir(directory);
    while (directory_entry != ft_nullptr)
    {
        if (ft_strcmp(directory_entry->d_name, ".") == 0
            || ft_strcmp(directory_entry->d_name, "..") == 0)
        {
            directory_entry = file_readdir(directory);
            continue ;
        }
        if (skip_prefix && has_prefix_case_insensitive(directory_entry->d_name,
                skip_prefix) == 1)
        {
            directory_entry = file_readdir(directory);
            continue ;
        }
        if (required_prefix && has_prefix_case_insensitive(directory_entry->d_name,
                required_prefix) == 0)
        {
            directory_entry = file_readdir(directory);
            continue ;
        }
        if (append_entry_variants(entries, directory_entry->d_name) != 0)
        {
            file_closedir(directory);
            return (-1);
        }
        directory_entry = file_readdir(directory);
    }
    if (file_closedir(directory) != 0)
    {
        ft_errno = FT_ERR_IO;
        return (-1);
    }
    ft_errno = ER_SUCCESS;
    return (0);
}

static void debug_print_candidate(const ft_string &candidate, const char *name,
        int use_against)
{
    if (DEBUG != 1)
        return ;
    if (use_against == 1)
    {
        pf_printf("Checking %s against %s\n", candidate.c_str(), name);
        return ;
    }
    pf_printf("Checking %s %s\n", candidate.c_str(), name);
    return ;
}

static int match_candidate_name(ft_vector<ft_string> &entries,
        const char *name, int use_against)
{
    size_t          total_entries;
    size_t          index;
    const ft_string *candidate;

    total_entries = entries.size();
    if (entries.get_error() != ER_SUCCESS)
        return (-1);
    index = 0;
    while (index < total_entries)
    {
        candidate = &entries[index];
        if (entries.get_error() != ER_SUCCESS)
            return (-1);
        debug_print_candidate(*candidate, name, use_against);
        if (ft_strcmp(candidate->c_str(), name) == 0)
        {
            if (DEBUG == 1)
                pf_printf("Found %s\n", name);
            ft_errno = ER_SUCCESS;
            return (1);
        }
        index++;
    }
    return (0);
}

int ft_set_stats_check_name(const char *name)
{
    ft_vector<ft_string>    entries;
    int                     result;

    if (!name)
    {
        pf_printf_fd(2, "259-Error: Name does not exist\n");
        return (-1);
    }
    result = collect_directory_entries(entries, ft_nullptr, PREFIX_TO_SKIP);
    if (result == -2)
    {
        pf_printf_fd(2, "295-Error: Opendir has failed: %s\n", ft_strerror(ft_errno));
        return (-2);
    }
    if (result != 0)
    {
        pf_printf_fd(2, "296-Error: Failed to collect player names: %s\n",
            ft_strerror(ft_errno));
        return (-2);
    }
    result = match_candidate_name(entries, name, 0);
    if (result == 1)
        return (0);
    if (result == -1)
    {
        pf_printf_fd(2, "297-Error: Failed to iterate player names: %s\n",
            ft_strerror(ft_errno));
        return (-2);
    }
    pf_printf_fd(2, "258-Error: Target does not exist\n");
    return (1);
}

int ft_check_player_character(const char *name)
{
    ft_vector<ft_string>    entries;
    int                     result;

    result = collect_directory_entries(entries, PC_PREFIX, ft_nullptr);
    if (result == -2)
    {
        pf_printf_fd(2, "307-Error: Opendir has failed: %s\n", ft_strerror(ft_errno));
        return (-2);
    }
    if (result != 0)
    {
        pf_printf_fd(2, "308-Error: Failed to collect player names: %s\n",
            ft_strerror(ft_errno));
        return (-2);
    }
    result = match_candidate_name(entries, name, 1);
    if (result == 1)
        return (0);
    if (result == -1)
    {
        pf_printf_fd(2, "309-Error: Failed to iterate player names: %s\n",
            ft_strerror(ft_errno));
        return (-2);
    }
    return (1);
}
