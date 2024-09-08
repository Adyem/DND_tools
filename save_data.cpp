#include "dnd_tools.hpp"
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

static void	ft_npc_write_file_1(t_char *info, t_stats *stats, std::ofstream &ofs)
{
	ofs << "HEALTH=" << stats->health << std::endl;
	ofs << "TEMP_HP=" << stats->temp_hp << std::endl;
	ofs << "STR=" << stats->str << std::endl;
	ofs << "DEX=" << stats->dex << std::endl;
	ofs << "CON=" << stats->con << std::endl;
	ofs << "INT=" << stats->inte << std::endl;
	ofs << "WIS=" << stats->wis << std::endl;
	ofs << "CHA=" << stats->cha << std::endl;
	ofs << "TURN=" << stats->turn << std::endl;
	ofs << "PHASE=" << stats->phase << std::endl;
	ofs << "INITIATIVE=" << info->initiative << std::endl;
	ofs << "BLESS_DUR=" << info->bufs.bless.duration << std::endl;
	ofs << "LIGHTNING_STRIKE_DUR=" << info->bufs.lightning_strike.duration << std::endl;
	ofs << "PROTECTIVE_WINDS_DUR=" << info->bufs.protective_winds.duration << std::endl;
	return ;
}

static void	ft_npc_write_file_double_char(const char *msg, char **targets, std::ofstream &ofs, t_char *info)
{
	int	i = 0;

	if (targets)
	{
		while (targets[i])
		{
			if (DEBUG == 1)
				std::cout << "saving array " << info->name << " " << msg << targets[i] << std::endl;
			ofs << msg << targets[i] << std::endl;
			i++;
		}
	}
}

static void	ft_npc_write_file_2(t_char *info, t_resistance *resistance, std::ofstream &ofs)
{
	ofs << "ACID_RESISTANCE=" << resistance->acid << std::endl;
	ofs << "BLUDGEONING_RESISTANCE=" << resistance->bludgeoning << std::endl;
	ofs << "COLD_RESISTANCE=" << resistance->cold << std::endl;
	ofs << "FIRE_RESISTANCE=" << resistance->fire << std::endl;
	ofs << "FORCE_RESISTANCE=" << resistance->force << std::endl;
	ofs << "LIGHTNING_RESISTANCE=" << resistance->lightning << std::endl;
	ofs << "NECROTIC_RESISTANCE=" << resistance->necrotic << std::endl;
	ofs << "PIERCING_RESISTANCE=" << resistance->piercing << std::endl;
	ofs << "POISON_RESISTANCE=" << resistance->poison << std::endl;
	ofs << "PSYCHIC_RESISTANCE=" << resistance->psychic << std::endl;
	ofs << "RADIANT_RESISTANCE=" << resistance->radiant << std::endl;
	ofs << "SLASHING_RESISTANCE=" << resistance->slashing << std::endl;
	ofs << "THUNDER_RESISTANCE=" << resistance->thunder << std::endl;
	ofs << "CONCENTRATION=" << info->concentration.concentration << std::endl;
	ofs << "CONC_SPELL_ID=" << info->concentration.spell_id << std::endl;
	ofs << "CONC_DICE_AMOUNT=" << info->concentration.dice_amount_mod << std::endl;
	ofs << "CONC_DICE_FACES=" << info->concentration.dice_faces_mod << std::endl;
	ofs << "CONC_BASE_MOD=" << info->concentration.base_mod << std::endl;
	ofs << "CONC_DURATION=" << info->concentration.duration << std::endl;
	ft_npc_write_file_double_char("CONC_TARGETS=", info->concentration.targets, ofs, info);
	ofs << "HUNTERS_MARK_AMOUNT=" << info->debufs.hunters_mark.amount << std::endl;
	ft_npc_write_file_double_char("HUNTERS_MARK_CASTER=", info->debufs.hunters_mark.caster_name, ofs, info);
	ofs << "CHAOS_ARMOR_DURATION=" << info->bufs.chaos_armor.duration << std::endl;
	ofs << "PRONE=" << info->flags.prone << std::endl;
	ofs << "BLINDED=" << info->debufs.blinded.duration << std::endl;
	return ;
}

#include "dnd_tools.hpp"
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

void	ft_npc_write_file(t_char *info, t_stats *stats, t_resistance *resistance, int fd)
{
	std::ofstream ofs;

	if (DEBUG == 1)
		std::cout << "fd = " << fd << std::endl;
	if (info->flags.alreaddy_saved)
		return ;
	if (fd == -1)
	{
		fd = open(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd == -1)
		{
			std::cerr << "Error opening file " << info->save_file 
                      << ": " << strerror(errno) << std::endl;
			return ;
		}
	}
	ofs.open("/proc/self/fd/" + std::to_string(fd));
	if (!ofs.is_open())
	{
		std::cerr << "Error: failed to open file stream for descriptor " << fd << std::endl;
		return ;
	}
	ft_npc_write_file_1(info, stats, ofs);
	ft_npc_write_file_2(info, resistance, ofs);
	ofs.close();
	info->flags.alreaddy_saved = 1;
	return ;
}
