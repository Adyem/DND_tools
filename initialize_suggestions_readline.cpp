#include "dnd_tools.hpp"
#include "libft/ReadLine/readline.hpp"
#include "identification.hpp"

void	ft_initialize_suggestions_readline()
{
	rl_add_suggestion(DAMAGE_TYPE_ACID);
	rl_add_suggestion(DAMAGE_TYPE_COLD);
	rl_add_suggestion(DAMAGE_TYPE_FIRE);
	rl_add_suggestion(DAMAGE_TYPE_FORCE);
	rl_add_suggestion(DAMAGE_TYPE_POISON);
	rl_add_suggestion(DAMAGE_TYPE_PSYCHIC);
	rl_add_suggestion(DAMAGE_TYPE_RADIANT);
	rl_add_suggestion(DAMAGE_TYPE_THUNDER);
	rl_add_suggestion(DAMAGE_TYPE_NECROTIC);
	rl_add_suggestion(DAMAGE_TYPE_PIERCING);
	rl_add_suggestion(DAMAGE_TYPE_SLASHING);
	rl_add_suggestion(DAMAGE_TYPE_LIGHTNING);
	rl_add_suggestion(DAMAGE_TYPE_BLUDGEONING);
}
