#include "dnd_tools.hpp"

const char *ft_ordinal_suffix(int number)
{
    static const char *suffix_table[20] = {
        "first", "second", "third", "fourth", "fifth",
        "sixth", "seventh", "eighth", "ninth", "tenth",
        "eleventh", "twelfth", "thirteenth", "fourteenth",
        "fifteenth", "sixteenth", "seventeenth", "eighteenth",
        "nineteenth", "twentieth"
    };

    if (number >= 1 && number <= 20)
        return (suffix_table[number - 1]);
    return ("nth");
}
