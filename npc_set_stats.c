#include "dnd_tools.h"

int ft_set_stats_1(t_char *info, char **content, int i)
{
	int	r_value;

	r_value = 0;
	if (ft_strncmp(content[i], "HEALTH=", 7) == 0 && (info->stats.health == -1))
		info->stats.health = ft_check_stat(info, content[i], 7);
	else if (ft_strncmp(content[i], "TEMP_HP=", 8) == 0 && (info->stats.temp_hp == -1))
		info->stats.temp_hp = ft_check_stat(info, content[i], 8);
	else if (ft_strncmp(content[i], "AC=", 3) == 0 && (info->stats.ac == -1))
		info->stats.ac = ft_check_stat(info, content[i], 3);
	else if (ft_strncmp(content[i], "STR=", 4) == 0 && (info->stats.str == -1))
		info->stats.str = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "DEX=", 4) == 0 && (info->stats.dex == -1))
		info->stats.dex = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "CON=", 4) == 0 && (info->stats.con == -1))
		info->stats.con = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "INT=", 4) == 0 && (info->stats.inte == -1))
		info->stats.inte = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "WIS=", 4) == 0 && (info->stats.wis == -1))
		info->stats.wis = ft_check_stat(info, content[i], 4);
	else if (ft_strncmp(content[i], "CHA=", 4) == 0 && (info->stats.cha == -1))
		info->stats.cha = ft_check_stat(info,content[i], 4);
	else if (ft_strncmp(content[i], "TURN=", 5) == 0 && (info->stats.turn == -1))
		info->stats.turn = ft_check_stat(info, content[i], 5);
	else if (ft_strncmp(content[i], "INITIATIVE=", 11) == 0 && (info->initiative == -1))
		info->initiative = ft_check_stat(info, content[i], 11);
	else if (ft_strncmp(content[i], "BLESS_DUR=", 10) == 0
			&& (info->bufs.bless.duration == 0))
		info->bufs.bless.duration = ft_check_stat(info, content[i], 10);
	else if(ft_strncmp(content[i], "PHASE=", 6) == 0 && (info->stats.phase== -1))
		info->stats.phase = ft_check_stat(info, content[i], 6);
	else if (ft_strncmp(content[i], "LIGHTNING_STRIKE_DUR=", 21) == 0)
		info->bufs.lightning_strike.duration = ft_check_stat(info, content[i], 21);
	else if (ft_strncmp(content[i], "PROTECTIVE_WINDS_DUR=", 21) == 0)
		info->bufs.protective_winds.duration = ft_check_stat(info, content[i], 21);
	else
		r_value = 1;
	return(r_value);
}

int	ft_set_stats_2(t_char *info, char **content, int i)
{
	int r_value;

	r_value = 0;
	if (ft_strncmp(content[i], "ACID_RESISTANCE=", 16) == 0
			&& info->c_resistance.acid == -501)
		info->c_resistance.acid = ft_check_stat(info, content[i], 16);
	else if (ft_strncmp(content[i], "BLUDGEONING_RESISTANCE=", 23) == 0 
			&& info->c_resistance.bludgeoning == -501)
		info->c_resistance.bludgeoning = ft_check_stat(info, content[i], 23);
	else if (ft_strncmp(content[i], "COLD_RESISTANCE=", 16) == 0
			&& info->c_resistance.cold == -501)
		info->c_resistance.cold = ft_check_stat(info, content[i], 16);
	else if (ft_strncmp(content[i], "FIRE_RESISTANCE=", 16) == 0
			&& info->c_resistance.fire == -501)
		info->c_resistance.fire = ft_check_stat(info, content[i], 16);
	else if (ft_strncmp(content[i], "FORCE_RESISTANCE=", 17) == 0
			&&  info->c_resistance.force == -501)
		info->c_resistance.force = ft_check_stat(info, content[i], 17);
	else if (ft_strncmp(content[i], "LIGHTNING_RESISTANCE=", 21) == 0
			&& info->c_resistance.lightning == -501)
		info->c_resistance.lightning = ft_check_stat(info, content[i], 21);
	else if (ft_strncmp(content[i], "NECROTIC_RESISTANCE=", 20) == 0
			&& info->c_resistance.necrotic == -501)
		info->c_resistance.necrotic = ft_check_stat(info, content[i], 20);
	else if (ft_strncmp(content[i], "PIERCING_RESISTANCE=", 20) == 0
			&& info->c_resistance.piercing == -501)
		info->c_resistance.piercing = ft_check_stat(info, content[i], 20);
	else if (ft_strncmp(content[i], "POISON_RESISTANCE=", 18) == 0
			&& info->c_resistance.poison  == -501)
		info->c_resistance.poison = ft_check_stat(info, content[i], 18);
	else if (ft_strncmp(content[i], "PSYCHIC_RESISTANCE=", 19) == 0
			&& info->c_resistance.psychic == -501)
		info->c_resistance.psychic = ft_check_stat(info, content[i], 19);
	else if (ft_strncmp(content[i], "RADIANT_RESISTANCE=", 19) == 0
			&& info->c_resistance.radiant == -501)
		info->c_resistance.radiant = ft_check_stat(info, content[i], 19);
	else if (ft_strncmp(content[i], "SLASHING_RESISTANCE=", 20) == 0
			&& info->c_resistance.slashing == -501)
		info->c_resistance.slashing = ft_check_stat(info, content[i], 20);
	else if (ft_strncmp(content[i], "THUNDER_RESISTANCE=", 19) == 0
			&& info->c_resistance.thunder == -501)
		info->c_resistance.thunder = ft_check_stat(info, content[i], 19);
	else if (ft_strncmp(content[i], "CONCENTRATION=", 14) == 0 &&
			info->concentration.concentration == 0)
		info->concentration.concentration = ft_check_stat(info, content[i], 14);
	else if (ft_strncmp(content[i], "CONC_SPELL_ID=", 14) == 0 &&
			info->concentration.spell_id == 0)
		info->concentration.spell_id = ft_check_stat(info, content[i], 14);
	else if (ft_strncmp(content[i], "CONC_DICE_AMOUNT=", 17) == 0 &&
			info->concentration.dice_amount_mod == 0)
		info->concentration.dice_amount_mod = ft_check_stat(info, content[i], 17);
	else if (ft_strncmp(content[i], "CONC_DICE_FACES=", 16) == 0 &&
			info->concentration.dice_faces_mod == 0)
		info->concentration.dice_faces_mod = ft_check_stat(info, content[i], 16);
	else if (ft_strncmp(content[i], "CONC_BASE_MOD=", 14) == 0 &&
			info->concentration.base_mod == 0)
		info->concentration.base_mod = ft_check_stat(info, content[i], 14);
	else if (ft_strncmp(content[i], "CONC_DURATION=", 14) == 0 &&
             info->concentration.duration == 0)
        info->concentration.duration = ft_check_stat(info, content[i], 14);
	else if (ft_strncmp(content[i], "HUNTERS_MARK_AMOUNT=", 20) == 0 &&
            info->debufs.hunters_mark.amount == 0)
        info->debufs.hunters_mark.amount = ft_check_stat(info, content[i], 20);
	else if (ft_strncmp(content[i], "CHAOS_ARMOR_DURATION=", 21) == 0 &&
			info->bufs.chaos_armor.duration == 0)
		info->bufs.chaos_armor.duration = ft_check_stat(info, content[i], 21);
	else
		r_value = 1;
	return(r_value);
}

static int	ft_set_stats_string(t_char *info, char **content, int i)
{
	if (ft_strncmp(content[i], "CONC_TARGETS=", 13) == 0)
    {
        info->concentration.targets = ft_set_stats_con_targets(content[i],
				13, info->concentration.targets);
        if (!info->concentration.targets)
            return (-1);
		return (0);
    }
	else if (ft_strncmp(content[i], "HUNTERS_MARK_CASTER=", 20) == 0)
    {
        info->debufs.hunters_mark.caster_name = ft_set_stats_con_targets(content[i],
				20, info->debufs.hunters_mark.caster_name);
        if (!info->debufs.hunters_mark.caster_name)
            return (-1);
		return (0);
    }
    return (1);
}

int	ft_set_stats(t_char *info, char **content)
{
	int	error;
	int	i;

	i = 0;
	while (content[i])
	{
		if (ft_set_stats_1(info, content, i) == 0)
		{
			i++;
			continue ;
		}
		if (info->version_number >= 2 && ft_set_stats_2(info, content, i) == 0)
		{
			i++;
			continue ;
		}
		if  (info->version_number >= 2 && (error = ft_set_stats_string(info, content, i)) <= 0)
		{
			if (error == 0)
			{
				i++;
				continue ;
			}
			else if (error < 0)
				return (1);
		}
		else
		{
			ft_printf_fd(2, "1-Something is wrong with the save file for Maverick at the "\
				"line: %s, please reinitialize the save\n", content[i]);
			ft_free_double_char(content);
			return (1);
		}
		i++;
	}
	return (0);
}
