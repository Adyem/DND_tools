#include "dnd_tools.hpp"
#include "libft/CPP_class/string.hpp"

int	ft_check_value(const char *input)
{
	long	check;
	int		i;
	int		sign;

	check = 0;
	i = 0;
	sign = 1;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (!input[i])
		return (1);
	if (input[0] == '-')
		sign = -1;
	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			check = (check * 10) + input[i] - '0';
			if (sign * check < -2147483648 || sign * check > 2147483647)
				return (2);
			i++;
		}
		else
			return (3);
	}
	return (0);
}

int	ft_strcmp_dnd(const char *string1, const char *string2)
{
	if (!string1 || !string2)
		return (-1);
	while (*string1 && (*string1) == (*string2))
	{
		string1++;
		string2++;
	}
	return ((int)(*string1) - (int)(*string2));
}

ft_string ft_check_availeble_spell_slots(int spell_level, t_char *character)
{
	ft_string available_levels;

	if (spell_level == 1 && character->spell_slots.level_1.available == 0)
		available_levels.append(" 1,");
	if (spell_level == 2 && character->spell_slots.level_2.available == 0)
		available_levels.append(" 2,");
	if (spell_level == 3 && character->spell_slots.level_3.available == 0)
		available_levels.append(" 3,");
	if (spell_level == 4 && character->spell_slots.level_4.available == 0)
		available_levels.append(" 4,");
	if (spell_level == 5 && character->spell_slots.level_5.available == 0)
		available_levels.append(" 5,");
	if (spell_level == 6 && character->spell_slots.level_6.available == 0)
		available_levels.append(" 6,");
	if (spell_level == 7 && character->spell_slots.level_7.available == 0)
		available_levels.append(" 7,");
	if (spell_level == 8 && character->spell_slots.level_8.available == 0)
		available_levels.append(" 8,");
	if (spell_level == 9 && character->spell_slots.level_9.available == 0)
		available_levels.append(" 9,");
	if (!available_levels.empty())
		available_levels.erase(available_levels.size() - 1, 1);
	return (available_levels);
}
