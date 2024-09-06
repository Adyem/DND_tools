#include "dnd_tools.hpp"

const char *ft_ordinal_suffix(int number)
{
    if (number == 1)
		return ("first");
    else if (number == 2)
		return ("second");
    else if (number == 3)
		return ("third");
    else if (number == 4)
		return ("fourth");
    else if (number == 5)
		return ("fifth");
    else if (number == 6)
		return ("sixth");
    else if (number == 7)
		return ("seventh");
    else if (number == 8)
		return ("eighth");
    else if (number == 9)
		return ("ninth");
    else if (number == 10)
		return ("tenth");
    else if (number == 11)
		return ("eleventh");
    else if (number == 12)
		return ("twelfth");
    else if (number == 13)
		return ("thirteenth");
    else if (number == 14)
		return ("fourteenth");
    else if (number == 15)
		return ("fifteenth");
    else if (number == 16)
		return ("sixteenth");
    else if (number == 17)
		return ("seventeenth");
    else if (number == 18)
		return ("eighteenth");
    else if (number == 19)
		return ("nineteenth");
    else if (number == 20)
		return ("twentieth");
    return ("nth");
}
